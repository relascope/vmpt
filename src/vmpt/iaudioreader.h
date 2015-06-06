#ifndef IAUDIOREADER_H
#define IAUDIOREADER_H

/**
 * @brief The IAudioReader Interface
 * defines functions for reading float audio data
 * each class must provide AUDIO_INFO about the source
 */
class IAudioReader {
public:
    virtual int readFloat(float* buffer, int size) = 0;

    typedef struct {
        int channels;
        int samplerate;
    } AUDIO_INFO;

    // TODO DOJOY rename to... getAudioInfo
    virtual AUDIO_INFO getFileInfo() = 0;
    virtual ~IAudioReader() {}
};

#endif // IAUDIOREADER_H
