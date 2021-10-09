#include "Adafruit_Trellis.h"
#include <MIDIUSB.h>

const byte CHANNEL = 1;
const byte OFFSET = 48;
const byte NUMSWITCHES = 16;

Adafruit_Trellis trellis = Adafruit_Trellis();
Adafruit_TrellisSet matrix = Adafruit_TrellisSet(&trellis);

void setup() 
{
    matrix.begin(0x70);

    for(int i = 0; i < NUMSWITCHES; ++i)
    {
        matrix.setLED(i);
        matrix.writeDisplay();
        delay(50);
    }

    for(int i = 0; i < NUMSWITCHES; ++i)
    {
        matrix.clrLED(i);
        matrix.writeDisplay();
        delay(50);
    }
}

void loop()
{    
    delay(30);
    if(matrix.readSwitches())
    {
        for(int i = 0; i < NUMSWITCHES; ++i)
        {
            if(matrix.justPressed(i))
            {
                setSwitch(i);
            }
            if(matrix.justReleased(i))
            {
                unsetSwitch(i);
            }
        }
        matrix.writeDisplay();
    }
}

void setSwitch(int switchNum)
{
    if(!matrix.isLED(switchNum)) matrix.setLED(switchNum);
    sendNoteOn(CHANNEL, switchNum + OFFSET, 127);
}

void unsetSwitch(int switchNum)
{
    if(matrix.isLED(switchNum)) matrix.clrLED(switchNum);
    sendNoteOff(CHANNEL, switchNum + OFFSET, 127);
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
