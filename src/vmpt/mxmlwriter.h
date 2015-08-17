#ifndef MXMLWRITER_H
#define MXMLWRITER_H

#include <libmusicxml/factory.h>
#include <libmusicxml/elements.h>
#include <libmusicxml/xml.h>
#include <libmusicxml/xmlfile.h>

using namespace MusicXML2;

class MXMLWriter
{
public:
    MXMLWriter(std::string fileName);
    virtual ~MXMLWriter();

    void addNote(std::string step, int octave, int duration);
    void finish();

private:
    std::string m_fileName;

    Sxmlelement score;
    Sxmlelement part;
    Sxmlelement measure;
    SXMLFile m_xmlFile;

    int positionInMeasure = 0;
    int measureCount = 1;

    double measureFill = 0;

};

#endif // MXMLWRITER_H
