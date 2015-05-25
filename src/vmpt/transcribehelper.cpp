#include "transcribehelper.h"

#include <QtMath>
#include <QStringList>

TranscribeHelper::TranscribeHelper()
{

}

qreal TranscribeHelper::qLog2(qreal n)
{
    return qLn(n) / qLn(2);
}

QString TranscribeHelper::getNoteName(int roundedLevel)
{
    // level ranges from A=440(e.g.) up and down. every step is a half tone...

    QStringList listNotes;

//    listNotes << "a" << "ais" << "b" << "c" << "cis" << "d" << "dis" << "e" << "f" << "fis" << "g" << "gis";
    listNotes << "A" << "A" << "B" << "C" << "C" << "D" << "D" << "E" << "F" << "F" << "G" << "G";

    int realLevel = roundedLevel % 12;

    if (realLevel < 0) realLevel += 12;

    return listNotes[realLevel];
}

QString TranscribeHelper::getNoteFromFreq(float val)
{
    // freq = 440 * 2 ^ i/12

    // 12 * log2(freq/440) = level

    qreal level = 12 * qLog2(val/440.);

    int roundedLevel = qRound(level);

    QString noteName = getNoteName(roundedLevel);

    return noteName;
}
