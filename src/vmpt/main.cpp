#include "generatescore.h"

#include <boost/program_options.hpp>

namespace po = boost::program_options;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
    po::options_description desc("Allowed options");

    desc.add_options()
            ("help", "produce help message")
            ("version,v", "print version string")
            ("inputaudiofile,i", po::value<string>(), "audio input file")
            ("outputmusicxmlscorefile,o", po::value<string>(), "music xml score output file")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }

    if (vm.count("version")) {
        cout << "Version not defined... call Petra!" << endl;
        return 1;
    }

    if (vm.count("inputaudiofile") && vm.count("outputmusicxmlscorefile")) {
        QString inputAudioFile = QString::fromStdString(vm["inputaudiofile"].as<string>());
        QString outputMusicXMLScoreFile = QString::fromStdString(vm["outputmusicxmlscorefile"].as<string>());

        GenerateScore().fromAudioFile(inputAudioFile).toMusicXML(outputMusicXMLScoreFile);
    } else {
        cout << desc << endl;
        return 1;
    }

    return 0;
}
