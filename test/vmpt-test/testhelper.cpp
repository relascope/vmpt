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

QString getOneChannelFileName()
{
    return getAudioDir().absoluteFilePath("fini1.wav");
}

QString getTwoChannelFileName()
{
    return getAudioDir().absoluteFilePath("fini2.wav");
}

