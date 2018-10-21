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

#ifndef FILETOSCORE_H
#define FILETOSCORE_H

#include <vamp-hostsdk/RealTime.h>
#include <vamp-hostsdk/Plugin.h>

using Vamp::Plugin;
using std::string;

#include <fstream>
#include <string>
#include <iostream>

//TODO
using namespace std;

class MusicWriter;

class MusicWriter {
public:
	void start() {
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
		
		os << "{ ";
		
	}	
	void finish(){
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
		
		os << " }";		
		};
	void write(string str) {
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
		os << str;
	}
	
	void startChord() {
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
		
		os << "\chordmode { ";
		
	}	
	void finishChord(){
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
		
		os << " }";
		
		};
	void writeChord(string str) {
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
		os << " " << str << " ";
	 }
		
	
	
	void setFile(string outputFile) {this->m_outputFile = outputFile;}
	virtual ~MusicWriter() {
		if (os.is_open()) {
			os.close();
		}
	}
protected:
	ofstream os;
	string m_outputFile;
};




// TODO DoJoY Better description
class GenerateScore
{
public:
    GenerateScore(string outputScore);
    void fromAudio(string inputAudio);
    GenerateScore();
    virtual ~GenerateScore();


private:
	void collectChords(Plugin::FeatureList * features);
    void collectFeatures(Plugin::FeatureList *features);
    void writeNoteToScore(float val, Vamp::RealTime duration, Vamp::RealTime timestamp);
    void writeChordToScore(string label, Vamp::RealTime timestamp);


    string m_outputScore;
    MusicWriter *m_writer;    
};

#endif // FILETOSCORE_H
