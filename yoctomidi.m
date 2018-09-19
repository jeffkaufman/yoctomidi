/* Pipes a Yocto-3D-V2 through to MIDI
 *
 * Jeff Kaufman, September 2018
 *
 * This file is under GPL v3 or later.
 *
 * The yoctolib directory is under different licensing; see yoctolib/README.txt
 * for those terms.  That directory has no changes from upstream, except for
 * deleting irrelevant directories under Examples/.
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

#import "yocto_api.h"
#import "yocto_tilt.h"

#define MAX_AXES 256

MIDIClientRef midiclient;
MIDIEndpointRef midiendpoint;

YTilt* tilt1;
YTilt* tilt2;

int last_tilt1 = 63;
int last_tilt2 = 63;

#define CC_TILT1 30
#define CC_TILT2 31

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

void yocto_callback(YTilt* tilt, NSString* functionValue) {
  NSLog(@"Tilt %d: %@", tilt == tilt1 ? 1 : 2, functionValue);
  // todo call send_midi
}

void setup_yocto() {
  NSError *error;
  if([YAPI RegisterHub:@"usb": &error] != YAPI_SUCCESS) {
    NSLog(@"RegisterHub error: %@", [error localizedDescription]);
    exit(1);
  }

  YTilt *anytilt = [YTilt FirstTilt];
  if (anytilt == NULL) {
    NSLog(@"No yocto module connected (check USB cable)");
    exit(1);
  }

  NSString *serial = [[anytilt get_module] get_serialNumber];
  // retrieve all sensors on the device matching the serial
  tilt1 = [YTilt FindTilt:[serial stringByAppendingString:@".tilt1"]];
  tilt2 = [YTilt FindTilt:[serial stringByAppendingString:@".tilt2"]];

  [tilt1 registerValueCallback:yocto_callback];
  [tilt2 registerValueCallback:yocto_callback];
}

int map_to_midi(double tilt) {
  // Tilt is in degress, so from -180 to +180.  Map to 0 ... 127
  return (tilt + 180) * 128 / 360;
}

void setup() {
  setup_midi();
  setup_yocto();
}

int main(int argc, char** argv) {
  @autoreleasepool {
    setup();
    while (true) {
      [YAPI Sleep:250:NULL];
    }
  }
  return 0;
}
