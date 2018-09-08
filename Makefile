gcmidi: yoctocmidi.m
	gcc \
    -F/System/Library/PrivateFrameworks \
	  -framework CoreMIDI \
    -framework CoreFoundation \
    -framework CoreAudio \
    -framework Foundation \
    -framework IOKit \
	  yoctomidi.m -o yoctomidi -std=c99 -Wall

run: yoctomidi
	./yoctomidi
