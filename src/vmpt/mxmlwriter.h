#ifndef MXMLWRITER_H
#define MXMLWRITER_H

#include <QString>

#include<fstream>

#include <libmusicxml/elements.h>
#include <libmusicxml/factory.h>
#include <libmusicxml/xml.h>
#include <libmusicxml/xmlfile.h>

using namespace MusicXML2;

class MXMLWriter
{
public:
    MXMLWriter(QString fileName);
    virtual ~MXMLWriter();

    void addNote(QString step, int octave);
    void finish();

private:
    QString m_fileName;
    std::ofstream m_outStream;

    Sxmlelement score;
    Sxmlelement part;
    Sxmlelement measure;
    SXMLFile f;

    int positionInMeasure = 0;
    int measureCount = 1;

};

#endif // MXMLWRITER_H
