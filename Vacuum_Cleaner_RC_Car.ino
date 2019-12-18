/* Vacuum Cleaner Bluetooth RC Car     ***** Made by SeungGun, Refered to IC114(Basic RC Car) *****
    ※Above Sentences have function of this RC Car. 
    1. Direction indicating Using Dot-Matrix 
    2. Horning 
    3. Vaccum Cleaner [main function] 
*/
#include <AFMotor.h>
#include "LedControl.h"
LedControl matrix = LedControl(12, 11, 10, 2);

AF_DCMotor motor1(1); //Left motor(Standard For Behind)- M3 in shield -> M1(Suddenly occur the problem) -> M4
AF_DCMotor motor2(2); //Right motor (Standard For Behind)- M4 in shield -> M2

#include <SoftwareSerial.h> //For Using HC-06 as a digital pin
SoftwareSerial GunBT(2, 13); //Bluetooth Module HC-06, RX - digital number13,  TX - digital number 2

/* Dot-Matrix Observation is different compared to normal. */
byte For[] =
{ B00000000,
  B00100000,
  B01100000,
  B11111111,
  B11111111,
  B01100000,
  B00100000,
  B00000000
};

byte Back[] =
{ B00000000,
  B00000100,
  B00000110,
  B11111111,
  B11111111,
  B00000110,
  B00000100,
  B00000000
};

byte Left[] =
{ B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B01111110,
  B00111100,
  B00011000
};

byte Right[] =
{ B00011000,
  B00111100,
  B01111110,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000
};

byte ForRight[] =
{ B11111000,
  B11100000,
  B11110000,
  B10111000,
  B10011100,
  B00001110,
  B00000111,
  B00000011
};

byte ForLeft[] =
{ B00000011,
  B00000111,
  B00001110,
  B10011100,
  B10111000,
  B11110000,
  B11100000,
  B11111000
};

byte BackRight[] =
{ B00011111,
  B00000111,
  B00001111,
  B00011101,
  B00111001,
  B01110000,
  B11100000,
  B11000000
};

byte BackLeft[] =
{ B11000000,
  B11100000,
  B01110000,
  B00111001,
  B00011101,
  B00001111,
  B00000111,
  B00011111
};

int ENA = 9;   //Enable, Control PWM
int IN1 = 5;   //Control Motor A
int IN2 = 6;  // Control Motor A
/* Signal For Operating Motor
    IN1  IN2     Statement
    LOW  LOW   No Electricity
    LOW  HIGH  Rotate on Reverse Direction
    HIGH LOW   Rotate on Forward Direction
    HIGH HIGH  Stop
*/
char command; // For Switch function through Application.

void setup()
{
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 5);
  matrix.clearDisplay(0);

  Serial.begin(9600);
  GunBT.begin(9600);

  pinMode(8, OUTPUT);  // Buzzer
  pinMode(ENA, OUTPUT); // PWM Control of Motor Driver
  pinMode(IN2, OUTPUT); // IN2 Pin in Motor Driver (Reverse Direction)
  pinMode(IN1, OUTPUT); // IN1 Pin in Motor Driver (Forward Direction)

}

void loop() {

  if (GunBT.available() > 0) {
    command = GunBT.read();
    Stop();
    switch (command) {
      case 'F':
        forward();
        For_Light();
        break;
      case 'B':
        back();
        Back_Light();
        break;
      case 'L':
        left();
        Left_Light();
        break;
      case 'R':
        right();
        Right_Light();
        break;
      case 'I':
        forwardR();
        ForRight_Light();
        break;
      case 'G':
        forwardL();
        ForLeft_Light();
        break;
      case 'J':
        backR();
        BackRight_Light();
        break;
      case 'H':
        backL();
        BackLeft_Light();
        break;
      case 'W':
        FL_On();
        break;
      case 'w':
        FL_Off();
        break;
      case 'U':
        BL_On();
        break;
      case 'u':
        BL_Off();
        break;
      case 'V':
        Horn_On();
        break;
      case 'v':
        Horn_Off();
        break;
      case 'X':
        Cleaner_On();
        break;
      case 'x':
        Cleaner_Off();
        break;
    }

  }

}

void FL_On()
{
// Command: 'W'
// If you want to add specific function, Add here code and Command to communication with App
}

void FL_Off()
{
// Command: 'w'
// If you want to add specific function, Add here code and Command to communication with App
}

void BL_On()
{
//Command: 'U'
// If you want to add specific function, Add here code and Command to communication with App
}

void BL_Off()
{
//Command: 'u'
// If you want to add specific function, Add here code and Command to communication with App
}

void forward()
{
  motor1.setSpeed(210);
  motor1.run(FORWARD);
  motor2.setSpeed(210);
  motor2.run(FORWARD);

}

void forwardR()
{
  motor1.setSpeed(210);
  motor1.run(FORWARD);
  motor2.setSpeed(100);
  motor2.run(FORWARD);

}

void forwardL()
{
  motor1.setSpeed(100);
  motor1.run(FORWARD);
  motor2.setSpeed(210);
  motor2.run(FORWARD);

}


void back()
{
  motor1.setSpeed(210);
  motor1.run(BACKWARD);
  motor2.setSpeed(210);
  motor2.run(BACKWARD);

}

void backR()
{
  motor1.setSpeed(100);
  motor1.run(BACKWARD);
  motor2.setSpeed(210);
  motor2.run(BACKWARD);

}

void backL()
{
  motor1.setSpeed(210);
  motor1.run(BACKWARD);
  motor2.setSpeed(100);
  motor2.run(BACKWARD);

}

void left()
{
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(210);
  motor2.run(FORWARD);

}

void right()
{
  motor1.setSpeed(210);
  motor1.run(FORWARD);
  motor2.setSpeed(0);
  motor2.run(RELEASE);

}

void Stop()
{
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(0);
  motor2.run(RELEASE);

}
void For_Light() {

  for (int i = 0; i < 8; i++)
  { matrix.setRow(0, i, For[i]);

  }
}

void Back_Light() {

  for (int i = 0; i < 8; i++)
  { matrix.setRow(0, i, Back[i]);

  }
}
void Left_Light() {

  for (int i = 0; i < 8; i++)
  { matrix.setRow(0, i, Left[i]);

  }
}
void Right_Light() {

  for (int i = 0; i < 8; i++)
  { matrix.setRow(0, i, Right[i]);

  }
}
void ForRight_Light() {

  for (int i = 0; i < 8; i++)
  { matrix.setRow(0, i, ForRight[i]);

  }
}
void ForLeft_Light() {

  for (int i = 0; i < 8; i++)
  { matrix.setRow(0, i, ForLeft[i]);

  }
}
void BackRight_Light() {

  for (int i = 0; i < 8; i++)
  { matrix.setRow(0, i, BackRight[i]);

  }
}
void BackLeft_Light() {

  for (int i = 0; i < 8; i++)
  { matrix.setRow(0, i, BackLeft[i]);

  }
}

void Horn_On() {
  tone(3, 452);
}

void Horn_Off() {
  noTone(3);
}

void Cleaner_On() {
  digitalWrite(IN1, HIGH);
  analogWrite(ENA, 255);
}

void Cleaner_Off() {
  digitalWrite(IN1, HIGH); 
  analogWrite(ENA, 0);
}
