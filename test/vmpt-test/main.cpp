#include <QtTest/QtTest>

#include "testrunner.h"


#include "sndfiletest.h"
#include "sndfiletesthh.h"

#include "audiofilereadertest.h"
#include "transcribetest.h"


#include <QDebug>
int main(int argc, char **argv) {

    QCoreApplication a(argc, argv);


    TestRunner testRunner;

    testRunner.addTest(new TranscribeTest());

    testRunner.addTest(new AudioFileReaderTest());


    bool testsSucceeded = testRunner.runTests();

    qDebug() << "Overall result: " << (testsSucceeded?"====PASS====":"XXX - - - F A I L - - -XXX - - - WORK HARDER! www.dojoy.at needs YOU!");
    qDebug() << "finished!";

    return a.exec();
}
