/*Programming the sound sensor module(microphone) using arduino
   LIST OF MATERIALS
   #1.Arduino Board(Any can do)
   #2.3 or 4 MTM(Male to female) connecting pins
   #3.2 male to male connecting pins(or increase depending on the number of LEDs)
   #4.Sound sensor module--

   #####HOW TO SET IT UP######
   -Take the three male to female jumpers(wires) and connect +, G and the DO(Digital Output)pin on the sound sensor to 
    5V, gnd and any digital I/O pin on the  on the arduino respectfully.
   -Connect the +ve end of an LED to any other digital pin and -ve to gnd of arduino

*/

//##CODE##
#define soundPin 7      //You can change this to whatever pin you chose 
#define ledPin 8 
int soundVal;
int clapped = 1;       //You can as well change this to be whatever pin you chose for the led
void setup() {
  pinMode(soundPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  soundVal = digitalRead(soundPin);
  Serial.println(clapped);
  if(soundVal ==1 ){
    clapped++;
    clapped = clapped%2;
    if(clapped%2 == 0){
      digitalWrite(ledPin, HIGH);
      delay(200);
    }
    else{
      digitalWrite(ledPin, LOW);
      delay(200);
    }
  }
  

}
