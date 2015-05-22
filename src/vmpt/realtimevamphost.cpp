#include "realtimevamphost.h"

#include <signal.h>
#include <QDebug>


#include <string>
#include <vamp-hostsdk/PluginLoader.h>

using Vamp::HostExt::PluginLoader;

RealTimeVampHost::RealTimeVampHost(QString libraryName, QString pluginId, float inputSampleRate,
                   QString output, int outputNo, bool useFrames) :
    m_libraryName(libraryName),
    m_pluginId(pluginId),
    m_inputSampleRate(inputSampleRate),
    m_output(output),
    m_outputNo(outputNo),
    m_useFrames(useFrames)
{
    // TODOJOY Argument Checking and Error handling...
    if (m_libraryName.isNull() || m_libraryName.isEmpty())
        throw "Library name cannot be null or empty. ";
    if (m_pluginId.isNull() || m_pluginId.isEmpty())
        throw "Plugin ID cannot be null or empty. ";

    initialisePlugin();
}

void *RealTimeVampHost::finish()
{
    return 0;
}

void RealTimeVampHost::initialisePlugin()
{
    PluginLoader *loader = PluginLoader::getInstance();
    PluginLoader::PluginKey key =
            loader->composePluginKey(m_libraryName.toStdString(), m_pluginId.toStdString());

    // TODOJOY Play around if buffer works...
    int adapterFlags = PluginLoader::ADAPT_ALL;
    m_plugin = loader->loadPlugin(key, m_inputSampleRate, adapterFlags);

    if (!m_plugin)
    {
        throw "Plugin loading failed";
    }
    else
    {
        qDebug() << QString("Plugin %1 loaded successfully... ").arg(m_pluginId);
    }
}

RealTimeVampHost::~RealTimeVampHost()
{
    if (m_plugin)
        delete m_plugin;
}
