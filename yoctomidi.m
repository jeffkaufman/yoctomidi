/* Pipes a Yocto-3D-V2 through to MIDI
 *
 * Jeff Kaufman, September 2018
 *
 * This file is under GPL v3 or later.
 *
 * The yoctolib directory is under different licensing; see yoctolib/README.txt
 * for those terms.  That directory has no changes from upstream.
 *
 * See README for usage.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreMIDI/MIDIServices.h>
#include <CoreAudio/HostTime.h>
#include <IOKit/hid/IOHIDDevice.h>
#include <IOKit/hid/IOHIDManager.h>
#import <Foundation/Foundation.h>

#define MAX_AXES 256

MIDIClientRef midiclient;
MIDIEndpointRef midiendpoint;

void die(char *errmsg) {
  printf("%s\n",errmsg);
  exit(-1);
}

void attempt(OSStatus result, char* errmsg) {
  if (result != noErr) die(errmsg);
}

#define PACKET_BUF_SIZE (3+64) /* 3 for message, 32 for structure vars */
void send_midi(int cc, int v) {
  printf("Sending CC-%d: %d\n", cc, v);

  Byte buffer[PACKET_BUF_SIZE];
  Byte msg[3];
  msg[0] = 0xb0;  // control change
  msg[1] = cc;
  msg[2] = v;

  MIDIPacketList *packetList = (MIDIPacketList*) buffer;
  MIDIPacket *curPacket = MIDIPacketListInit(packetList);

  curPacket = MIDIPacketListAdd(packetList,
				PACKET_BUF_SIZE,
				curPacket,
				AudioGetCurrentHostTime(),
				3,
				msg);
  if (!curPacket) die("packet list allocation failed");

  attempt(MIDIReceived(midiendpoint, packetList), "error sending midi");
}

void setup_midi() {
  attempt(
    MIDIClientCreate(
     CFSTR("yocto 3d v2"),
     NULL, NULL, &midiclient),
    "creating OS-X MIDI client object." );
  attempt(
    MIDISourceCreate(
      midiclient,
      CFSTR("yocto 3d v2"),
      &midiendpoint),
   "creating OS-X virtual MIDI source." );
}


void setup_yocto() {
  // todo
}

void setup() {
  setup_midi();
  setup_yocto();
}

int main(int argc, char** argv) {
  setup();
  while (true) {
    poll_yocto();
    usleep(10);
  }
  return 0;
}
