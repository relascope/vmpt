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

/**
 * @brief The VampHost class
 * loads and runs the specified Vamp Plugin
 */
class RealTimeVampHost
{
public:
    RealTimeVampHost(QString libraryName, QString pluginId, float inputSampleRate, QString output, int outputNo, bool useFrames);

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

    QString m_output;

    int m_outputNo;
    bool m_useFrames;

    Plugin *m_plugin;
};

#endif // VAMPHOST_H
