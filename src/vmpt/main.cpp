#include <QCoreApplication>

#include <QDebug>


#include <QFile>
#include <QDir>

#include <realtimevamphost.h>
#include "filetoscore.h"

#include <time.h>
#include <math.h>

#include "debughelper.h"


#include <QtMath>

QDir getAudioDir()
{
    QDir appDir = QCoreApplication::applicationDirPath();

    appDir.cdUp();
    appDir.cdUp();
    appDir.cd("audio");

    return appDir;
}

int wavheadersize(QString fileName){

    char b[4];
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    file.seek(16);

    file.read(b, 4);
    file.close();

    // little endian
//    int Subchunk1Size2 = (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | (b[3]);
            // big endian??
    int Subchunk1Size = (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | (b[0]);

    if (Subchunk1Size < 16)
        throw "no valid wav file";
    else
    {
        switch (Subchunk1Size)
        {
        case 16:
            return 44;
        case 18:
            return 46;
        default:
            throw "Header contains extra data and is larger than 46 bytes";
            break;
        }
    }

    ASSERT(false)

    return 0;
}

void testOneTwoChannels()
{
    QDir audioDir = getAudioDir();

    QString file1 = audioDir.absoluteFilePath("fini1.wav");
    QString file2 = audioDir.absoluteFilePath("fini.wav");

    qDebug() << "read file with TWO channels ... ";
    SoundFile(file2).toMusicXML("/tmp/fini2.xml");

    qDebug() << "read file with ONE channel ... ";
    SoundFile(file1).toMusicXML("/tmp/fini1.xml");



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
#include <QThread>

void testRecord()
{
    InputTest audiotest;

    qDebug() << "start record ";
    audiotest.createAudioInputAndStart();

    QThread::msleep(5000);

    audiotest.stop();

    qDebug() << "stopped recording ";

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testOneTwoChannels();
    qDebug() << "test succeeded! ";


//    SoundFile().fromFile("/tmp/testfloat.raw").toMusicXML("/tmp/raw.xml");


//    testRecord();

//    SoundFile().fromMicrophone(5).toMusicXML("/tmp/mic.xml");

    return a.exec();
}
