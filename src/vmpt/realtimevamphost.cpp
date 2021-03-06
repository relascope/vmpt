/*
   vmpt - virtual music power teacher/transcriber

   Copyright (c) 2015 www.dojoy.at, Günther Humer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "realtimevamphost.h"

#include <vamp-hostsdk/PluginLoader.h>
#include <vamp-hostsdk/PluginInputDomainAdapter.h>

#include <sndfile.h>
#include <string.h>

using Vamp::HostExt::PluginLoader;
using Vamp::HostExt::PluginWrapper;
using Vamp::RealTime;
using Vamp::HostExt::PluginInputDomainAdapter;

using namespace std;

RealTimeVampHost::RealTimeVampHost(string libraryName, string pluginId, string output, bool useFrames, std::map<string, float> pluginParameters,
                    IAudioReader &reader) :
    m_libraryName(libraryName),
    m_pluginId(pluginId),
    m_inputSampleRate(reader.getFileInfo().samplerate),
    m_channels(reader.getFileInfo().channels),
    m_output(output),
    m_useFrames(useFrames),
    m_reader(reader),
    m_pluginParameters(pluginParameters),
    m_outputNo(-1)
{
    // TODO DoJoY Argument Checking and Error handling...
    if (m_libraryName.empty())
        throw std::string("Library name cannot be null or empty. ");
    if (m_pluginId.empty())
        throw std::string("Plugin ID cannot be null or empty. ");

    initialisePlugin();
}

void RealTimeVampHost::process()
{
    float *readbuf = new float[m_blockSize * m_channels];
    float **plugbuf = new float*[m_channels];

    for (int c = 0; c < m_channels; c++)
    {
        plugbuf[c] = new float[m_blockSize + 2];
    }

    long currentStep = 0;
    int finalStepsRemaining = std::max(1, (m_blockSize/m_stepSize) -1);

    do
    {
        int readCount;

        if ((m_blockSize==m_stepSize) || (currentStep == 0))
        {
            // read a full fresh block
            if ((readCount = this->m_reader.readFloat(readbuf, m_blockSize)) < 0)
            {
                throw "Error reading block. ";
                break;
            }
            if (readCount != m_blockSize)
            {
                finalStepsRemaining--;
            }
        }
        else
        {
            // TODO DoJoY step 3 is getting zeros at the beginning... (only if m_channels != 1)
            memmove(readbuf, readbuf + (m_stepSize * m_channels),
                    m_overlapSize * m_channels * sizeof(float));
            if ((readCount = this->m_reader.readFloat(readbuf + (m_overlapSize * m_channels), m_stepSize)) < 0)
            {
                throw "Error reading block. ";
            }
            if (readCount != m_stepSize)
            {
                finalStepsRemaining--;
            }

            readCount += m_overlapSize;
        }

        for (int c = 0; c < m_channels; c++)
        {
            // copy values to buffer
            int r = 0;
            while (r < readCount)
            {
                plugbuf[c][r] = readbuf[r * m_channels + c];
                r++;
            }

            // fill up with zero until blockSize
            while (r < m_blockSize)
            {
                plugbuf[c][r] = 0.0f;
                r++;
            }
        }

        RealTime rt = RealTime::frame2RealTime(currentStep * m_stepSize, m_inputSampleRate);
        Plugin::FeatureSet features = m_plugin->process(plugbuf, rt);

        if (features[m_outputNo].size() > 0)
        {
            if (featuresAvailable)
                featuresAvailable(&features[m_outputNo]);
            printFeatures(RealTime::realTime2Frame(rt + m_timestampAdjustment, m_inputSampleRate),
                          m_inputSampleRate, m_outputNo, features, m_useFrames);
        }

        currentStep++;
    } while (finalStepsRemaining > 0);

    std::cout << "Remaining features..." << std::endl;

    RealTime rt = RealTime::frame2RealTime(currentStep * m_stepSize, m_inputSampleRate);
    Plugin::FeatureSet remainingFeatures = m_plugin->getRemainingFeatures();

    if (remainingFeatures[m_outputNo].size() > 0)
    {
        if (featuresAvailable)
            featuresAvailable(&remainingFeatures[m_outputNo]);

        printFeatures(RealTime::realTime2Frame(rt + m_timestampAdjustment, m_inputSampleRate),
                  m_inputSampleRate, m_outputNo,
                  remainingFeatures, m_useFrames);
    }

    // TODO delete also on error conditions!!!
    delete [] readbuf;

    for (int i=0;i<m_channels;i++)
        delete [] plugbuf[i];

    delete [] plugbuf;

    std::cout << "Processing done." << std::endl;
}


void RealTimeVampHost::initialisePlugin()
{
    PluginLoader *loader = PluginLoader::getInstance();
    PluginLoader::PluginKey key =
            loader->composePluginKey(m_libraryName, m_pluginId);

    int adapterFlags = PluginLoader::ADAPT_ALL_SAFE;
    m_plugin = loader->loadPlugin(key, m_inputSampleRate, adapterFlags);

    if (!m_plugin)
    {
        throw "Plugin loading failed";
    }

    m_blockSize = m_plugin->getPreferredBlockSize();
    m_stepSize = m_plugin->getPreferredStepSize();

    if (m_blockSize == 0)
    {
        m_blockSize = 1024;
    }

    if (m_stepSize == 0)
    {
        if (m_plugin->getInputDomain() == Plugin::FrequencyDomain)
        {
            m_stepSize = m_blockSize / 2;
        }
        else
        {
            m_stepSize = m_blockSize;
        }
    } else if (m_stepSize > m_blockSize)
    {
        if (m_plugin->getInputDomain() == Plugin::FrequencyDomain)
        {
            m_blockSize = m_stepSize * 2;
        }
        else
        {
            m_blockSize = m_stepSize;
        }
    }

    m_overlapSize = m_blockSize - m_stepSize;

    Plugin::OutputList outputs = m_plugin->getOutputDescriptors();

    if (outputs.empty())
    {
        throw "Plugin has no outputs. ";
    }

    for (size_t oi = 0; oi <  outputs.size(); oi++)
    {
        if (outputs[oi].identifier == m_output)
        {
            m_outputNo = oi;
            break;
        }
    }

    if (m_outputNo == -1)
    {
        throw "Plugin Outputdescriptor not found. ";
    }
    
    for (auto& param : m_pluginParameters) {
		m_plugin->setParameter(param.first, param.second);
    }

    if (!m_plugin->initialise(m_channels, m_stepSize, m_blockSize))
    {
        throw "Plugin Initialisation failed. ";
    }

    PluginWrapper* wrapper = dynamic_cast<PluginWrapper *>(m_plugin);
    if (wrapper)
    {
        PluginInputDomainAdapter *ida =
                wrapper->getWrapper<PluginInputDomainAdapter>();
        if (ida)
        {
            m_timestampAdjustment = ida->getTimestampAdjustment();
        }
    }

    std::cout << "Plugin " << m_pluginId << " loaded and initialised successfully... " << std::endl;
}

RealTimeVampHost::~RealTimeVampHost()
{
    if (m_plugin)
        delete m_plugin;
}

/**
  * FROM VAMP-HOSTSDK HOST EXAMPLE
  */
void RealTimeVampHost::printFeatures(int frame, int sr, int output,
              Plugin::FeatureSet features, bool useFrames)
{
    for (unsigned int i = 0; i < features[output].size(); ++i) {

        if (useFrames) {

            int displayFrame = frame;

            if (features[output][i].hasTimestamp) {
                displayFrame = RealTime::realTime2Frame
                    (features[output][i].timestamp, sr);
            }

            cout << displayFrame;

            if (features[output][i].hasDuration) {
                displayFrame = RealTime::realTime2Frame
                    (features[output][i].duration, sr);
                cout << "," << displayFrame;
            }

            cout  << ":";

        } else {

            RealTime rt = RealTime::frame2RealTime(frame, sr);

            if (features[output][i].hasTimestamp) {
                rt = features[output][i].timestamp;
            }

            cout << rt.toString();

            if (features[output][i].hasDuration) {
                rt = features[output][i].duration;
                cout << "," << rt.toString();
            }

            cout << ":";
        }

        for (unsigned int j = 0; j < features[output][i].values.size(); ++j) {
            cout << " " << features[output][i].values[j];
        }
        cout << " " << features[output][i].label;

        cout << endl;
    }
}
