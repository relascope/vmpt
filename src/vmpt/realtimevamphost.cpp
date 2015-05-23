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
                   int channels, QString output, bool useFrames) :
    m_libraryName(libraryName),
    m_pluginId(pluginId),
    m_inputSampleRate(inputSampleRate),
    m_channels(channels),
    m_output(output),
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

void *RealTimeVampHost::process(char *buffer, int size)
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

    for (Plugin::OutputDescriptor od : outputs)
    {
        if (od.identifier == m_output.toStdString())
        {
            m_outputDescriptor = od;
            break;
        }
    }

    if (m_outputDescriptor.identifier != m_output.toStdString())
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
}

RealTimeVampHost::~RealTimeVampHost()
{
    if (m_plugin)
        delete m_plugin;
}
