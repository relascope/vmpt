#include <QCoreApplication>

#include <QDebug>


#include <QFile>

#include <realtimevamphost.h>

#include <sndfile.h>
#include <time.h>
#include <math.h>


SNDFILE *sndfile;
int readFloatSND(float *buffer, int size)
{
    return sf_read_float(sndfile, buffer, size);
}

void processSndFile()
{

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    sndfile = sf_open("/home/dojoy/Music/allemeineentlein.wav", SFM_READ, &sfinfo);
    if (!sndfile) {
        cerr << ": ERROR: Failed to open input file " << sf_strerror(sndfile) << endl;
        throw "Error loading file ";
    }


    RealTimeVampHost *myHost = new RealTimeVampHost("pyin",
                    "pyin", sfinfo.samplerate, sfinfo.channels, "notes", false,
                    readFloatSND);

    myHost->process();
    myHost->finish();

    delete myHost;

}

int readFloat(float *buffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        buffer[i] = r;
    }

    // size adjusting!!! read should read frames or so...
    return size;
}

QFile soundFile;

int readFloatFromFile(float *buffer, int size)
{
    char *cBuffer = new char[size*sizeof(float)/sizeof(char)];
    qint64 bytesRead = soundFile.read(cBuffer, size * sizeof(float)/sizeof(char));
    memcpy(buffer, cBuffer, bytesRead);

    return bytesRead  * sizeof(char) / sizeof(float);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    srand(time(NULL));

//    soundFile.setFileName("/home/dojoy/Music/allemeineentleinGuitar.wav");
//    soundFile.open(QFile::ReadOnly);

//    RealTimeVampHost *myHost = new RealTimeVampHost("pyin",
//                    "pyin", 44100, 2, "notes", false,
//                    readFloatFromFile);

//    myHost->process();
//    myHost->finish();

//    delete myHost;

     works...
    processSndFile();

    return a.exec();
}
