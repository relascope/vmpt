#ifndef TESTHELPER_H
#define TESTHELPER_H

#include <QDir>

using std::string;

/**
 * @brief getAudioDir returns the directory containing audio test data
 * @return
 */
QDir getAudioDir();

string getOneChannelFileName();
string getTwoChannelFileName();

#endif // TESTHELPER_H

