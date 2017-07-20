#include <Servo.h>//include built in Arduino servo library
//     note, period 
#define c  3830  
#define d  3400  
#define e  3038  
#define f  2864 
#define g  2550  
#define a  2272  
#define b  2028 
#define C  1912
// Define a special note, 'R', to represent a rest
#define R 0

// Set up Arduino Ports and Pins to support Robot
int redLedPin = 11;// robot alive red blinky light pin
int greenLedPin = 10;// robot alive green blinky light pin
int blueLedPin = 9;// robot alive blue blinky light pin
int eStopPin = 5;// create name for E-Stop reading pin
int eStopButtonState= 0; // eStop button status
int delayPeriod = 100; // hindbrain loop delay 
int DT = 0; // create name for sharp ir 0 analog input pin 0 / distance sensor for outside objects / sharpDistance0--> DT
int DM = 1; // create name for sharp ir 1 analog input pin 1-- distance sensor for anything in mouth / sharpDistance1--> DM
int speakerOut = 6;// create name for speaker pin
int jaw = 60;  // variable to store jaw servo position in degrees
Servo jawServo; // create jaw servo object to control a servo
char command = 'g' ;// 'g' is go command from midbrain 's' is stop,
char hBrainStatus = 'r'; // hindbrain status 'r' running, 's' E-Stopped
char pickUp= 'p' ; //'p' pickup command
char drop= 'd' ; //'d' drop command
String readString; // create a string to store Midbrain commands in

boolean readEstop (){  // Read relay attached to E-stop switch
boolean eStopTriggered = digitalRead (eStopPin);
return eStopTriggered;
}

float sharpRange(int sensornum) {  //Read Sharp range, return range in cms
 int rawData = analogRead(sensornum); // V is 0-1023
 float volts = rawData*0.0048828125;  //convert to volts
 float range = 65*pow(volts, -1.10);  // approximate exp data graph function
return range;
}




void setup() {
// put your setup code here, to run once:
// put your setup code here, to run once:
pinMode (blueLedPin, OUTPUT); //sets up Blinky "alive" light" 
pinMode (greenLedPin, OUTPUT); //sets up Blinky "alive" light"
pinMode (redLedPin, OUTPUT);  //sets up Blinky "alive" light"
pinMode (eStopPin, INPUT);  //sets up Sense input of E-Stop button 
jawServo.write(60);//set initial jaw position to 60 degrees or open
jawServo.attach(3);//attach the jaw servo to pin 3
Serial.begin(9600);//send and recieve at 9600 baud
 pinMode(speakerOut, OUTPUT);
 // Run Hindbrain loop until commanded to stop by Midbrain
pinMode(speakerOut, OUTPUT);
int melody[]= {c,d,e,f,g,R,C};// melody
int beats[]= { 16,16,16,16,16,32,8 }; // note length, higher number means longer note
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping
}
long tempo = 10000; // Set length of pause between notes
int pause = 1000; // Loop variable to increase Rest length
int rest_count = 100; //rest
int tone_= 0; // Initialize core variables
int beat= 0;
long duration= 0;
void playTone() {
 long elapsed_time = 0;
 if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
//played less long than 'duration', pulse speaker HIGH and LOW
while (elapsed_time < duration) {
digitalWrite(speakerOut,HIGH);
delayMicroseconds(tone_ / 2);
digitalWrite(speakerOut, LOW);
delayMicroseconds(tone_ / 2);
elapsed_time += (tone_);
 }
}
else {
for (int j = 0; j < rest_count; j++) { 
delayMicroseconds(duration);
} 
 }
}
void melody (){
  int MAX_COUNT = sizeof(melody) / 2;
  int beats[]= { 16,16,16,16,16,32,8 };
  int beat= 0;
for (int i=0; i<MAX_COUNT; i++) {
tone_ = melody[i];
beat = beats[i];

duration = beat * tempo; // Set up timing

playTone(); 
// A pause between notes...
delayMicroseconds(pause);
}
}

void loop() {
 // put your main code here, to run repeatedly:
 // Hindbrain functions 
 // Sense Functions



// Think Functions



// Act Functions

// Read Midbrain commands
 while (Serial.available()) {// checks to see if you have message in serial buffer
 command = Serial.read();// read character command from serial monitor
 readString += command; //makes the string readString to store commands
 delay(5000);   //slow loop to allow buffer to fill with next character
 }

if (Serial.available ()) {
 command = Serial.read(); //read character command from serial monitor
 Serial.println ("Mindbrain sent:");
 Serial.println (command); //print midbrain command in serial monitor
}

 if (readString.length() >0) {
 Serial.println(readString);  //so you can see the captured string 
 if (command != 's') {//during stop, ignore command to move jaw
 jaw = readString.toInt();  //convert readString into a jaw angle
 } 
 readString=""; //empty readString for next input
 } 

eStopButtonState= digitalRead(eStopPin);
 
// S
// E
// N
// S
// E
// Read and Process Robot Sensors
//Serial.println (readEstop()); //read and print
if (eStopButtonState == HIGH){
 hBrainStatus = 's' ; // if E-Stop switch triggered set Hindbrain status to E-Stopped
}
if (hBrainStatus = 'r'){ // else set status to running
Serial.println (sharpRange (DT)); //Print range from Sharp on Pin A0 (debug only)
Serial.println (sharpRange (DM)); //Print range from Sharp on Pin A1 (debug only)
  float DT= sharpRange(DT);  // Read Sharp mouth range 0 on Pin A0-- distance sensor for outside objects
  float DM= sharpRange(DM);  // Read Sharp nose range 1 on Pin A1-- distance sensor for anything in mouth
}

//T
//H
//I
//N
//K
//Run low level cognition and safety code
if (command == 'g') { 
digitalWrite (blueLedPin, HIGH);
delay (delayPeriod);
digitalWrite (blueLedPin, LOW);
delay(delayPeriod);
digitalWrite (greenLedPin, HIGH);
delay (delayPeriod);
digitalWrite (greenLedPin, LOW);
delay(delayPeriod);
digitalWrite (redLedPin, HIGH);
delay (delayPeriod);
digitalWrite (redLedPin, LOW);
delay (delayPeriod);  // blink hindbrain running LEDs
}
else { //if e-Stopepd
delay (delayPeriod);
delay (delayPeriod); 
}
if (command == 'p') {
Serial.println ("Pick up");
jawServo.write(60); // command open mouth
delay(500);
if (DM < 20.0){   // if something in the mouth
jawServo.write(70);  // command close mouth
delay(500);

}
if (command == 'd') {
  Serial.println ("Drop");
  jawServo.write(60);  // command open mouth
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
Serial.println("hind brain stopped");//print hindbrain status on serial monitor
}
if (command == 'g') {
Serial.println("Hind brain running!!!!");  //print hindbrain status on serial monitor
Serial.println ("Commanding jaw angle:");
Serial.println ("Distance to outside objects (DT):");
Serial.println (DT);//distance sensor for outside objects
Serial.println ("Distance in mouth (DM):");
Serial.println (DM);//distance sensor for anything in mouth
Serial.println ("Jaw angle:");
Serial.println (jaw);
jawServo.write (jaw);
} 
}
}


