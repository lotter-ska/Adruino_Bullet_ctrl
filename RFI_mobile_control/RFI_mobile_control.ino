/*

  RFI Mobile Control Software.
   Commands:
 SW11 = SW1 in pos 1
 SW12 = SW1 in pos 2
 SW21 = SW2 in pos 1
 SW22 = SW2 in pos 2
 SW31 = SW3 in pos 1
 SW32 = SW3 in pos 2
 SW41 = SW4 in pos 1
 SW42 = SW4 in pos 2
 
 ND_0 = ND OFF
 ND_1 = ND ON 
 
 LN10 = LNA1 OFF
 LN11 = LNA1 ON

 LN20 = LNA2 OFF
 LN21 = LNA2 ON

 PARK = ALL OFF
 
 CW__= Antenna CW
 CCW_= Antenna CCW
 HOR_= Antenna HOR
 VER_= Antenna VER
 POSA=Azi Pos
 POSP=Pol Pos
 
 Commands for Auto Mode (ADD + AFTER MODE ENTRY):
 MOD0 = MODE0 - 0.1-2  GHz high  gain  measurement
 MOD1 = MODE1 - 0.85-6  GHz high  gain  measurement
 MOD2 = MODE2 - high  gain  calibration
 MOD3 = MODE3 - 0.1-2 GHz medium  gain  measurement
 MOD4 = MODE4 - 0.85-12 GHz medium  gain  measurement
 MOD5 = MODE5 - medium  gain  calibration
 MOD6 = MODE6 - 0.85-26.5 GHz zero  gain  measurement
 MOD7 = MODE7 - zero gain calibration

TD =  SWITCH ND AT (INPUT(Hz))
ND =  PULSE ND
ND1 = SWITCH ND PN FOR INPUT(MS)
==================================================================================

Rotator control:
analoq V: 
0 - 5.1v ----> 0 to 405 ----> 0 - 1023
0 to 5.2v ----> 0 to 180 ----> 0 - 1023
scale factor az: 1023/405 = 2.526
scale factor pol: 1023/180 = 5.683
pinout control connector:
orange 4 rot left
w/green 2 rot right
brown 3 rot up
blue 5 rot down

w/blue 6 0 to 405 Deg
w/orange 1 0 to 180 Deg
green 8 common grnd
w/brown 7 Provides 13V to 6V DC @ 200mA

 created  Jun 2015
 by Lötter Kock
 */
#include <math.h>
// pins for the Outputs Arduino MEGA:
// To RF 
const int SW11 = 2;
const int SW12 = 3;
const int SW21 = 4;
const int SW22 = 5;
const int SW31 = 6;
const int SW32 = 7;
const int SW41 = 8;
const int SW42 = 9;

const int LNA10 = 10;
const int LNA11 = 11;
const int LNA20 = 12;
const int LNA21 = 13;
const int ND = 14;



// To Antenna Pos control
const int CW = 24;
const int CCW = 25;
const int HOR = 26;
const int VER = 27;


const float az_c = 2.526;
const float po_c = 5.683;

// Antenna Pos
int HOR_p = A0;
int VER_p = A1;
int cnt=0;
String command = "";
String command_old = "";
boolean stringComplete = false;  // whether the string is complete
unsigned long tt;
#define numberOfBytes 4

float pos = 0;
float freq = 0;
int del = 0;
void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  command.reserve(200);
  pinMode(SW11, OUTPUT); // 2: OW
  pinMode(SW12, OUTPUT); // 2: W
  pinMode(SW21, OUTPUT); // 2: BLW
  pinMode(SW22, OUTPUT); // 2: BL
  pinMode(SW31, OUTPUT); // 2: BR
  pinMode(SW32, OUTPUT); // 2: BRW
  pinMode(SW41, OUTPUT); // 2: G
  pinMode(SW42, OUTPUT); // 2: GW

  

  pinMode(LNA10, OUTPUT); // 1: BLW
  pinMode(LNA11, OUTPUT); // 1: BL
  pinMode(LNA20, OUTPUT); // 1: GW
  pinMode(LNA21, OUTPUT); // 1: G
  pinMode(ND, OUTPUT);
  digitalWrite(LNA10, LOW);
  digitalWrite(LNA20, LOW);

  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
  pinMode(HOR, OUTPUT);
  pinMode(VER, OUTPUT);



}


void loop() {
  serialEvent(); //call the function
  // print the string when a newline arrives:
  if (stringComplete) {
    check_command();
    if (command == "POSA+" || command == "POSP+") {
      Serial.println("Send Pos:");
      while(Serial.available()==0) { // Wait for User to Input Data 
      }
//      pos = Serial.parseInt();
      pos = Serial.parseFloat();
//      Serial.println(String(pos));
      if (command == "POSA+") {
        move();
      }
      if (command == "POSP+") {
        move1();
      }
      
    }
//    Serial.println(command);
    
    // clear the string:
    command = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    command += inChar;

    if (inChar == '+') {
      stringComplete = true;
    }
    if (inChar == 'Z') {
      stringComplete = true;
      command = "POSA+";
    }
    if (inChar == 'X') {
      stringComplete = true;
      command = "POSP+";
    }
    if (inChar == 'Q') {
      stringComplete = true;
      cnt=1000000;
    }
  }
}

//Check what hardware states have to change
void check_command(){
  //////////////////////////////////////////////////////////
    if (command == "SW11+") {
      Serial.println(command);
      clock_pin_inv(SW11);
      
    }
    else if (command == "SW12+") {
      Serial.println(command);
      clock_pin_inv(SW12);
    }
     else if (command == "SW21+") {
      Serial.println(command);
      clock_pin_inv(SW21);       
    }
    else if (command == "SW22+") {
      Serial.println(command);
      clock_pin_inv(SW22);    
    }
     else if (command == "SW31+") {
      Serial.println(command);
      clock_pin_inv(SW31);      
    }
    else if (command == "SW32+") {
      Serial.println(command);
      clock_pin_inv(SW32);     
    }
     else if (command == "SW41+") {
      Serial.println(command);
      clock_pin_inv(SW41);       
    }
    else if (command == "SW42+") {
      Serial.println(command);
      clock_pin_inv(SW42);     
    }
    ///////////////////////////////////////////////////////////
    else if (command == "LN10+") {
      Serial.println(command);
      clock_pin(LNA10);        
    }
    else if (command == "LN11+") {
      Serial.println(command);
      clock_pin(LNA11);     
    }
    else if (command == "LN20+") {
      Serial.println(command);
      clock_pin(LNA20);        
    }
    else if (command == "LN21+") {
      Serial.println(command);
      clock_pin(LNA21);     
    }
    else if (command == "NON+") {
      Serial.println(command);
      digitalWrite(ND, 1);  
      digitalWrite(LNA11, 1);
      digitalWrite(LNA21, 1);   
    }
     else if (command == "NOF+") {
      Serial.println(command);
      digitalWrite(ND, 0); 
      digitalWrite(LNA11, 0);
      digitalWrite(LNA21, 0);    
    }


    else if (command == "ND+") {
      Serial.println(command);
      digitalWrite(LNA11, 1);
      digitalWrite(LNA21, 1);
      clock_pin(ND); 
      digitalWrite(LNA11, 0);
      digitalWrite(LNA21, 0);    
    }

    else if (command == "ND1+") {
      Serial.println(command);
      Serial.println("Send ND ontime[ms]:");
      while(Serial.available()==0) { // Wait for User to Input Data 
      }
      float time = Serial.parseFloat();
      digitalWrite(LNA11, 1);
      digitalWrite(LNA21, 1);
      digitalWrite(ND, 1);
      delay(time);
      digitalWrite(ND, 0);
      digitalWrite(LNA11, 0);
      digitalWrite(LNA21, 0);    
    }

    else if (command == "TD+") {
      Serial.println(command);
      Serial.println("Send ND Freq[Hz]:");
      while(Serial.available()==0) { // Wait for User to Input Data 
      }
      freq = Serial.parseFloat();
      freq=1e6*(1/freq - 10e-3);
      if (freq > 16383) {
        del=1; //set flag to delay ms, not us
        freq=round(freq/1000); 
      }
      else {
        del = 0;
        
      }

      Serial.println(freq);
//      pos = Serial.parseFloat();

      // setup for TD chain
      clock_pin_inv(SW21);   //SW21
      clock_pin_inv(SW12);   //SW11
      clock_pin(LNA11);   //LNA1_ON
      clock_pin(LNA21);   //LNA2_ON
      digitalWrite(LNA11, 1);
      digitalWrite(LNA21, 1);
      tt=millis();
      for (cnt = 0; cnt<10000; cnt++) {
        clock_pin_q(ND);
        if (del == 0) {
          delayMicroseconds(freq);
        }
        else {
          delay(freq);
        }
        serialEvent();

      }
      tt=millis()-tt;
      Serial.println(tt);     
      digitalWrite(LNA11, 0);
      digitalWrite(LNA21, 0); 
      clock_pin(LNA10); 
      clock_pin(LNA20);          
    }
    ///////////////////////////////////////////////////////////
    else if (command == "MOD0+") {
      Serial.println(command);
      clock_pin_inv(SW11);   //SW11
      
      clock_pin_inv(SW31);   //SW31 
      
      clock_pin_inv(SW41);  //SW41 
      clock_pin(LNA11);   //LNA1_ON
      clock_pin(LNA21);   //LNA2_ON
//      clock_pin(1,0,0,1);   //ND_OFF
    }
    else if (command == "MOD1+") {
      Serial.println(command);
      clock_pin_inv(SW12);   //SW12
      clock_pin_inv(SW22);   //SW22
      clock_pin(LNA11);   //LNA1_ON
      clock_pin_inv(SW31);   //SW31
      clock_pin(LNA21);   //LNA2_ON
      clock_pin_inv(SW41);   //SW41 
//      clock_pin(1,0,0,1);   //ND_OFF
    }
    else if (command == "MOD2+") {
      Serial.println(command);
      clock_pin_inv(SW12);   //SW12
      clock_pin_inv(SW21);   //SW21
      clock_pin(LNA11);   //LNA1_ON
      clock_pin_inv(SW31);   //SW31
      clock_pin(LNA21);   //LNA2_ON
      clock_pin_inv(SW41);   //SW41
//      clock_pin(1,0,1,0);   //ND_ON
    } 
    else if (command == "MOD3+") {
      Serial.println(command);
      clock_pin_inv(SW12);   //SW12
      clock_pin(LNA10);   //LNA1_OFF
      clock_pin_inv(SW32);   //SW32
      clock_pin(LNA21);   //LNA2_ON
      clock_pin_inv(SW41);   //SW41
//      clock_pin(1,0,0,1);   //ND_OFF

    } 
    else if (command == "MOD4+") {
      Serial.println(command);
      clock_pin_inv(SW11);   //SW11
      clock_pin_inv(SW22);   //SW22
      clock_pin(LNA10);   //LNA1_OFF
      clock_pin_inv(SW32);   //SW32
      clock_pin(LNA21);   //LNA2_ON
      clock_pin_inv(SW41);   //SW41
//      clock_pin(1,0,0,1);   //ND_OFF
    }
    else if (command == "MOD5+") {
      Serial.println(command);
      clock_pin_inv(SW11);   //SW11
      clock_pin_inv(SW21);   //SW21
      clock_pin(LNA10);   //LNA1_OFF
      clock_pin_inv(SW32);   //SW32
      clock_pin(LNA21);   //LNA2_ON
      clock_pin_inv(SW41);   //SW41
//      clock_pin(1,0,1,0);   //ND_ON
    }
    else if (command == "MOD6+") {
      Serial.println(command);
      clock_pin_inv(SW21);   //SW21
      clock_pin(LNA10);   //LNA1_OFF
      clock_pin(LNA20);   //LNA2_OFF
      clock_pin_inv(SW42);   //SW42
//      clock_pin(1,0,0,1);   //ND_OFF 
    }
    else if (command == "MOD7+") {
      Serial.println(command);
      clock_pin_inv(SW22);   //SW22
      clock_pin(LNA10);   //LNA1_OFF
      clock_pin(LNA20);   //LNA2_OFF
      clock_pin_inv(SW42);   //SW42
//      clock_pin(1,0,1,0);   //ND_ON
    }
    else if (command == "PARK+") {
      Serial.println(command);
      clock_pin(LNA10);   //LNA1_OFF
      clock_pin(LNA20);   //LNA2_OFF
//      clock_pin(1,0,0,1);   //ND_OFF
//      clock_pin(0,0,0,0);   //NO CMD  
    }
    else if (command == "POSA+") {
      Serial.println(command);
    }   
    else {
      Serial.println("Bad cmd");            
    }
}

void clock_pin(int pin) {
  
  digitalWrite(pin, 1);
  delay(50);
  digitalWrite(pin, 0);
}

void clock_pin_inv(int pin) {
  
  digitalWrite(pin, 1);
  delay(80);
  digitalWrite(pin, 0);
}

void clock_pin_q(int pin) {

  digitalWrite(pin, 1);
  delay(10);
  digitalWrite(pin, 0);
}

void move(){

  int az = analogRead(HOR_p); 
  delay(100);
  pos=pos*az_c;
  Serial.println(String(pos));
  Serial.println(az);
  if (az<pos) {
    digitalWrite(CW, 1);
    while (analogRead(HOR_p)<pos) {
    }
    digitalWrite(CW, 0);
    Serial.println("Done Rotating CW");
  }
  else {
    digitalWrite(CCW, 1);
    while (analogRead(HOR_p)>pos) {
    }
    digitalWrite(CCW, 0);
    Serial.println("Done Rotating CCW");
  }  
}
void move1(){

  int po = analogRead(VER_p); 
  delay(100);
  pos=pos*po_c;
  Serial.println(String(pos));
  Serial.println(po);
  if (po<pos) {
    digitalWrite(HOR, 1);
    while (analogRead(VER_p)<pos) {
    }
    digitalWrite(HOR, 0);
    Serial.println("Done Rotating HOR");
  }
  else {
    digitalWrite(VER, 1);
    while (analogRead(VER_p)>pos) {
    }
    digitalWrite(VER, 0);
    Serial.println("Done Rotating VER");
  }  
}

