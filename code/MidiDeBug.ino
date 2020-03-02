//This program is used to test out each individual button
const int buttonPins[] = {13,12,11,10,9,8,7,6,5,4,3,2};  // the number of the Button pin

//variables will change:
boolean currentState = LOW;//stroage for current button state

void setup() {
  Serial.begin(9600);  //default midi speed rate
  //initialize the pushbutton pin as an input:
  for(int i = 0; i < 12; i++){
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}
  
void loop(){
  for(int i = 0; i < 12; i++){
   currentState = digitalRead(buttonPins[i]);
   
  if(currentState == 1)
    currentState = LOW;
   else
    currentState = HIGH;
   
    if (currentState == HIGH) {
      Serial.print(i + 1);
     }
  } 
}
