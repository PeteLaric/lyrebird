# lyrebird
A musical steganography system that converts arbitrary data into listenable music, and vice-versa.

LYREBIRD MUSICAL STEGANOGRAPHY SYSTEM
(cc) BY 2019 Pete Laric
http://www.PeteLaric.com



VIDEOS

Lyrebird musical steganography suite: demo
https://youtu.be/lFGXv-U1yWI



OVERVIEW

Lyrebird is a musical steganography system that converts arbitrary data into listenable music, and vice-versa.  The goal of the project is to blur the line between artistic expression, which enjoys First Amendment protection against censorship, and other forms of speech that the U.S. government has erroneously claimed are exempt from such protections.  One relevant example of the latter is a technical drawing of a firearm that could allow a person to fabricate such a weapon using a 3D printer, or other CNC-type rapid prototyping equipment.



MOTIVATION

My primary motivation for developing this software was to illustrate that data can be expressed and transformed in many ways.  Prior to Lyrebird, most people would probably have contended that "a drawing of a gun", and "a piece of music", are two mutually exclusive categories, i.e. there is no piece of music that is also a drawing of a gun, or vice-versa.  Now that Lyrebird exists, it has been conclusively shown that it is possible to express any digital information -- including information that is potentially "controversial" or "regulated" -- as music.  I wish law enforcement the best of luck in detecting music with hidden data contained therein.  I wish the courts the best of luck in prosecuting people for possessing, distributing, and enjoying music that may or may not contain such data... of which the listener may or may not even be aware!  Our would-be nannies are about to develop one hell of a headache.

My secondary motivation was to give the world a small sample of my capabilities, to advertise my availability for employment and contract work of a technical nature.  I don't work cheap, but I do quality work (as I hope you will agree).  If you are interested in hiring me, please contact:

	peter_desimone at hotmail dot com



DONATIONS

Donations are always appreciated, and may be sent to my bitcoin address:

	1EExevPZkgjoRFEbQzTFLpAoyDpwAdeQXw

If you send a donation, please also consider sending me an email (peter_desimone at hotmail dot com) so I can thank you for your generosity.



INSTRUCTIONS

Lyrebird is actually a suite of three independent programs:


1) lyrebird_compose

lyrebird_compose takes as input any file containing arbitrary data.  This could be text, a photo, music, a ZIP archive -- whatever.  It outputs music in .lyrebird format.  lyrebird_compose is written in ANSI C, and may be compile from the Mac OS or Linux terminal using a command like this:

	gcc -g -Wall lyrebird_compose.c -lm -o lyrebird_compose

To use lyrebird_compose, navigate to the enclosing directory within Terminal and type something like this:

	./lyrebird_compose myfile.txt

where "myfile.txt" is some file that you want to turn into music (it doesn't have to be a text file).


2) lyrebird_play

lyrebird_play takes as input a piece of music in .lyrebird format.  It outputs listenable music in .WAV or .OGG format, and also plays the music for your enjoyment.  A visual representation of the waveform is displayed to the screen.  lyrebird_play is written in MATLAB, which is a proprietary high-level scripting language for scientific computing.  To run lyrebird_play, MATLAB must be installed on your computer.  As of this writing, compatibility with Octave (an open source knockoff of MATLAB) has not been confirmed.  In the future, I plan to port lyrebird_play to a more portable language like C, Java, Processing, or Python.


3) lyrebird_decompose

lyrebird_decompose takes as input a piece of music in .lyrebird format, and converts the music into whatever file was used to generate it in the first place.  If you downloaded a piece of music from the internet that someone else created, chances are, lyrebird_decompose is the program you want to use.

lyrebird_decompose is written in ANSI C, and may be compile from the Mac OS or Linux terminal using a command like this:

	gcc -g -Wall lyrebird_decompose.c -lm -o lyrebird_decompose

To use lyrebird_decompose, navigate to the enclosing directory within Terminal and type something like this:

	./lyrebird_decompose mysong.lyrebird

where "mysong.lyrebird" is some song that you want to decode back into whatever data was used to create it.



LICENSE

Lyrebird is released under a Creative Commons: Attribution license and may be freely distributed (even commercially), so long as credit is given to the author.  Basically, give me credit and you can do whatever the hell you want with it.
