#ifndef TESTHELPER_H
#define TESTHELPER_H

#include <QDir>

/**
 * @brief getAudioDir returns the directory containing audio test data
 * @return
 */
QDir getAudioDir();

QString getOneChannelFileName();

QString getTwoChannelFileName();

#endif // TESTHELPER_H

