#include "audioreaderfactory.h"

#include "sndfileaudioreader.h"

std::unique_ptr<IAudioReader>
AudioReaderFactory::create(std::string fromFile) {
    if (SndFileAudioReader::canReadFile(fromFile))
        return SndFileAudioReader::create(fromFile);
    else
        throw std::string("File ") + fromFile + " cannot be read.";
}
