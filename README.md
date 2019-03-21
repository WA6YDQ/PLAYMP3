# PLAYMP3
Python3 mp3 and mp4 player with playlists

(Taken from the source code)
This is an mp3 player written in python 3 using a raspberry pi zero w.

I expect it should work with any computer thay runs python 3 using appropriate
hardware and software drivers.

The software library used for mp3 codecs etc is vlc.py

The ID3 data is from the eyeD3 library.

pip3 install python-vlc (for mp3 player)

vlc (via sudo apt-get install vlc) for mp3 player

pip install eyeD3 (for mp3 ID3 tags for mp3 player)

Hardware used for the mp3 player include a 2x16 line LCD display
connected via I2C thru an adafruit i2c-lcd interface board.

The switches are using an adafruit capacitive touch sensor 
(mpr121, part number 1982) with the sensor pins wired as 
follows:

pin 0:	unused

pin 1:	shift (rcrd - used as a record button in other applications)

pin 2:	stop

pin 3:	play/pause

pin 4:	rewind to beginning of the current playing song

pin 5:	foward to next song

pin 6-13: unused

Lastly, there is a rotary encoder (mechanical, 2 lines) tied to
GPIO. This is used for a volume control, tuning in 5% steps.

shift function commands:

rcrd + stop:	save current song to most fav playlist (mostfav.m3u)

rcrd + play:	toggle thru shuffle and repeat play

rcrd + rew:	shuffle back by 2%/second to beginning of song

rcrd + fwd:	shuffle forward by 2%/second to end of song

The output goes thru I2S for audio out giving CD quality. The board
I use is an adafruit I2S stereo decoder, UDA1334A. With the wires 
between the pi zero and the I2S board kept apart from other wires, the
playback audio is very nice. No clicks, 44.1k audio quality. Much better 
(and easier to setup/use) than an external USB soundcard.

Many of the hardware drivers come from adafruit's circuit py driver library.
Their instructions for install and setup are adequit, if a little terse.

plmp3 uses playlists to hold lists of songs. The playlist extension is .m3u
and the playlist contents is a filename with the full path:

mp3/Music/William Shatner/Has Been/01 Common People.mp3
mp3/Music/Firefall/Firefall_-_Cinderella.mp3
etc.

The shuffle function is written in c since the python version took 30 minutes to 
run with 5000 songs. The c version takes 3 seconds on the pi zero.


--------------------------------------

While there is special hardware for the buttons/display, the overall program is a good framework
for playing musin in python.

You will need vlc.py as the player engine. It does a lot more than I use it for.

