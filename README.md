VMPT virtual music power transcriber/teacher
================================================
VMPT PeNny notates music notes from an audio file. 
The file can be saved and viewed in common Notation Programs. 
Most Audio Files are supported. 

Features
================================================
 * Console UI
 * Read Monophonic Audio
 * Transcribe Note Pitch
 * Save as MusicXML
 
Limitations
------------------------------------------------
 * no alterations
 
Known Bugs
------------------------------------------------
 * playing the same note twice can be interpreted as one long note

Run VMPT
================================================
vmpt InputAudioFile OutputMusicXmlScoreFile

The OutputMusicXmlScoreFile can be viewed/edited in MuseScore, a free scorewriter. 

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
 * Cepstral Pitch Tracker - copyright (c) 2012 Chris Cannam, permissive license
 * sndfile - Erik de Castro Lopo, LGPL2.1
 * libmusicxml - MPL2.0
 * Boost C++ libraries - Boost Software License

Copyright 2015 Günther Humer
================================================
VMPT is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.  See the file COPYING included with
this distribution for more information. 

