#include "sndfileallinclusive.h"
#include <string>

string getFileWithTwoChannels()
{
    return "/home/dojoy/vmpt/audio/fini.wav";
}

void Read(xReadInterface &reader)
{
//     get some data (10k)
    int size = 10000 / sizeof(float);
    float *buffer = new float[size];
    int readSize = reader.Read(buffer, size);

}

void testsndfileread()
{
    string file = getFileWithTwoChannels();

    xAudioFileReader reader(file);

    reader.opensnd();

    xMyManager man(reader);

    Read(reader);
    man.testRead();
}


void testgenericsndfileread()
{
    string file = getFileWithTwoChannels();

    QString fileInput = QString::fromStdString(file);

    xGenericAudioFileReader reader(fileInput);

    reader.opensnd();

    xMyManager man(reader);

    Read(reader);
    man.testRead();
}





bool xGenericAudioFileReader::fileExists(QString path) {

    string myPath = path.toStdString();


    QFileInfo checkFile;

    QString makeQ = QString::fromStdString(myPath);

    checkFile.setFile(makeQ);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}


xAudioFileReader::xAudioFileReader(string audioFile)
  : m_sndfile(audioFile)
{
}

int xAudioFileReader::Read(float* buffer, int size)
{
    return m_sndfile.readf(buffer, size);
}

void xAudioFileReader::opensnd()
{

    if (!m_sndfile.error()) {
        // get fileinfo
    } else {
        // report error
        cerr << m_sndfile.strError() << endl;
        throw m_sndfile.strError();
    }
}

xAudioFileReader::~xAudioFileReader()
{
    // here once was if (m_sndfile) sf_close(); // but the same errors
}


xGenericAudioFileReader::xGenericAudioFileReader(QString audioFile) :
    m_fileName(audioFile)
  , m_sndfile(audioFile.toStdString())
  , m_file(0)
{
    m_fileName = "/home/dojoy/vmpt/audio/fini2.wav";
    if (!fileExists(m_fileName))
        throw "File not found ";
}


int xGenericAudioFileReader::readRawFloat(float *buffer, int size)
{
    char* charbuff = new char[size * sizeof(float)];
    qint64 readCount = m_file->read(charbuff, size * sizeof(float));

    memcpy(buffer, charbuff, readCount);

    return readCount / sizeof(float);
}

int xGenericAudioFileReader::Read(float* buffer, int size)
{
    if (!m_file)
        return m_sndfile.readf(buffer, size);
    else
        return readRawFloat(buffer, size);
}

xGenericAudioFileReader::AUDIO_FILE_INFO xGenericAudioFileReader::opensnd()
{
    AUDIO_FILE_INFO result;

    if (!m_sndfile.error()) {
        result.channels = m_sndfile.channels();
        result.samplerate = m_sndfile.samplerate();
    } else {
        QString msg("Error loading file: ");
        msg += m_sndfile.strError();

        qDebug() << msg;
        qDebug() << "We try to read raw data... ";

        // begin to work...
        // we try to provide a fake info in the format of the recording we support
        result.channels = 1;
        result.samplerate = 44100;

        m_file = new QFile(m_fileName);
        m_file->open(QIODevice::ReadOnly);
    }

    return result;
}

xGenericAudioFileReader::~xGenericAudioFileReader()
{
    if (m_file)
    {
        if (m_file->isOpen())
            m_file->close();
        delete m_file;
    }
}


