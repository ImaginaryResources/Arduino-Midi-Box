#include <MIDI.h>  // Include MIDI library
MIDI_CREATE_DEFAULT_INSTANCE();
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

//The final and working version of midi box
//This includes all 12 buttons as midi inputs

int anVal[5];
int anValPrev[5];

const int anPins[] = {A0,A1,A2,A3,A4};

const int buttonPins[] = {13,12,11,10,
                          9,8,7,6,
                          5,4,3,2};  //the number of the Button pin
                          
const int notes[] = {40,38,46,44,
                      48,47,45,43,
                      49,55,51,53};//MIDI Note Numbers

//variables will change:
boolean currentState = LOW;//stroage for current button state

void setup() {
  Serial.begin(31250);  //default midi speed rate
  //initialize the pushbutton pin as an input:
  for(int i = 0; i < 12; i++){
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  MIDI.begin(); 
}
  
void loop(){
  for(int i = 0; i < 12; i++){
   currentState = digitalRead(buttonPins[i]);
  
  if(currentState == 1)
    currentState = LOW;
   else
    currentState = HIGH;
   
    if (currentState == HIGH) {
      MIDI.sendNoteOn(notes[i],127,1);
      delay(200);
      MIDI.sendNoteOff(notes[i],0,1);
    }
   }

  for(int i = 0; i < 5; i++){
     anValPrev[i] = anVal[i]; //previous value
     anVal[i] = analogRead(anPins[i])/8; //Divide by 8 to get range of 0-127 for midi
     analogPinMidiTX(i + 1,anVal[i],anValPrev[i]); //TX value
  }
}

void analogPinMidiTX(int iChan, int iVal, int iValPrev)
{  
  //TX Value only if it has changed
  if(iValPrev != iVal)
  {
    MidiTX(176,iChan,iVal); //176 = CC command, 1 = Which Control, val = value read from Potentionmeter
  }
}

void MidiTX(unsigned char MESSAGE, unsigned char CONTROL, unsigned char VALUE) //Value in Midi Command
{
   Serial.write(MESSAGE);
   Serial.write(CONTROL);
   Serial.write(VALUE);
}
