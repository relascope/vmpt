#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

// TODOJOY works only on linux!!!
#include <signal.h>
#define ASSERT(TEST) if(!(TEST)) raise(SIGSTOP);


#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QCoreApplication>


#include <sndfile.h>
class reader
{
public:
    reader() {opensnd();}

//    static int stat(float* buffer, int size)

//    {
//        return sf_readf_float(sndfiletmp, buffer, size);
//    }

    int nonstat(float* buffer, int size);


    SNDFILE *m_sndfiletmp;

    void opensnd();
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

