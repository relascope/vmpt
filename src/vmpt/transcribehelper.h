#ifndef TRANSCRIBEHELPER_H
#define TRANSCRIBEHELPER_H

#include <QString>

class TranscribeHelper
{
public:
    TranscribeHelper();

    void setStandardPitch(float standardPitch) { m_standardPitch = standardPitch; }

    QString getNoteFromFreq(float val);

private:
    QString getNoteName(int roundedLevel);
    static qreal qLog2(qreal n);

private:
    float m_standardPitch = 440;
};

#endif // TRANSCRIBEHELPER_H
