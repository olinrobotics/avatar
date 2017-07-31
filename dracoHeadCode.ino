#include <Servo.h>//include built in Arduino servo library

// Set up Arduino Ports and Pins to support Robot
int redLedPin = 11;// robot alive red blinky light pin
int greenLedPin = 10;// robot alive green blinky light pin
int blueLedPin = 9;// robot alive blue blinky light pin
int eStopPin = 5;// create name for E-Stop reading pin
int eStopButtonState= 0; // eStop button status
int delayPeriod = 100; // hindbrain loop delay 
int DT = 0; // create name for sharp ir 0 analog input pin 0 / distance sensor for outside objects / sharpDistance0--> DT
int DM = 1; // create name for sharp ir 1 analog input pin 1-- distance sensor for anything in mouth / sharpDistance1--> DM
int speakerPin = 6;// create name for speaker pin
int numtones = 7;         // create number of tones
int tones[] = { 392, 379, 349, 330, 349, 370, 392 };  //stored tones
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
pinMode(speakerPin, OUTPUT);
 // Run Hindbrain loop until commanded to stop by Midbrain
  for (int i=0; i < numtones; i++)
  { tone(speakerPin, tones[i]);
    delay(200);
  }
  noTone(speakerPin);
}
void loop() {
 // put your main code here, to run repeatedly:
 // Hindbrain functions 


// Read Midbrain commands
if (DT > 15.0){
  hBrainStatus = 'r' ;
}
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
  Serial.println ("Nose distance:");
Serial.println (sharpRange (DT)); //Print range from Sharp on Pin A0
Serial.println ("Mouth distance:");
Serial.println (sharpRange (DM)); //Print range from Sharp on Pin A1 
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
jawServo.write(55); // command open mouth
delay(1000);
if (DM < 20.0){   // if something in the mouth
jawServo.write(70);  // command close mouth
delay(1000);

}

}
if (command == 'd') {
  Serial.println ("Drop");
  jawServo.write(55);  // command open mouth
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



