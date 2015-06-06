/*
 * (c) dojoy.at, Dipl.-Ing.(FH) Günther Humer, CLYL
 *
 * */


#ifndef VAMPHOST_H
#define VAMPHOST_H

#include <vamp-hostsdk/PluginLoader.h>

#include <functional>

#include <QString>

#include "iaudioreader.h"
#include "debughelper.h"

using Vamp::Plugin;
using Vamp::RealTime;

using namespace std::placeholders;

typedef std::function<void(Plugin::FeatureList* features)> cbFeaturesAvailable;

/**
 * @brief The VampHost class
 * loads and runs the specified Vamp Plugin
 */
class RealTimeVampHost
{
    // TODO DoJoY eventually refactor /output to a new constructor
    // or property
    // TODO DoJoY useFrames default to false and a setter.
public:
    RealTimeVampHost(QString libraryName, QString pluginId,
                     QString output, bool useFrames,
                     IAudioReader& reader);
    virtual ~RealTimeVampHost();

    /**
     * @brief process
     * processes the data read from the given reader
     * and gives the results to the featuresAvailable callback
     */
    void process();

    cbFeaturesAvailable featuresAvailable;

protected:
    void initialisePlugin();

    QString m_libraryName;
    QString m_pluginId;

    float m_inputSampleRate;
    int m_channels;

    QString m_output;

    bool m_useFrames;

    IAudioReader& m_reader;
private:
    Plugin *m_plugin;

    int m_blockSize;
    int m_stepSize;
    int m_overlapSize;

    int m_outputNo;

    RealTime m_timestampAdjustment;

private:
    /**
      * FROM VAMP-HOSTSDK HOST EXAMPLE
      */
    void printFeatures(int frame, int sr, int output,
                  Plugin::FeatureSet features, bool useFrames);

};

#endif // VAMPHOST_H
