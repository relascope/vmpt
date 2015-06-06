#include "debughelper.h"

#include <QDebug>
#include <QTimer>


//const int BufferSize = 4096;

//InputTest::InputTest() :
//    m_device(QAudioDeviceInfo::defaultInputDevice()),
//    m_buffer(BufferSize, 0)
//{
//    m_pullMode = true;

//    m_format.setSampleRate(44100);
//    m_format.setChannelCount(1);
//    m_format.setSampleSize(32);
////    m_format.setSampleType(QAudioFormat::SignedInt);
//    m_format.setSampleType(QAudioFormat::Float);
//    m_format.setByteOrder(QAudioFormat::LittleEndian);
//    m_format.setCodec("audio/pcm");

//    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());

//    qDebug() << "default device: " << info.deviceName();

//    if (!info.isFormatSupported(m_format)) {
//        qWarning() << "Default format not supported - trying to use nearest";
//        m_format = info.nearestFormat(m_format);
//    }

//    m_audioInfo  = new AudioInfo(m_format, "/tmp/testfloat.raw", this);
//}

//void InputTest::stop()
//{
//    if (m_audioInput)
//    {
//        m_audioInput->stop();
//        delete m_audioInput;
//        m_audioInput = 0;
//    }

//    if (m_audioInfo)
//    {
//        m_audioInfo->stop();
//        delete m_audioInfo;
//        m_audioInfo = 0;
//    }

//    if (m_input)
//    {
//        if (m_input->isOpen())
//            m_input->close();

//        delete m_input;
//        m_input = 0;
//    }
//}

//void InputTest::createAudioInputAndStart()
//{
//    m_audioInput = new QAudioInput(m_device, m_format, this);
//    m_audioInfo->start();

//    m_audioInput->start(m_audioInfo);

////    QTimer *timer = new QTimer(this);
////    ASSERT(connect(timer, SIGNAL(timeout()), this, SLOT(stop())));

////    timer->start(5000);
//}

//void InputTest::readMore()
//{
//    if (!m_audioInput)
//        return;
//    qint64 len = m_audioInput->bytesReady();

//    qDebug() << "bytes ready: " << len;

//    if (len > BufferSize)
//        len = BufferSize;

//    qint64 l = m_input->read(m_buffer.data(), len);

//    qDebug() << "bytes read: " << l << endl;

//    if (l > 0)
//        m_audioInfo->write(m_buffer.constData(), l);
//}



//AudioInfo::AudioInfo(const QAudioFormat &format, QString fileToWrite, QObject *parent)
//    :   QIODevice(parent)
//    ,   m_format(format)
//    ,   m_maxAmplitude(0)
//    ,   m_level(0.0)
//    ,   m_running(false)

//{
//    if (fileToWrite.isEmpty() || fileToWrite.isNull())
//        m_writeFile = false;
//    else
//    {
//        m_File.setFileName(fileToWrite);
//        m_writeFile = true;
//    }
//}

//AudioInfo::~AudioInfo()
//{
//    if (m_File.isOpen())
//        m_File.close();
//}

//void AudioInfo::start()
//{
//    m_running = true;

//    if (m_writeFile)
//    {
//        m_File.open(QFile::WriteOnly);
//    }

//    open(QIODevice::WriteOnly);
//}

//void AudioInfo::stop()
//{
//    if (m_File.isOpen())
//        m_File.close();

//    close();

//    m_running = false;
//}

//qint64 AudioInfo::readData(char *data, qint64 maxlen)
//{
//    Q_UNUSED(data)
//    Q_UNUSED(maxlen)

//    return 0;
//}

//qint64 AudioInfo::writeData(const char *data, qint64 len)
//{

//    // here we get our data...

//    if (m_writeFile)
//        m_File.write(data, len);

//    // now begins the hard work.
//    // assemble the data for our VAMP-Plugin

//    // done in separate step!!
//    // we try to do it reverse way???

//    qint64 bytesWritten = m_data.write(data, len);

//    if (bytesWritten != len)
//    {
//        qDebug() << "could not store all data...";
//    }

//    return len;
//}


//int AudioInfo::ReadFloat(float *buffer, int size)
//{
////    int bytesReady = m_data.bytesAvailable();

////    while (size * 4 > bytesReady && m_running)
////    {
////        // wait
//////        QThread::msleep(10);
////        QTimer t;
////        t.setSingleShot(true);
////        t.start(10);

////        bytesReady = m_data.bytesAvailable();
////    }

//    int bytesRead = 0;

////    bytesRead = m_data.read(reinterpret_cast<char*>(buffer), size*4);

//    return bytesRead;
//}


