VMPT virtual music power transcriber/teacher
================================================
VMPT PeNny notates music notes from an audio file. 
The file can be saved and viewed in common Notation Programs. 
Most Audio Files are supported. 

Dependencies
================================================
 * QT5.4 (https://www.qt.io/download/)
 * vamp-hostsdk (http://www.vamp-plugins.org/develop.html)
 * pYIN (probablistic YIN) - Centre for Digital Music, Queen Mary, University of London, GPL
 * sndfile (http://www.mega-nerd.com/libsndfile/)
 * libmusicxml (https://code.google.com/p/libmusicxml/)
 * libboost-program-options-dev (http://www.boost.org)

sudo apt-get install build-essential libsndfile1-dev libvamp-hostsdk3

QT
download community edition and follow setup instructions. 

libMusicXML
get the code and follow setup instruction

Cepstral Pitch Tracker
copy the library (.so, .dll) to $HOME/vamp/ (create directory if needed)


OR JUST USE THIS SCRIPT
(it will install packages and build dependencies)
Run from a directory where it is OK to place some code. 
It will get everything up and running 
(it's the same that runs on the build-server)


echo Installing/Building dependencies
sudo apt-get update
sudo apt-get --yes --force-yes install build-essential git
sudo apt-get --yes --force-yes install cmake
echo getting/building libmusicxml
mkdir libmusicxml || true
cd libmusicxml
git clone https://code.google.com/p/libmusicxml/ . || git pull
cd cmake
cmake .
make
sudo make install
cd ..
cd ..
echo getting/building pYIN
sudo apt-get --yes --force-yes install libboost-all-dev vamp-plugin-sdk mercurial
mkdir pYIN || true
cd pYIN
hg clone https://code.soundsoftware.ac.uk/hg/pyin . || hg update
make -f Makefile.linux64
mkdir ~/vamp
cp pyin.so ~/vamp/
cd ..
echo finnally installing vmpt
sudo apt-get --yes --force-yes install libsndfile1-dev libvamp-hostsdk3 qtbase5-dev 
#may not be needed later (QCommandlineParser!)
sudo apt-get --yes --force-yes install libboost-program-options-dev
#may be needed sometime... (Microphone)
#sudo apt-get --yes --force-yes install qtmultimedia5-dev qtmobility-dev



#VMPT
echo building VMPT
cd ./src/vmpt
QT_SELECT=5 qmake
QT_SELECT=5 make

#Tests
echo building tests
cd ..
cd ..
cd test
cd vmpt-test
QT_SELECT=5 qmake
QT_SELECT=5 make

#run tests
echo running tests
./vmpt-test



Build
------------------------------------------------
(git clone)

cd vmpt
cd src
cd vmpt
QT_SELECT=5 qmake
QT_SELECT=5 make

RUN
./vmpt

Copyright 2015 Günther Humer
================================================
VMPT is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.  See the file COPYING included with
this distribution for more information. 
