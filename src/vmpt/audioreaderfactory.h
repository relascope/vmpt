#ifndef AUDIOREADERFACTORY_H
#define AUDIOREADERFACTORY_H


#include <memory>

#include "iaudioreader.h"

class AudioReaderFactory {
public:
    static std::unique_ptr<IAudioReader> create(std::string fromFile);
};
#endif // AUDIOREADERFACTORY_H
