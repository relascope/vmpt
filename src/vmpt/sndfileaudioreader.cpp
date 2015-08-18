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

#include "sndfileaudioreader.h"

#include <iostream>
#include <string.h>

SndFileAudioReader::SndFileAudioReader(std::string fileName)
    : m_fileHandle(fileName)
{
}

bool
SndFileAudioReader::canReadFile(std::string fileName)
{
    SndfileHandle handle(fileName);

    if (handle.error())
    {
        return false;
    }

    return true;
}

std::unique_ptr<SndFileAudioReader>
SndFileAudioReader::create(std::string fileName)
{
    if (!canReadFile(fileName))
    {
        std::string msg("SndFileReader cannot read file: ");
        msg += fileName;
        std::cerr << msg;
        throw msg;
    }

    return std::unique_ptr<SndFileAudioReader>(new SndFileAudioReader(fileName));
}

// IAudioReader interface
int
SndFileAudioReader::readFloat(float *buffer, int size) {
    return m_fileHandle.readf(buffer, size);
}

IAudioReader::AUDIO_INFO
SndFileAudioReader::getFileInfo()
{
    AUDIO_INFO result;
    memset(&result, 0, sizeof(AUDIO_INFO));

    result.channels = m_fileHandle.channels();
    result.samplerate = m_fileHandle.samplerate();

    return result;
}
