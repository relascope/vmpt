#include "realtimevamphost.h"

#include "debughelper.h"
#include <iostream>
#include <fstream>

#include <sndfile.h>


#include <signal.h>
#include <QDebug>

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

//    ASSERT(m_channels == 1);
//    if (m_channels != 1)
//    {
//        throw "Sorry, we have a bug in here. At the time we can only work with one channel audio. ";
//    }

    initialisePlugin();
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

int RealTimeVampHost::runPlugin()
{
    string myname = "hello";


    int overlapSize = m_blockSize - m_stepSize;
    sf_count_t currentStep = 0;
    int finalStepsRemaining = max(1, (m_blockSize / m_stepSize) - 1); // at end of file, this many part-silent frames needed after we hit EOF

    int channels = m_channels;

#define READLOCAL

#ifdef READLOCAL

    SNDFILE *sndfile;
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    sndfile = sf_open("/home/dojoy/vmpt/audio/fini.wav", SFM_READ, &sfinfo);
    if (!sndfile) {
        cerr << ": ERROR: Failed to open input file " << sf_strerror(sndfile) << endl;
        throw "Error loading file ";
    }
#endif


    float *filebuf = new float[m_blockSize * channels];
    float **plugbuf = new float*[channels];
    for (int c = 0; c < channels; ++c) plugbuf[c] = new float[m_blockSize + 2];

    cerr << "Using block size = " << m_blockSize << ", step size = "
              << m_stepSize << endl;

    // The channel queries here are for informational purposes only --
    // a PluginChannelAdapter is being used automatically behind the
    // scenes, and it will take case of any channel mismatch

    int minch = m_plugin->getMinChannelCount();
    int maxch = m_plugin->getMaxChannelCount();
    cerr << "Plugin accepts " << minch << " -> " << maxch << " channel(s)" << endl;
    cerr << "Sound file has " << channels << " (will mix/augment if necessary)" << endl;

    Plugin::OutputList outputs = m_plugin->getOutputDescriptors();
    Plugin::OutputDescriptor od;

    int returnValue = 1;
    int progress = 0;

    RealTime rt;
    PluginWrapper *wrapper = 0;
    RealTime adjustment = RealTime::zeroTime;

    this->initialisePlugin();

    // Here we iterate over the frames, avoiding asking the numframes in case it's streaming input.
    do {

        int count;

        if ((m_blockSize==m_stepSize) || (currentStep==0)) {
            // read a full fresh block
#ifdef READLOCAL
            if ((count = sf_readf_float(sndfile, filebuf, m_blockSize)) < 0) {
#else
            if ((count = this->m_readFloatFunc(filebuf, m_blockSize)) < 0) {
#endif
//                cerr << "ERROR: sf_readf_float failed: " << sf_strerror(sndfile) << endl;
                throw "Read Error";
                break;
            }
            if (count != m_blockSize) --finalStepsRemaining;
        } else {
            //  otherwise shunt the existing data down and read the remainder.
            memmove(filebuf, filebuf + (m_stepSize * channels),
                    overlapSize * channels * sizeof(float));
#ifdef READLOCAL
            if ((count = sf_readf_float(sndfile, filebuf + (overlapSize * channels), m_stepSize)) < 0) {
#else
            if ((count = this->m_readFloatFunc(filebuf + (overlapSize * channels), m_stepSize)) < 0) {
#endif
                throw "Error reading float";
                break;
            }
            if (count != m_stepSize) --finalStepsRemaining;
            count += overlapSize;
        }

        for (int c = 0; c < channels; ++c) {
            int j = 0;
            while (j < count) {
                plugbuf[c][j] = filebuf[j * m_channels + c];
                ++j;
            }
            while (j < m_blockSize) {
                plugbuf[c][j] = 0.0f;
                ++j;
            }
        }

        rt = RealTime::frame2RealTime(currentStep * m_stepSize, m_inputSampleRate);

        Plugin::FeatureSet features = m_plugin->process(plugbuf, rt);

        printFeatures
            (RealTime::realTime2Frame(rt + adjustment, m_inputSampleRate),
             m_inputSampleRate, m_outputNo, features,
             m_useFrames);

        ++currentStep;

    } while (finalStepsRemaining > 0);

    cerr << "\rDone" << endl;

    rt = RealTime::frame2RealTime(currentStep * m_stepSize, m_inputSampleRate);

    cerr << flush;
    cout << flush;

    cerr << "remaining features..." << endl;

//    Plugin::FeatureSet remainingFeatures = plugin->getRemainingFeatures();
//    cerr << "remaining features: " << remainingFeatures.size() << endl;

//    printFeatures(RealTime::realTime2Frame(rt + adjustment, sfinfo.samplerate),
//                  sfinfo.samplerate, outputNo,
//                  remainingFeatures, out, useFrames);

//    cerr << "skip remaining..." << endl;
    printFeatures(RealTime::realTime2Frame(rt + adjustment, m_inputSampleRate),
        m_inputSampleRate, m_outputNo,
        m_plugin->getRemainingFeatures(), m_useFrames);

    returnValue = 0;

done:
    return returnValue;
}


void *RealTimeVampHost::process()
{
    this->runPlugin();
    return 0;

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
            // TODOJOY step 3 is getting zeros at the beginning... (only if m_channels != 1)
            memmove(readbuf, readbuf + (m_stepSize * m_channels),
                    m_overlapSize * m_channels * sizeof(float));
            if ((readCount = this->m_readFloatFunc(readbuf + (m_overlapSize * m_channels), m_stepSize)) < 0)
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

    qDebug() << "Remaining features...";

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

