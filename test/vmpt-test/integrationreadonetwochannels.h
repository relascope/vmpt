#ifndef INTEGRATIONREADONETWOCHANNELS
#define INTEGRATIONREADONETWOCHANNELS

#include <QtTest>
#include <QObject>
#include <QTemporaryFile>

#include "testrunner.h"

#include "generatescore.h"

#include "testhelper.h"

using std::endl;
using std::string;

class IntegrationReadOneTwoChannels
    : public QObject
{
    Q_OBJECT
private slots:
    void testReadFilesWithOneAndTwoChannelsAndCompareOutput()
    {
        string oneChannelFile = getOneChannelFileName();
        string twoChannelFile = getTwoChannelFileName();

        QTemporaryFile twoChannelScore;
        QTemporaryFile oneChannelScore;

        // open files so we can get the fileName
        oneChannelScore.open();
        twoChannelScore.open();

        GenerateScore().fromAudioFile(twoChannelFile).toMusicXML(twoChannelScore.fileName().toStdString());
        GenerateScore().fromAudioFile(oneChannelFile).toMusicXML(oneChannelScore.fileName().toStdString());

        QVERIFY2(oneChannelScore.isOpen() && oneChannelScore.isReadable(), "File is not readable!");
        QVERIFY2(twoChannelScore.isOpen() && oneChannelScore.isReadable(), "File is not readable!");

        QByteArray bytes1 = oneChannelScore.readAll();
        QByteArray bytes2 = twoChannelScore.readAll();

        QVERIFY(bytes1.size() == bytes2.size());

        QVERIFY2(bytes1.size() > 0, "no bytes written for ONE channel Score");
        QVERIFY2(bytes2.size() > 0, "no bytes written for TWO channel Score");

        for (qint64 i = 0; i < bytes1.size(); i++)
        {
            QVERIFY2(bytes1.at(i) == bytes2.at(i), "Result file not identical!");
        }
    }
};

DECLARE_TEST(IntegrationReadOneTwoChannels)

#endif // INTEGRATIONREADONETWOCHANNELS

