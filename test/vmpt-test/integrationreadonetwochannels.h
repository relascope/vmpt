#ifndef INTEGRATIONREADONETWOCHANNELS
#define INTEGRATIONREADONETWOCHANNELS

#include <QtTest>
#include <QObject>
#include <QTemporaryFile>

#include "testrunner.h"

#include "generatescore.h"
#include "debughelper.h"
#include "helpers.h"

#include "testhelper.h"

using std::endl;

class IntegrationReadOneTwoChannels
    : public QObject
{
    Q_OBJECT
private slots:
    void testOneTwoChannels()
    {
        QString oneChannelFile = getOneChannelFileName();
        QString twoChannelFile = getTwoChannelFileName();

        QTemporaryFile twoChannelScore;
        QTemporaryFile oneChannelScore;

        // open files so we can get the fileName
        oneChannelScore.open();
        twoChannelScore.open();

        qStdOut() << "read file with TWO channels and generating score... " << endl;
        GenerateScore().fromAudioFile(twoChannelFile).toMusicXML(twoChannelScore.fileName());

        qStdOut() << "read file with ONE channel and generating score... " << endl;
        GenerateScore().fromAudioFile(oneChannelFile).toMusicXML(oneChannelScore.fileName());

        QVERIFY2(oneChannelScore.isOpen() && oneChannelScore.isReadable(), "File is not readable!");
        QVERIFY2(twoChannelScore.isOpen() && oneChannelScore.isReadable(), "File is not readable!");

        QByteArray bytes1 = oneChannelScore.readAll();
        QByteArray bytes2 = twoChannelScore.readAll();

        ASSERT(bytes1.size() == bytes2.size())

        for (qint64 i = 0; i < bytes1.size(); i++)
        {
            QVERIFY2(bytes1.at(i) == bytes2.at(i), "Result file not identical!");
        }
    }
};

DECLARE_TEST(IntegrationReadOneTwoChannels)

#endif // INTEGRATIONREADONETWOCHANNELS

