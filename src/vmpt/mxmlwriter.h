/*
   vmpt - virtual music power teacher/transcriber

   Copyright (c) 2015 www.dojoy.at, Günther Humer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
