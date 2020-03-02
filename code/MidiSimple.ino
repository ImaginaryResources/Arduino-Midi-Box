#include <MIDI.h>  // Include MIDI library
MIDI_CREATE_DEFAULT_INSTANCE();
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

//This program is tests out only one button as midi input

int iAn0Val;

const int buttonPin2 = 2;  //the number of the Button pin

//variables will change:
boolean currentState2 = LOW;//stroage for current button state

void setup() {
  
  Serial.begin(31250);  //default midi speed rate
  //initialize the pushbutton pin as an input:
  pinMode(buttonPin2, INPUT_PULLUP);      
  MIDI.begin(); 
}
  
void loop(){
  

   currentState2 = digitalRead(buttonPin2);
   
  if(currentState2 == 1)
    currentState2 = LOW;
   else
    currentState2 = HIGH;
   
    if (currentState2 == HIGH) {
      MIDI.sendNoteOn(36,127,1);
      MIDI.sendNoteOff(36,0,1);
     }       
     
   int iAn0ValPrev = iAn0Val; //previous value
   iAn0Val = analogRead(A0)/8; //Divide by 8 to get range of 0-127 for midi
   analogPinMidiTX(1,iAn0Val,iAn0ValPrev); //TX value 
}

void analogPinMidiTX(int iChan, int iVal, int iValPrev)
{  
  //TX Value only if it has changed
  if(iValPrev != iVal)
  {
    MidiTX(176,iChan,iVal); //176 = CC command, 1 = Which Control, val = value read from Potentionmeter
  }
}

void MidiTX(unsigned char MESSAGE, unsigned char CONTROL, unsigned char VALUE)//Value of Midi Command
{
   Serial.write(MESSAGE);
   Serial.write(CONTROL);
   Serial.write(VALUE);
}
