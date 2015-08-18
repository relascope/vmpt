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

#include <boost/program_options.hpp>

namespace po = boost::program_options;
using std::cout;
using std::endl;
using std::string;

void printVersion(const char *prog)
{
    cout << prog << "PeNny version 0.1" << endl;
    cout << "(c) Günther Humer" << endl;
    cout << "http://www.dojoy.at" << endl;
}

void printHelp(const char *prog, po::options_description desc)
{
    printVersion(prog);
    cout << "Usage: " << prog << " InputAudioFile OutputMusicXmlScoreFile" << endl;
    cout << desc << endl;
}

int main(int argc, char *argv[])
{
    // TODO DoJoY bad style to catch them all here...
    try
    {
        // TODO DoJoY QCommandlineParser could be used... our framework...
        po::options_description desc("Allowed options");

        desc.add_options()
                ("inputaudiofile,i", po::value<string>(), "audio input file")
                ("outputmusicxmlscorefile,o", po::value<string>(), "music xml score output file")
                ("help,h", "produce help message")
                ("version,v", "print version string")
                ;

        po::positional_options_description posopt;
        posopt.add("inputaudiofile", 1);
        posopt.add("outputmusicxmlscorefile", 1);


        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).
                  options(desc).positional(posopt).run(), vm);

        po::notify(vm);

        if (vm.count("help")) {
            printHelp(argv[0], desc);
            return 1;
        }

        if (vm.count("version")) {
            printVersion(argv[0]);
            return 1;
        }

        if (vm.count("inputaudiofile") && vm.count("outputmusicxmlscorefile")) {
            string inputAudioFile = vm["inputaudiofile"].as<string>();
            string outputMusicXMLScoreFile = vm["outputmusicxmlscorefile"].as<string>();

            GenerateScore().fromAudioFile(inputAudioFile).toMusicXML(outputMusicXMLScoreFile);
        } else {
            printHelp(argv[0], desc);
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
