VMPT - virtual music power transcriber (teacher)
================================================
transcribes music (from audio) to MusicXML




Dependencies
------------------------------------------------
 * QT5.4 (https://www.qt.io/download/)
 * vamp-hostsdk (http://www.vamp-plugins.org/develop.html)
 * Cepstral Pitch Tracker (https://code.soundsoftware.ac.uk/projects/cepstral-pitchtracker)
 * sndfile (http://www.mega-nerd.com/libsndfile/)
 * libmusicxml (https://code.google.com/p/libmusicxml/)

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
echo getting/building cepstral-pitchtracker
sudo apt-get --yes --force-yes install libboost-all-dev vamp-plugin-sdk mercurial
mkdir cepstral-pitchtracker || true
cd cepstral-pitchtracker
hg clone https://code.soundsoftware.ac.uk/hg/cepstral-pitchtracker . || hg update
make -f Makefile.linux64
mkdir ~/vamp
cp cepstral-pitchtracker.so ~/vamp/
cd ..
echo finnally installing vmpt
sudo apt-get --yes --force-yes install libsndfile1-dev libvamp-hostsdk3 qtbase5-dev qtmultimedia5-dev

cd ./src/vmpt
QT_SELECT=5 qmake
QT_SELECT=5 make




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


