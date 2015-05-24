#include <QCoreApplication>

#include <QDebug>


#include <QFile>

#include <realtimevamphost.h>

#include <sndfile.h>
#include <time.h>
#include <math.h>

#include <debughelper.h>

SNDFILE *sndfile;
int64_t readFloatSND(float *buffer, int64_t size)
{
    int64_t ret = sf_read_float(sndfile, buffer, size);
    return ret;
}

void processSndFile()
{

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    sndfile = sf_open("/home/dojoy/Music/a1.wav", SFM_READ, &sfinfo);
    if (!sndfile) {
        cerr << ": ERROR: Failed to open input file " << sf_strerror(sndfile) << endl;
        throw "Error loading file ";
    }


    RealTimeVampHost *myHost = new RealTimeVampHost("cepstral-pitchtracker",
                    "cepstral-pitchtracker", sfinfo.samplerate, sfinfo.channels, "notes", false,
                    readFloatSND);

    myHost->process();

    delete myHost;

}

QFile soundFile;

int64_t readFloatFromFile(float *buffer, int64_t size)
{
    char *cBuffer = new char[size*sizeof(float)/sizeof(char)];
    qint64 bytesRead = soundFile.read(cBuffer, size * sizeof(float)/sizeof(char));
    memcpy(buffer, cBuffer, bytesRead);

    return bytesRead  * sizeof(char) / sizeof(float);
}

//#include "debug/macros.h"
//#include "debug/functions.h"

#include "debughelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    srand(time(NULL));

    soundFile.setFileName("/home/dojoy/Music/a1.wav");
    soundFile.open(QFile::ReadOnly);

    RealTimeVampHost *myHost = new RealTimeVampHost("cepstral-pitchtracker",
                    "cepstral-pitchtracker", 44100, 1, "notes", false,
                    readFloatFromFile);


    myHost->process();

    delete myHost;

     //works... (with one channel)
    processSndFile();

    return a.exec();
}
