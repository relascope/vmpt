#include "audioreaderfactory.h"

#include "sndfileaudioreader.h"
#include "rawfileaudioreader.h"

std::unique_ptr<IAudioReader>
AudioReaderFactory::create(QString fromFile) {
    if (SndFileAudioReader::canReadFile(fromFile))
        return SndFileAudioReader::create(fromFile);
    else if (RawFileAudioReader::mayReadFile(fromFile))
        return RawFileAudioReader::create(fromFile);
    else
        throw "File " + fromFile + " cannot be read.";
}
