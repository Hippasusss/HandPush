#include <Adafruit_trellis.h>

const byte CHANNEL = 1;
const byte OFFSET = 9+24;


void setup() 
{
}

void loop()
{    
}

void sendNoteOn(byte channel, byte pitch, byte velocity) 
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void sendNoteOff(byte channel, byte pitch, byte velocity) 
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
