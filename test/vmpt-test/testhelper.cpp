#include "testhelper.h"

#include <QCoreApplication>

QDir getAudioDir()
{
    QDir appDir = QCoreApplication::applicationDirPath();

    appDir.cdUp();
    appDir.cdUp();
    appDir.cd("audio");

    return appDir;
}

string getOneChannelFileName()
{
    return getAudioDir().absoluteFilePath("fini1.wav").toStdString();
}

string getTwoChannelFileName()
{
    return getAudioDir().absoluteFilePath("fini2.wav").toStdString();
}

