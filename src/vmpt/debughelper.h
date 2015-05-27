#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H


#ifdef __GNUC__
#define DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED
#endif

// TODOJOY works only on linux!!!
#include <signal.h>
#define ASSERT(TEST) if(!(TEST)) raise(SIGTRAP);


#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QCoreApplication>




#include <QAudioInput>
#include <QByteArray>
#include <QObject>


#include <QFile>


#include <QBuffer>


#include "readfloatinterface.h"

class AudioInfo : public QIODevice,
        public ReadFloatInterface
{
    Q_OBJECT

public:
    AudioInfo(const QAudioFormat &format, QString fileToWrite = "", QObject *parent = 0);
    ~AudioInfo();

    void start();
    void stop();

    qreal level() const { return m_level; }

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

    // ReadFloatInterface interface
public:
    int ReadFloat(float *buffer, int size);

private:
    const QAudioFormat m_format;
    quint32 m_maxAmplitude;
    qreal m_level; // 0.0 <= m_level <= 1.0

    QString m_fileToWrite;
    bool m_writeFile;
    QFile m_File;

    QBuffer m_data;

    bool m_running;
signals:
    void update();

};



class InputTest : public QObject
{
    Q_OBJECT
public:
    InputTest();
    void createAudioInputAndStart();

    ReadFloatInterface *getReader() {return m_audioInfo;}
public slots:
    void stop();
private:
    bool m_pullMode;

    QAudioFormat m_format;

    AudioInfo *m_audioInfo;

    QAudioInput *m_audioInput;

    QAudioDeviceInfo m_device;

    void readMore();

    int BufferSize;

    QIODevice *m_input;
    QByteArray m_buffer;
};








class DebugHelper
{
public:

    void assertFileIsOpen()
    {
        if (!m_outputFile.isOpen())
        {
            QDateTime time = QDateTime::currentDateTime();
            QString appName = QFileInfo( QCoreApplication::applicationFilePath() ).fileName();
            QString fileName = "/tmp/" + time.toString("YYYY-MM-dd-HH-mm-ss") + "_" + appName;

            m_outputFile.setFileName(fileName);

            m_outputFile.open(QFile::WriteOnly | QFile::Text);

            Q_ASSERT(m_outputFile.isOpen() && m_outputFile.isWritable());
        }
    }

    void printFloat(float val)
    {
        QString strVal;
        strVal.setNum(val);
        printToFile(strVal.toStdString().c_str());
    }

    void printFloatArray(float* buffer, int64_t size)
    {
        for (int64_t i = 0; i < size; i++)
        {
            printFloat(buffer[i]);
            printToFile("|");
        }
    }

    void printToFile(const char* val)
    {
        assertFileIsOpen();
        m_outputFile.write(val);
    }

    static DebugHelper *instance()
    {
        static DebugHelper *m_instance;
        if (m_instance == 0)
        {
            m_instance = new DebugHelper();
        }

        return m_instance;
    }

private:
    QFile m_outputFile;

    DebugHelper() {}
};


#endif // DEBUGHELPER_H

