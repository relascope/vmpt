#include <QCoreApplication>

#include <QDebug>


#include <QFile>

#include <realtimevamphost.h>
#include "filetoscore.h"

#include <time.h>
#include <math.h>

#include <debughelper.h>


#include <QtMath>

QFile soundFile;

int64_t readFloatFromFile(float *buffer, int64_t size)
{
    char *cBuffer = new char[size*sizeof(float)/sizeof(char)];
    qint64 bytesRead = soundFile.read(cBuffer, size * sizeof(float)/sizeof(char));
    memcpy(buffer, cBuffer, bytesRead);

    throw "reads shit";

    return bytesRead  * sizeof(char) / sizeof(float);
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

void readWavDirect()
{
//    soundFile.setFileName("/home/dojoy/Music/a1.wav");

    QString fileName = "/home/dojoy/Music/cats1.wav";

    int wavHeaderInBytes = wavheadersize(fileName);

    soundFile.setFileName(fileName);
    soundFile.open(QFile::ReadOnly);

    soundFile.read(wavHeaderInBytes); // read header to not be mixed with our data ;-)

    RealTimeVampHost *myHost = new RealTimeVampHost("cepstral-pitchtracker",
                    "cepstral-pitchtracker", 44100, 1, "notes", false,
                    readFloatFromFile);

    myHost->process();
    delete myHost;

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    readWavDirect();

    FileToScore().processSndFile("/home/dojoy/vmpt/audio/fini.wav", "/tmp/fini.xml");


    return a.exec();
}
