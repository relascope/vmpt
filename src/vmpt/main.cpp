#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>

#include "generatescore.h"

#include "debughelper.h"

QDir getAudioDir()
{
    QDir appDir = QCoreApplication::applicationDirPath();

    appDir.cdUp();
    appDir.cdUp();
    appDir.cd("audio");

    return appDir;
}

void testOneTwoChannels()
{
    QDir audioDir = getAudioDir();

    QString file1 = audioDir.absoluteFilePath("fini1.wav");
    QString file2 = audioDir.absoluteFilePath("fini.wav");

    qDebug() << "read file with TWO channels ... ";
    GenerateScore().fromAudioFile(file2).toMusicXML("/tmp/fini2.xml");

    qDebug() << "read file with ONE channel ... ";
    GenerateScore().fromAudioFile(file1).toMusicXML("/tmp/fini1.xml");


    qDebug() << "Files read, analised and written";

    // TODOJOY ASSERT ARE IDENTICAL!!!
    // MOVE TO TEST

    QFile f1("/tmp/fini1.xml");
    QFile f2("/tmp/fini2.xml");


    f1.open(QIODevice::ReadOnly);
    f2.open(QIODevice::ReadOnly);

    QByteArray bytes1 = f1.readAll();
    QByteArray bytes2 = f2.readAll();

    ASSERT(bytes1.size() == bytes2.size())

    for (qint64 i = 0; i < bytes1.size(); i++)
    {
        if (bytes1.at(i) != bytes2.at(i))
            throw "MusicXML not equivalent for different channels ";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testOneTwoChannels();
    qDebug() << "test succeeded! ";

    GenerateScore().fromAudioFile(getAudioDir().absoluteFilePath("fini1.wav")).toMusicXML("/tmp/fini1.xml");
    GenerateScore().fromAudioFile(getAudioDir().absoluteFilePath("fini2.wav")).toMusicXML("/tmp/fini2.xml");

    qDebug() << "score generation done...";

    return a.exec();
}
