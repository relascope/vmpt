/*
   vmpt - virtual music power teacher/transcriber

   Copyright (c) 2015 www.dojoy.at, Günther Humer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SNDFILEAUDIOREADER_H
#define SNDFILEAUDIOREADER_H

#include <sndfile.hh>
#include <memory>
#include "iaudioreader.h"

class SndFileAudioReader : public IAudioReader {
public:
    static bool canReadFile(std::string fileName);
    static std::unique_ptr<SndFileAudioReader> create(std::string fileName);

    // IAudioReader interface
public:
    int readFloat(float *buffer, int size);
    AUDIO_INFO getFileInfo();
private:
    SndFileAudioReader(std::string fileName);
    SndfileHandle m_fileHandle;
};

#endif // SNDFILEAUDIOREADER_H
