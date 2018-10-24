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
        }
	void write(string str) {
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
        os << str << " ";
	}
	
	void startChord() {
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
		
        os << "\\chordmode { ";
		
	}	
	void finishChord(){
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
		
		os << " }";
		
        }
	void writeChord(string str) {
		if (!os.is_open()) {
			os.open(m_outputFile);
		}
        os << str << " ";
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



