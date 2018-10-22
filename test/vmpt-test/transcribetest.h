#ifndef TRANSCRIBETEST_H
#define TRANSCRIBETEST_H

#include <QtTest/QtTest>

//#include <QtMath>

#include "testrunner.h"

#include "transcribehelper.h"

/**
 * @brief The TranscribeTest class
 * Octave must be consistent with note finding
 * otherwise a frequence could be an b and
 * the octave find a "c" and put it in another
 */
class TranscribeTest : public QObject
{
    Q_OBJECT

private slots:
    /**
     * @brief testOctave
     * standard pitch for this test is expected to be 440Hz
     */
    void testOctave()
    {
        // compare a's
        QCOMPARE(getOctave(440), 4);

        QCOMPARE(getOctave(880), 5);
        QCOMPARE(getOctave(220), 3);

        QCOMPARE(getOctave(1760), 6);
        QCOMPARE(getOctave(110), 2);

        // compare c's
        QCOMPARE(getOctave(523.2511), 5);
        QCOMPARE(getOctave(1046.5022), 6);

        QCOMPARE(getOctave(261.6256), 4);
        QCOMPARE(getOctave(130.81), 3);
    }

private:
    int getOctave(float frequency)
    {
        return TranscribeHelper().getOctaveFromFreq(frequency);
    }
};

DECLARE_TEST(TranscribeTest)

#endif // TRANSCRIBETEST_H

