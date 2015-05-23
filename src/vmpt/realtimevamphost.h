/*
 * (c) dojoy.at, Dipl.-Ing.(FH) Günther Humer, CLYL
 *
 * */


#ifndef VAMPHOST_H
#define VAMPHOST_H

#include <QString>

#include <vamp-hostsdk/PluginLoader.h>

using namespace std;

using Vamp::Plugin;
using Vamp::RealTime;

/**
 * @brief The VampHost class
 * loads and runs the specified Vamp Plugin
 */
class RealTimeVampHost
{
public:
    RealTimeVampHost(QString libraryName, QString pluginId, float inputSampleRate, int channels, QString output, bool useFrames);

    /**
     * @brief process
     * processes the buffer with the vamp Plugin and returns the results
     * @param buffer
     * @param size
     * @return
     */
    void* process(char* buffer, int size);

    /**
     * @brief finish
     * tells the VampHost to finish the processing
     * and get Remaining Features from the plugin
     * @return
     */
    void *finish();

    virtual ~RealTimeVampHost();

protected:
    void initialisePlugin();

    QString m_libraryName;
    QString m_pluginId;

    float m_inputSampleRate;
    int m_channels;

    QString m_output;

    bool m_useFrames;

    Plugin *m_plugin;

    int m_blockSize;
    int m_stepSize;
    int m_overlapSize;

    Plugin::OutputDescriptor m_outputDescriptor;

    RealTime m_timestampAdjustment;
};

#endif // VAMPHOST_H
