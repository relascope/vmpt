#ifndef TRANSCRIBETEST_H
#define TRANSCRIBETEST_H

#include <QtTest/QtTest>

#include <QtMath>


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
        int octave = 4; // octave of standard pitch (a)

        // 440 * 2 ^(noteabstandvona/12) = freq
        qreal c4freq = 440 * qPow(2, -9.5/12.);

        if (frequency < c4freq)
        {
            do
            {
                octave--;
                frequency *= 2.;
            } while (frequency < c4freq);

            return octave;
        }


        while (frequency > c4freq)
        {
            octave++;
            frequency /= 2.;
        }
        octave--;

        return octave;
    }

    qreal qLog2(qreal n)
    {
        return qLn(n) / qLn(2);
    }

};


#endif // TRANSCRIBETEST_H

