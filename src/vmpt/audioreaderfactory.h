#ifndef AUDIOREADERFACTORY_H
#define AUDIOREADERFACTORY_H


#include <memory>

#include <QString>

#include "iaudioreader.h"

class AudioReaderFactory {
public:
    static std::unique_ptr<IAudioReader> create(QString fromFile);
};
#endif // AUDIOREADERFACTORY_H
