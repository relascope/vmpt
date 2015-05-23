#include "realtimevamphost.h"

#include <signal.h>
#include <QDebug>


#include <string>
#include <algorithm>
#include <vamp-hostsdk/PluginLoader.h>
#include <vamp-hostsdk/PluginInputDomainAdapter.h>

using Vamp::HostExt::PluginLoader;
using Vamp::HostExt::PluginWrapper;
using Vamp::RealTime;
using Vamp::HostExt::PluginInputDomainAdapter;

RealTimeVampHost::RealTimeVampHost(QString libraryName, QString pluginId, float inputSampleRate,
                   int channels, QString output, bool useFrames,
                    cbReadFloat readFloatFunc) :
    m_libraryName(libraryName),
    m_pluginId(pluginId),
    m_inputSampleRate(inputSampleRate),
    m_channels(channels),
    m_output(output),
    m_useFrames(useFrames),
    m_readFloatFunc(readFloatFunc),
    m_outputNo(-1)
{
    // TODOJOY Argument Checking and Error handling...
    if (m_libraryName.isNull() || m_libraryName.isEmpty())
        throw "Library name cannot be null or empty. ";
    if (m_pluginId.isNull() || m_pluginId.isEmpty())
        throw "Plugin ID cannot be null or empty. ";

    if (!m_readFloatFunc)
        throw "Set a function, where the host can read float values for audio analysis";

    initialisePlugin();
}

void *RealTimeVampHost::finish()
{
    return 0;
}


void
printFeatures(int frame, int sr, int output,
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

void *RealTimeVampHost::process()
{
    // negotiate over blocks
    // should we write a pluginBufferingadapter??

    // TRY with buffer of changing size and see if PluginBufferingAdapter works
    // it is loaded...

    // process exptects blocksize, so we give it to him!

    // buffer has to be remapped to a float buffer...


    float *readbuf = new float[m_blockSize * m_channels];
    float **plugbuf = new float*[m_channels];

    for (int c = 0; c < m_channels; c++)
    {
        plugbuf[c] = new float[m_blockSize + 2];
    }

    qint64 currentStep = 0;
    int finalStepsRemaining = max(1, (m_blockSize/m_stepSize) -1);

    do
    {
        int readCount;

        if ((m_blockSize==m_stepSize) || (currentStep == 0))
        {
            // read a full fresh block
            if ((readCount = m_readFloatFunc(readbuf, m_blockSize)) < 0)
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
            memmove(readbuf, readbuf + (m_stepSize * m_channels), m_overlapSize * m_channels * sizeof(float));
            if ((readCount = m_readFloatFunc(readbuf + (m_overlapSize * m_channels), m_stepSize)) < 0)
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

        printFeatures(RealTime::realTime2Frame(rt + m_timestampAdjustment, m_inputSampleRate),
                      m_inputSampleRate, m_outputNo, features, m_useFrames);

        currentStep++;
    } while (finalStepsRemaining > 0);

    RealTime rt = RealTime::frame2RealTime(currentStep * m_stepSize, m_inputSampleRate);
    Plugin::FeatureSet remainingFeatures = m_plugin->getRemainingFeatures();

    printFeatures(RealTime::realTime2Frame(rt + m_timestampAdjustment, m_inputSampleRate),
                  m_inputSampleRate, m_outputNo,
                  remainingFeatures, m_useFrames);

    qDebug() << "Processing done.";
    return 0;
}

void RealTimeVampHost::initialisePlugin()
{
    PluginLoader *loader = PluginLoader::getInstance();
    PluginLoader::PluginKey key =
            loader->composePluginKey(m_libraryName.toStdString(), m_pluginId.toStdString());

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
        if (outputs[oi].identifier == m_output.toStdString())
        {
            m_outputNo = oi;
            break;
        }
    }

    if (m_outputNo == -1)
    {
        throw "Plugin Outputdescriptor not found. ";
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

    qDebug() << QString("Plugin %1 loaded and initialised successfully... ").arg(m_pluginId);
}

RealTimeVampHost::~RealTimeVampHost()
{
    if (m_plugin)
        delete m_plugin;
}
