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

#include "generatescore.h"

#include <cstring>

using std::cout;
using std::endl;
using std::string;

void printVersion(const char *prog)
{
    cout << endl << prog << " - virtual music power transcriber" << endl;
    cout << "PeNny version 2.0 notates audio files to leadsheats" << endl;
    cout << "including melody and chords. " << endl << endl;
    cout << "Copyright (c) 2015 www.dojoy.at, Günther Humer" << endl << endl;
}

void usage(const char *name) {
    printVersion(name);
    cout << endl << "Usage: " << endl << endl;
    cout << name << " InputAudioFile OutputMusicXmlScoreFile" << endl;
    cout << " InputAudioFile             audio input file" << endl;
    cout << " OutputMusicXmlScoreFile    MusicXML score output file" << endl;
    cout << " -h [--help]                This help" << endl;
    cout << " -v [--version]             Version Information" << endl << endl;
    exit(2);
}

int main(int argc, char *argv[])
{
    // TODO DoJoY bad style to catch them all here...
    try
    {

        char *scooter = argv[0];
        char *name = 0;
        while (scooter && *scooter) {
            if (*scooter == '/' || *scooter == '\\') name = ++scooter;
            else ++scooter;
        }
        if (!name || !*name) name = argv[0];

        if (argc < 2) usage(name);

        if (argc == 2) {
            if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
                printVersion(name);
                return 0;
            } else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
                usage(name);
                return 0;
            } else {
                usage(name);
                return 0;
            }
        }

        if (argc < 3) {
            usage(name);
            return 0;
        }

        if (argc == 3) {
            string inputAudioFile = argv[1];
            string outputMusicScoreFile = argv[2];


	    GenerateScore(outputMusicScoreFile).fromAudio(inputAudioFile);
        } else {
            usage(name);
            return 1;
        }

        return 0;
    }
    catch (std::exception& ex)
    {
        std::cerr << "PeNny got stuck: ---catch std::exception&---" << std::endl;
        std::cerr << ex.what() << endl;
    }
    catch (std::string& ex)
    {
        std::cerr << "PeNny got stuck: ---catch std::string&---" << std::endl;
        std::cerr << ex << endl;
    }
    catch (const char *ex)
    {
        std::cerr << "PeNny got stuck: ---catch const char *---" << std::endl;
        std::cerr << ex << endl;
    }
    catch (...)
    {
        std::cerr << "PeNny got stuck: ---catch ... ---" << std::endl;
        std::cerr << "A very bad error occured. please contact http://www.dojoy.at" << std::endl;
    }

    return 1;
}
