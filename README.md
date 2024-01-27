VMPT virtual music power transcriber/teacher
================================================
VMPT PeNny notates music notes from an audio file. 
The file can be saved and viewed in common Notation Programs. 
Most Audio Files are supported. 

Highly recommended
==================
Sonic Visualizer and e.g. piYIN transformation can export the annotation layer to a MIDI file. 

piYIN, MELODIA or cepstral-pitchtracker get good results of monophonic audio. 
nnls-chroma and chordino can get the chords for you. 
Polyphonic music may be translated by melodia. 

If you just need the notes for the vocals, we recommend using Spleeter (https://github.com/deezer/spleeter) to extract the vocals first. 

UNMAINTAINED
============
VMPT project is not maintained right now. We had to move away from the MusicXML-lib since it was unavailable and the migration to Lilypond was not finished. 
When developing the project, Sonic-Visualiser could not export MIDI-Files



Features
================================================
 * Console UI
 * Read Monophonic Audio
 * Transcribe Note Pitch
 * Save as MusicXML
 
Limitations
------------------------------------------------
 * no alterations
 
Run VMPT
================================================
vmpt InputAudioFile OutputMusicXmlScoreFile

The OutputMusicXmlScoreFile can be viewed/edited in MuseScore, 
a free scorewriter. Get it at www.musescore.org. 

Credits
================================================
VMPT was started by Günther Humer (www.dojoy.at). 

Biggest Thanks to Chris Cannam (Centre for Digital Music, 
Queen Mary, University of London), who developed the VAMP Plugin Architecture
and the VAMP Plugin Cepstral Pitch Track, which are used here. 

VMPT uses the following libraries
------------------------------------------------ 
 * QT5 - copyright (c) 2015 Digia Plc, LGPL
 * Vamp Host SDK - copyright (c) 2005-2009 Chris Cannam and QMUL, permissive BSD-style license
 * pYIN (probablistic YIN) - Centre for Digital Music, Queen Mary, University of London, GPL
 * sndfile - Erik de Castro Lopo, LGPL2.1
 * libmusicxml - MPL2.0
 * Boost C++ libraries - Boost Software License

Copyright 2015 Günther Humer
================================================
VMPT is free software; you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published 
by the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.  See the file COPYING included with
this distribution for more information. 

