#include "BluetoothSerial.h"
#include "ESP32Servo.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Servo gripperServo;
Servo bracketServo;
  
  const int motorA1      = 32;  
  const int motorA2      = 33; 
 
  const int motorB1      = 26; 
  const int motorB2      = 27; 

  
  int state;
  int vSpeed=200;     // Default speed, from 0 to 255

  //Posisi Griper Open and Close dalam derajat
  const int gripperOpenPos = 100;   
  const int gripperClosePos = 30;

  //Posisi Bracket Up and Down dalam derajat
   const int bracketUp = 95;
   const int bracketDown = 30 ;

void setup() {
    // Set pins as outputs:
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);

    // ledcAttachPin(motorAspeed, 0);   
    // ledcAttachPin(motorBspeed, 1);   
    
    SerialBT.begin("COOL-E");
   
    // Initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

    gripperServo.attach(1);
    bracketServo.attach(23);
}
 
void loop() {
  
    if(SerialBT.available() > 0){
      state = SerialBT.read();
      Serial.println(state);    
    }
   
  //Change speed if state is equal from 0 to 4. Values must be from 0 to 255 (PWM)
  switch (state) {
  case 0:
  vSpeed = 0;
  break;
  case 1:
  vSpeed = 100;
  break;
  case 2:
  vSpeed = 180;
  break;
  case 3:
  vSpeed = 200;
  break;
  case 4:
  vSpeed = 255;
  break;

  case 83:
  /************************Stop*****************************/
  digitalWrite(motorA1, 0);  digitalWrite(motorA2, 0); 
  digitalWrite(motorB1, 0);  digitalWrite(motorB2, 0);
  break;

  case 70:
  /***********************Forward****************************/
  digitalWrite (motorA1,1);
  digitalWrite(motorA2,0);                       

  digitalWrite (motorB1,1);
  digitalWrite(motorB2,0);

  // digitalWrite (motorAspeed, vSpeed);
  // digitalWrite (motorBspeed, vSpeed);
  break;

  case 73:
  /**********************Forward Left************************/
  digitalWrite (motorA1,0);
  digitalWrite(motorA2,0);                       

  digitalWrite (motorB1,1);
  digitalWrite(motorB2,0);

  break;

  case 71:
  /**********************Forward Right************************/
  digitalWrite (motorA1,1);
  digitalWrite(motorA2,0);                       
  
  digitalWrite (motorB1,0);
  digitalWrite(motorB2,0);

  break;

  case 66:
  /***********************Backward****************************/
  digitalWrite (motorA1,0);
  digitalWrite(motorA2,1);                       
  
  digitalWrite (motorB1,0);
  digitalWrite(motorB2,1);

  // digitalWrite (motorAspeed, vSpeed);
  // digitalWrite (motorBspeed, vSpeed);
  break;

  case 74:
  /**********************Backward Left************************/
  digitalWrite (motorA1,0);
  digitalWrite(motorA2,0);                       
  
  digitalWrite (motorB1,0);
  digitalWrite(motorB2,1);
  break;

  case 72:
  /**********************Backward Right************************/
  digitalWrite (motorA1,0);
  digitalWrite(motorA2,1);                       
  
  digitalWrite (motorB1,0);
  digitalWrite(motorB2,0);

  break;

  case 76:
  /***************************Left*****************************/
  digitalWrite (motorA2,0);
  digitalWrite(motorA1,1);                       
  
  digitalWrite (motorB2,1);
  digitalWrite(motorB1,0);

  break;

  case 82:
  /***************************Right*****************************/
  digitalWrite (motorA2,1);
  digitalWrite(motorA1,0);                       
  
  digitalWrite (motorB2,0);
  digitalWrite(motorB1,1);
 
  break;

  case 'V' : 
  gripperServo.write(gripperOpenPos);   
  break;
  
  case 'v':
  // Menutup gripper
  //if (gripperOpenPos <= 120) {
    //gripperOpenPos -= gripperCloseIncrement;
    //gripperServo.write (gripperOpenPos);
  //}
  gripperServo.write(gripperClosePos);
  break;

  case 'U':
  bracketServo.write(bracketUp);
  break;

  case 'u':
  bracketServo.write(bracketDown);
  break;
  }
}