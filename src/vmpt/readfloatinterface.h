#ifndef READFLOATINTERFACE_H
#define READFLOATINTERFACE_H

class ReadFloatInterface
{
public:
    virtual int ReadFloat(float* buffer, int size) = 0;
};

#endif // READFLOATINTERFACE_H

