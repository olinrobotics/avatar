#include <Servo.h>        //include built in Arduino servo library

// Set up Arduino Ports and Pins to support Robot
int redLedPin = 11;          // robot alive red blinky light pin
int greenLedPin = 10;          // robot alive green blinky light pin
int blueLedPin = 9;           // robot alive blue blinky light pin
int eStopPin = 5;          // create name for E-Stop reading pin
int delayPeriod = 100;     // hindbrain loop delay 
int sharpDistance0 = 0;    // create name for sharp ir 0 analog input pin 0-- distance sensor for outside objects
int sharpDistance1 = 1;    // create name for sharp ir 1 analog input pin 1-- distance sensor for anything in mouth
int speakerPin = 6;        // create name for speaker pin
int jaw = 60;             // variable to store jaw servo position in degrees
Servo jawServo;           // create jaw servo object to control a servo
char command = 'g' ;      // 'g' is go command from midbrain 'e' is stop, 
char hBrainStatus = 'r'; // hindbrain status 'r' running, 'e' E-Stopped
String readString;        // create a string to store Midbrain commands in


void setup() {
  // put your setup code here, to run once:
   // put your setup code here, to run once:
  pinMode (blueLedPin, OUTPUT);           //sets up Blinky "alive" light"  
  pinMode (greenLedPin, OUTPUT);           //sets up Blinky "alive" light"
  pinMode (redLedPin, OUTPUT);           //sets up Blinky "alive" light"
  pinMode (eStopPin, INPUT);           //sets up Sense input of E-Stop button  
  jawServo.write(60);  //set initial jaw position to 60 degrees or open
  jawServo.attach(3);                  //attach the jaw servo to pin 3
  Serial.begin(9600);                  //send and recieve at 9600 baud
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
    if (command != 'e') {      //during stop, ignore command to move jaw
    jaw = readString.toInt();       //convert readString into a jaw angle
    }     
    readString="";                  //empty readString for next input
    } 
    
 // Sense: Read and Process Robot Sensors
//Serial.println (readEstop()); //read and print
if (readEstop()==1){
  hBrainStatus = 'e' ; // if E-Stop switch triggered set Hindbrain status to E-Stopped
}
else hBrainStatus - 'r' ; // else set status to running
//Serial.println (sharpRange (sharpDistance0)); //Print range from Sharp on Pin A0 (debug only)
//Serial.println (sharpRange (sharpDistance1)); //Print range from Sharp on Pin A1 (debug only)
  float SharpRange0= sharpRange(sharpDistance0);  // Read Sharp mouth range 0 on Pin A0-- distance sensor for outside objects
  float SharpRange1= sharpRange(sharpDistance1);  // Read Sharp nose range 1 on Pin A1-- distance sensor for anything in mouth

  // Think: Run low level cognition and safety code
if (command == 'g') {  
  blink();                          // blink hindbrain running LEDs
}
else { //if e-Stopepd
  delay (delayPeriod);
  delay (delayPeriod); 
}

   
  // Act: Run actuators and behavior lights
   
  // Write status data up to MidBrain
  if (command == 'e') {
  Serial.println("hind brain stopped");   //print hindbrain status on serial monitor
  }
  if (command == 'g') {
  Serial.println("Hind brain running!!!!");   //print hindbrain status on serial monitor
  Serial.println ("Commanding jaw angle:");
  Serial.println ("Distance to outside objects:");
  Serial.println (SharpRange0);  //distance sensor for outside objects
  Serial.println ("Distance in mouth:");
  Serial.println (SharpRange1);  //distance sensor for anything in mouth
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


