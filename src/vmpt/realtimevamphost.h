/*
 * (c) dojoy.at, Dipl.-Ing.(FH) Günther Humer, CLYL
 *
 * */


#ifndef VAMPHOST_H
#define VAMPHOST_H

#include <QString>

#include <vamp-hostsdk/PluginLoader.h>

#include <functional>

using namespace std;

using Vamp::Plugin;
using Vamp::RealTime;

//typedef int64_t (*cbReadFloat)(float*,int64_t);

using namespace std::placeholders;
typedef std::function<int(float*,int)> cbReadFloat;

// TODOJOY Qt Signal/Slot?
//typedef void (*cbFeaturesAvailable)(Plugin::FeatureList* features);

typedef std::function<void(Plugin::FeatureList* features)> cbFeaturesAvailable;

class ReadInterface
{
public:
    virtual int ReadFloat(float* buffer, int size) = 0;
};

/**
 * @brief The VampHost class
 * loads and runs the specified Vamp Plugin
 */
class RealTimeVampHost
{
public:
    RealTimeVampHost(QString libraryName, QString pluginId,
                     float inputSampleRate, int channels,
                     QString output, bool useFrames,
                     cbReadFloat readFloatFunc);

    /**
     * @brief process
     * processes the buffer with the vamp Plugin and returns the results
     * @param buffer
     * @param size
     * @return
     */
    void* process();

    virtual ~RealTimeVampHost();

    cbFeaturesAvailable featuresAvailable;

    ReadInterface *m_reader;

protected:
    void initialisePlugin();

    QString m_libraryName;
    QString m_pluginId;

    float m_inputSampleRate;
    int m_channels;

    QString m_output;

    bool m_useFrames;

    cbReadFloat m_readFloatFunc;

    Plugin *m_plugin;

    int m_blockSize;
    int m_stepSize;
    int m_overlapSize;

    int m_outputNo;

    RealTime m_timestampAdjustment;
private:
    int runPlugin();

};

#endif // VAMPHOST_H
