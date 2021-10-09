#include <Adafruit_trellis.h>
#include <MIDIUSB.h>

const byte CHANNEL = 1;
const byte OFFSET = 48;
const byte NUMSWITCHES = 16

Adafruit_Trellis matrix = Adafruit_Trellis();

void setup() 
{
    matrix.begin()
}

void loop()
{    
    if(matrix.readSwitches())
    {
        for(int i = 0; i < NUMSWITCHES; ++i)
        {
            if(matrix.justPressed(i))
            {
                setSwitch(i)
            }
            if(matrix.justReleased(i))
            {
                unsetSwitch(i)
            }
        }
    }
}

void setSwitch(int switchNum)
{
    matrix.setLED(switchNum);
    sendNoteOn(CHANNEL, switchNum + OFFSET, 127)
}

void unsetSwitch(int switchNum)
{
    matrix.unsetLED(switchNum);
    sendNoteOff(CHANNEL, switchNum + OFFSET, 127)
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
