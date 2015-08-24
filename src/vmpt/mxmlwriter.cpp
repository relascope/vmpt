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

#include "mxmlwriter.h"

#include <fstream>

#include <libmusicxml/elements.h>
#include <libmusicxml/factory.h>
#include <libmusicxml/xml.h>
#include <libmusicxml/xmlfile.h>


using namespace MusicXML2;
using std::string;

// TODO DoJoY DUPLICATE DEFINITION WITH FILETOSCORE
#define DIVISION_PER_QUARTER	4

static Sxmlattribute newAttribute(const string& name, const string& value)
{
    Sxmlattribute attribute = xmlattribute::create();
    attribute->setName(name);
    attribute->setValue(value);
    return attribute;
}

static Sxmlattribute newAttributeI(const string& name, int value)
{
    Sxmlattribute attribute = xmlattribute::create();
    attribute->setName(name);
    attribute->setValue(value);
    return attribute;
}

static Sxmlelement newElement(int type, const string& value)
{
    Sxmlelement elt = factory::instance().create(type);
    elt->setValue (value);
    return elt;
}

static Sxmlelement newElementI(int type, int value)
{
    Sxmlelement elt = factory::instance().create(type);
    elt->setValue (value);
    return elt;
}

static Sxmlelement makeMeasureAttributes() {
    Sxmlelement attributes = factory::instance().create(k_attributes);
    attributes->push (newElementI(k_divisions, DIVISION_PER_QUARTER));

    Sxmlelement time = factory::instance().create(k_time);
    time->push (newElement(k_beats, "4"));
    time->push (newElement(k_beat_type, "4"));
    attributes->push (time);

    Sxmlelement clef = factory::instance().create(k_clef);
    clef->push (newElement(k_sign, "G"));
    clef->push (newElement(k_line, "2"));
    attributes->push (clef);

    return attributes;
}

#define kPartID	"P1"

//------------------------------------------------------------------------
// creates the part list element
//------------------------------------------------------------------------
static Sxmlelement makePartList() {
    Sxmlelement partlist = factory::instance().create(k_part_list);
    Sxmlelement scorepart = factory::instance().create(k_score_part);
    scorepart->add (newAttribute("id", kPartID));
    scorepart->push (newElement(k_part_name, "Part name"));
    Sxmlelement scoreinstr = factory::instance().create(k_score_instrument);
    scoreinstr->add (newAttribute("id", "I1"));
    scoreinstr->push (newElement(k_instrument_name, "Any instr."));
    scorepart->push (scoreinstr);
    partlist->push(scorepart);
    return partlist;
}

//------------------------------------------------------------------------
// creates the identification element
//------------------------------------------------------------------------
static Sxmlelement makeIdentification() {
    Sxmlelement id = factory::instance().create(k_identification);
    Sxmlelement encoding = factory::instance().create(k_encoding);

    Sxmlelement creator = newElement(k_creator, "DoJoY VMPT, Dipl.-Ing. (FH) Günther Humer");
    creator->add(newAttribute("type", "Composer"));
    id->push (creator);

    encoding->push (newElement(k_software, "DoJoY VMPT powered by MusicXML Library v2"));
    id->push (encoding);
    return id;
}

//------------------------------------------------------------------------
// the function that creates and writes the score
//------------------------------------------------------------------------
static Sxmlelement makeScore() {
    Sxmlelement score = factory::instance().create(k_score_partwise);
    score->push (newElement(k_movement_title, "DoJoY VMPT generated music..."));
    score->push (makeIdentification());
    score->push (makePartList());

    return score;
}

MXMLWriter::MXMLWriter(std::string fileName) :
    m_fileName(fileName)
{
    m_xmlFile = TXMLFile::create();
    m_xmlFile->set(new TXMLDecl("1.0", "", TXMLDecl::kNo));
    m_xmlFile->set(new TDocType("score-partwise"));


    score = makeScore();

    part = factory::instance().create(k_part);
    part->add(newAttribute("id", kPartID));
}

void MXMLWriter::addNote(std::string step, int octave, int duration)
{
    // duration is 4 for quarter, 8 for half...
    // add measures to part...


//    int stepsPerMeasure = 4; // 4 4 per measure => 4 notes duration 4 gives 1 measure, 8 notes duration 8 gives 1 measure,

    // 4 notes duration 8 + 2 notes duration 4 gives 1 measure...

    if ((int)measureFill == 0)
    {
        measure = factory::instance().create(k_measure);
        measure->add(newAttributeI("number", measureCount));
        if (measureCount == 1)
        {
            measure->push(makeMeasureAttributes());
        }
        measureCount++;
    }

    Sxmlelement noteElem = factory::instance().create(k_note);
    Sxmlelement pitch = factory::instance().create(k_pitch);

    pitch->push(newElement(k_step, step));
    pitch->push(newElementI(k_octave, octave));

    noteElem->push(pitch);
    noteElem->push(newElementI(k_duration, duration));
//            // TODO DoJoY is this needed?
//    noteElem->push(newElement(k_type, "quarter"));

    measure->push(noteElem);

    measureFill += duration;

    // TODO DoJoY CHECK FOR DURATION OF NOTE!!! CAN IT BE ADDED? SPLIT!!

    if ((int)measureFill >= DIVISION_PER_QUARTER  * 4)
    {
        part->push(measure);
//        positionInMeasure = 0;
        measureFill = 0;
    }
}

void MXMLWriter::finish()
{
    if ((int)measureFill != 0)
        part->push(measure);

    score->push(part);			// adds a part to the score
    m_xmlFile->set(score);

    std::ofstream outStream;
    outStream.open(m_fileName.c_str());

    // TODO prints to stdout ("whitechars")...
    m_xmlFile->print(outStream);

    outStream << std::flush;
    outStream.close();
}

MXMLWriter::~MXMLWriter()
{
}

