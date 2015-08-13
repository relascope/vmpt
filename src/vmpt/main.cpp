#include "generatescore.h"

#include <QDebug>

#include <boost/program_options.hpp>

namespace po = boost::program_options;
using std::cout;
using std::endl;
using std::string;

void printVersion(const char *prog)
{
    cout << prog << "vmpt PeNny version 0.1" << endl;
    cout << "http://www.dojoy.at" << endl;
}

void printHelp(const char *prog, po::options_description desc)
{
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
            QString inputAudioFile = QString::fromStdString(vm["inputaudiofile"].as<string>());
            QString outputMusicXMLScoreFile = QString::fromStdString(vm["outputmusicxmlscorefile"].as<string>());

            GenerateScore().fromAudioFile(inputAudioFile).toMusicXML(outputMusicXMLScoreFile);
        } else {
            printHelp(argv[0], desc);
            return 1;
        }

        return 0;
    }
    catch (std::exception& ex)
    {
        qDebug() << "catch std::exception&";
        cout << ex.what() << endl;
    }
    catch (QString& ex)
    {
        qDebug() << "catch QString&";
        cout << ex.toStdString() << endl;
    }
    catch (std::string& ex)
    {
        qDebug() << "catch std::string&";
        cout << ex << endl;
    }
    catch (const char *ex)
    {
        qDebug() << "catch const char *";
        cout << ex << endl;
    }
    catch (...)
    {
        qDebug() << "catch ...";
        qFatal("A very bad error occured. please contact http://www.dojoy.at");
    }

    return 1;
}
