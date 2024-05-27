#include "BluetoothSerial.h"
#include "ESP32Servo.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Servo gripper;
Servo bracketServo;
  
  const int motorA1 = 32;  
  const int motorA2 = 33; 
 
  const int motorB1 = 17; 
  const int motorB2 = 16; 

  int gripperPin = 15; 

  int state;
  int vSpeed=210; // Default speed, from 0 to 255

  //Posisi Griper Open and Close dalam derajat
  // const int gripperOpenPos = 100;   
  // const int gripperClosePos = 30;

  //Posisi Bracket Up and Down dalam derajat
   const int bracketUp = 65;
   const int bracketDown = 0 ;

void setup() {
    // Set pins as outputs:
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    
    gripper.attach(gripperPin);
    bracketServo.attach(23);
    // ledcAttachPin(motorAspeed, 0);   
    // ledcAttachPin(motorBspeed, 1);   
    
    SerialBT.begin("COOL-E");
   
    // Initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

    
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
  vSpeed = 210;
  break;
  case 4:
  vSpeed = 255;
  break;

  case 83:
  /************************Stop*****************************/
  analogWrite(motorA1, 0); analogWrite(motorA2, 0); 
  analogWrite(motorB1, 0); analogWrite(motorB2, 0);
  break;

  case 70:
  /***********************Forward****************************/
  analogWrite (motorA1,210);
  analogWrite(motorA2,0);                       

  analogWrite (motorB1,210);
  analogWrite(motorB2,0);

  // analogWrite (motorAspeed, vSpeed);
  // analogWrite (motorBspeed, vSpeed);
  break;

  case 73:
  /**********************Forward Left************************/
  analogWrite (motorA1,0);
  analogWrite(motorA2,0);                       

  analogWrite (motorB1,210);
  analogWrite(motorB2,0);

  break;

  case 71:
  /**********************Forward Right************************/
  analogWrite (motorA1,210);
  analogWrite(motorA2,0);                       
  
  analogWrite (motorB1,0);
  analogWrite(motorB2,0);

  break;

  case 66:
  /***********************Backward****************************/
  analogWrite (motorA1,0);
  analogWrite(motorA2,210);                       
  
  analogWrite (motorB1,0);
  analogWrite(motorB2,210);

  // analogWrite (motorAspeed, vSpeed);
  // analogWrite (motorBspeed, vSpeed);
  break;

  case 74:
  /**********************Backward Left************************/
  analogWrite (motorA1,0);
  analogWrite(motorA2,0);                       
  
  analogWrite (motorB1,0);
  analogWrite(motorB2,210);
  break;

  case 72:
  /**********************Backward Right************************/
  analogWrite (motorA1,0);
  analogWrite(motorA2,210);                       
  
  analogWrite (motorB1,0);
  analogWrite(motorB2,0);

  break;

  case 76:
  /***************************Left*****************************/
  analogWrite (motorA2,0);
  analogWrite(motorA1,210);                       
  
  analogWrite (motorB2,210);
  analogWrite(motorB1,0);

  break;

  case 82:
  /***************************Right*****************************/
  analogWrite (motorA2,210);
  analogWrite(motorA1,0);                       
  
  analogWrite (motorB2,0);
  analogWrite(motorB1,210);
 
  break;

  // case 'V' : 
  // gripper.write(gripperOpenPos);   
  // break;
  
  // case 'v':
  // gripper.write(gripperClosePos);
  // break;
  
  case '1':
  gripper.write(30);
  break;

  case '2':
  gripper.write(45);
  break;
  
  case '3':
  gripper.write(60);
  break;
  
  case '4':
  gripper.write(75);
  break;
  
  // //case '5':
  // //gripper.write(90);
  // break;
  
  // case '6':
  // gripper.write(105);
  // break;

  case 'W':
  bracketServo.write(bracketUp);
  break;

  case 'w':
  bracketServo.write(bracketDown);
  break;
  }
}
