#include "debughelper.h"


int reader::nonstat(float* buffer, int size)

{
    return sf_readf_float(m_sndfiletmp, buffer, size);
}

void reader::opensnd()
{
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    m_sndfiletmp = sf_open("/home/dojoy/vmpt/audio/fini.wav", SFM_READ, &sfinfo);
    if (!m_sndfiletmp) {
        throw "Error loading file ";
    }
}
