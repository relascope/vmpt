#include "audioreaderfactory.h"

#include "sndfileaudioreader.h"
#include "rawfileaudioreader.h"

std::unique_ptr<IAudioReader>
AudioReaderFactory::create(QString fromFile) {
    if (SndFileAudioReader::canReadFile(fromFile))
        return SndFileAudioReader::create(fromFile);
    else
        return RawFileAudioReader::create(fromFile);
}
