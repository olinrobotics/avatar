#include <Servo.h>        //include built in Arduino servo library
#include "pitches.h"     // *TEST*

// Set up Arduino Ports and Pins to support Robot
int redLedPin = 11;          // robot alive red blinky light pin
int greenLedPin = 10;          // robot alive green blinky light pin
int blueLedPin = 9;           // robot alive blue blinky light pin
int eStopPin = 5;          // create name for E-Stop reading pin
int delayPeriod = 100;     // hindbrain loop delay 
int DT = 0;    // create name for sharp ir 0 analog input pin 0 / distance sensor for outside objects / sharpDistance0--> DT
int DM = 1;    // create name for sharp ir 1 analog input pin 1-- distance sensor for anything in mouth / sharpDistance1--> DM
int speakerPin = 6;        // create name for speaker pin
int jaw = 60;             // variable to store jaw servo position in degrees
Servo jawServo;           // create jaw servo object to control a servo
char command = 'g' ;      // 'g' is go command from midbrain 's' is stop, 
char hBrainStatus = 'r'; // hindbrain status 'r' running, 's' E-Stopped
char command = 'p' ; //'p' pickup command
char command = 'd' //'d' drop command
String readString;        // create a string to store Midbrain commands in
int melody[] = {
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A4, 0, NOTE_D4  //*TEST* might sound bad
};

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 8
};


void setup() {
  // put your setup code here, to run once:
   // put your setup code here, to run once:
  pinMode (blueLedPin, OUTPUT);           //sets up Blinky "alive" light"  
  pinMode (greenLedPin, OUTPUT);           //sets up Blinky "alive" light"
  pinMode (redLedPin, OUTPUT);           //sets up Blinky "alive" light"
  pinMode (eStopPin, INPUT);           //sets up Sense input of E-Stop button  
  jawServo.write(60);         //set initial jaw position to 60 degrees or open
  jawServo.attach(3);                  //attach the jaw servo to pin 3
  Serial.begin(9600);                  //send and recieve at 9600 baud
  for (int thisNote = 0; thisNote < 8; thisNote++) { //*TEST* melody
    int noteDuration = 1000 / noteDurations[thisNote];    //*TEST* quarter note = 1000 / 4, eighth note = 1000/8, etc.
    tone(6, melody[thisNote], noteDuration);     //*TEST* tone(pin, frequency, duration)
    int pauseBetweenNotes = noteDuration * 1.30;  //*TEST*
    delay(pauseBetweenNotes);  //*TEST*
    noTone(6);   //*TEST* stop the tone playing
  }

 // Run Hindbrain loop until commanded to stop by Midbrain

}

void loop() {
  // put your main code here, to run repeatedly:
  // Read Midbrain commands
  while (Serial.available()) {    // checks to see if you have message in serial buffer
    command = Serial.read();      // read character command from serial monitor
    readString += command;        //makes the string readString to store commands
    delay(5000);                     //slow loop to allow buffer to fill with next character
  }

if (Serial.available ()) {
  command = Serial.read(); //read character command from serial monitor
  Serial.println ("Mindbrain sent:");
  Serial.println (command); //print midbrain command in serial monitor
}
  
    if (readString.length() >0) {
    Serial.println(readString);     //so you can see the captured string 
    if (command != 's') {      //during stop, ignore command to move jaw
    jaw = readString.toInt();       //convert readString into a jaw angle
    }     
    readString="";                  //empty readString for next input
    } 
    
 // S
 // E
 // N
 // S
 // E
 // Read and Process Robot Sensors
//Serial.println (readEstop()); //read and print
if (readEstop()==1){
  hBrainStatus = 's' ; // if E-Stop switch triggered set Hindbrain status to E-Stopped
}
else hBrainStatus - 'r' ; // else set status to running
//Serial.println (sharpRange (sharpDistance0)); //Print range from Sharp on Pin A0 (debug only)
//Serial.println (sharpRange (sharpDistance1)); //Print range from Sharp on Pin A1 (debug only)
  float DT= sharpRange(DT);  // Read Sharp mouth range 0 on Pin A0-- distance sensor for outside objects
  float DM= sharpRange(DM);  // Read Sharp nose range 1 on Pin A1-- distance sensor for anything in mouth

  //T
  //H
  //I
  //N
  //K
  //Run low level cognition and safety code
if (command == 'g') {  
  blink();                          // blink hindbrain running LEDs
}
else { //if e-Stopepd
  delay (delayPeriod);
  delay (delayPeriod); 
}
if (command == 'p') {
  Serial.println (Pick up);
  jawServo.write(60);              // command open mouth
  delay(500);
  if (DM < 15.0){                 // if something in the mouth
    jawServo.write(70);              // command close mouth 
    delay(500);

}
if (command == 'd') {
  Serial.println (Drop);
  jawServo.write(60);              // command open mouth
  delay(500);
}   
if (DT < 15.0){
  hBrainStatus = 's' ;
}
  //A 
  //C
  //T
  //Run actuators and behavior lights
   
  // Write status data up to MidBrain
  if (command == 's') {
  Serial.println("hind brain stopped");   //print hindbrain status on serial monitor
  }
  if (command == 'g') {
  Serial.println("Hind brain running!!!!");   //print hindbrain status on serial monitor
  Serial.println ("Commanding jaw angle:");
  Serial.println ("Distance to outside objects (DT):");
  Serial.println (DT);  //distance sensor for outside objects
  Serial.println ("Distance in mouth (DM):");
  Serial.println (DM);  //distance sensor for anything in mouth
  Serial.println ("Jaw angle:");
  Serial.println (jaw);
  jawServo.write (jaw); 
  } 
 
}


// Hindbrain functions *************************************
// Sense Functions
boolean readEstop ()  {  // Read relay attached to E-stop switch
  boolean eStopTriggered = digitalRead (eStopPin);
  return eStopTriggered;
}

float sharpRange(int sensornum) {   //Read Sharp range, return range in cms
  int rawData = analogRead(sensornum);    // V is 0-1023
  float volts = rawData*0.0048828125;     //convert to volts
  float range = 65*pow(volts, -1.10);     // approximate exp data graph function
  return range;
}


// Think Functions
void blink (){                   //this function blinks the Hindbrain Alive LEDs
  digitalWrite (blueLedPin, HIGH);
  delay (delayPeriod);
  digitalWrite (blueLedPin, LOW);
  delay  (delayPeriod);
   digitalWrite (greenLedPin, HIGH);
  delay (delayPeriod);
  digitalWrite (greenLedPin, LOW);
  delay  (delayPeriod);
  digitalWrite (redLedPin, HIGH);
  delay (delayPeriod);
  digitalWrite (redLedPin, LOW);
  delay  (delayPeriod);
  }

  
// Act Functions


