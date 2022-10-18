#include "SerialCommand.h"
#include <AccelStepper.h>
#include "configuration.h"
/*
Commands :
identity

sardauscan =>ask if this is a sardaucan => response "yes" //

laser :
L => ask laser configuration => response number of lasers
L x => ask status of laser index X
      => 'x' laser number
L x y  => turn laser on or off 
    'x' laser number
    'y' state: 0=off 1=on

Table :
T => table position
T S => return the number of steps for a revolution 
T C => Set Current position as 0 (for absolute positionning
T R xxx => rotate relatively xxx steps 
T A xxx => turn position absolute xxx steps 

unknow command 
=> response "Hun?"

*/

AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);


SerialCommand SCmd;

int RotationToSteps(int rotation)
{
  return rotation*STEP_BY_MINMOVE;
}
int StepsToRotation(int rot)
{
  return rot/STEP_BY_MINMOVE;
}
void Identification()
{
	Serial.println("yes");
}
void Hun()
{
	Serial.println("Hun?");
}
void TableCommand()
{
	 char *arg; 
	 arg = SCmd.next(); 
	 if (arg != NULL) 
	 {
		 if(arg[0]=='R'||arg[0]=='r') // T R
		 {
                    char *arg2 = SCmd.next(); 
                    int pos=atoi(arg2);
                    stepper1.move(RotationToSteps(pos));
                    stepper1.runToPosition();
		    Serial.print("RELATIVE ROTATION :"); 
		    Serial.print(pos); 
		    Serial.print(" => "); 
		    Serial.println(StepsToRotation(stepper1.currentPosition())); 
		 }
		 else if(arg[0]=='A'||arg[0]=='a') // T A
		 {
                    char *arg2 = SCmd.next(); 
                    int pos=atoi(arg2);
                    stepper1.moveTo(RotationToSteps(pos));
                    stepper1.runToPosition();
		    Serial.print("ABSOLUTE ROTATION "); 
		    Serial.print(pos); 
		    Serial.print(" => "); 
		    Serial.println(StepsToRotation(stepper1.currentPosition())); 
		 }
		 else if(arg[0]=='S'||arg[0]=='s') //T S
                  {
		    Serial.print("REVOLUTION STEPS "); 
		    Serial.print(" => "); 
		    Serial.println(StepsToRotation(REVOLUTION_STEP)); 
                  }
		 else if(arg[0]=='C' ||arg[0]=='c') //T C
                  {
                    stepper1.setCurrentPosition(0);
		    Serial.print("RESET CUTTENT POSITION "); 
		    Serial.print(" => "); 
		    Serial.println(StepsToRotation(stepper1.currentPosition())); 
                  }
                 else
                 {
		    Serial.print("Unknown Table command :"); 
		    Serial.println(arg); 
                 }
	 } 
  else {
     Serial.print("Position "); 
    Serial.println(StepsToRotation(stepper1.currentPosition())); 
  }
}
int getLaserPin(int laserIndex)
{
       if(laserIndex==0)
         return LASER_PIN_1; 
       else if(laserIndex==1)
         return LASER_PIN_2; 
       else if(laserIndex==2)
         return LASER_PIN_3; 
       else if(laserIndex==3)
         return LASER_PIN_4; 
       else
         return (-1); 
}

void LaserCommand()
{
  char *arg; 
  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    int laserIndex=atoi(arg);
    char *arg2 = SCmd.next(); 
    if (arg2 == NULL) 
    {
       Serial.print("LASER_STATE: "); 
       Serial.print(laserIndex); 
       int pin =getLaserPin(laserIndex);
       Serial.print("("); 
       Serial.print(pin); 
       Serial.print(") = "); 
       if(pin>=0)
         Serial.println(digitalRead(pin)); 
       else
         Serial.println(-1); 
    }
    else 
    {
       int laserState = atoi(arg2);
       int pin =getLaserPin(laserIndex);
       if(pin>=0)
        digitalWrite( pin, laserState==1?HIGH:LOW);
       Serial.print("SET_LASER: "); 
       Serial.print(laserIndex); 
       Serial.print("("); 
       Serial.print(pin); 
       Serial.print(") = "); 
      Serial.println(digitalRead(pin)); 
     }
   }
   else 
   {
    Serial.print("LASER_COUNT: "); 
    Serial.println(LASER_COUNT); 
   }
}

void G01()
/*G01 [T(steps)] - Move the Turntable for number of steps*/
{
	 char *arg; 
	 arg = SCmd.next(); 
	 if (arg != NULL) 
	 {
		 if(arg[0]=='T'||arg[0]=='t') // G01 T
		 {
                    char *arg2 = SCmd.next(); 
                    int pos=atoi(arg2);
                    stepper1.move(RotationToSteps(pos));
                    stepper1.runToPosition();
		    Serial.print("RELATIVE ROTATION :"); 
		    Serial.print(pos); 
		    Serial.print(" => "); 
		    Serial.println(StepsToRotation(stepper1.currentPosition())); 
		 }
                 else
                 {
		    Serial.print("Unknown Table command :"); 
		    Serial.println(arg); 
                 }
	 } 
         else 
	 {
             Serial.print("Position "); 
             Serial.println(StepsToRotation(stepper1.currentPosition())); 
         }
}

void M04()
/*M4 [R(value) G(value) B(value)] - Turn on LED Ring for given RGB-Vlaues*/
{

}

void M17()
/*M17 - Enable Motors*/
{

}

void M18()
/*M18 - Disable Motors*/
{

}

void M19()
/*M19 - Turn On Laser 0*/
{

}

void M20()
/*M20 - Turn Off Laser 0*/
{

}

void M21()
/*M21 - Turn On Laser 1*/
{

}

void M22()
/*M22 - Turn Off Laser 1*/
{

}

void M100()
/*M100 - Show Help Message*/
{

}


void setup() {
  stepper1.setMaxSpeed(500.0);
  stepper1.setAcceleration(200.0);
  stepper1.setSpeed(400);
  stepper1.moveTo(0);
  stepper1.runToPosition();
  Serial.begin(SERIAL_BAUD);
 
  pinMode(LASER_PIN_1, OUTPUT);
  pinMode(LASER_PIN_2, OUTPUT);
  pinMode(LASER_PIN_3, OUTPUT);
  pinMode(LASER_PIN_4, OUTPUT);
  digitalWrite(LASER_PIN_1, LOW);
  digitalWrite(LASER_PIN_2, LOW);
  digitalWrite(LASER_PIN_3, LOW);
  digitalWrite(LASER_PIN_4, LOW);
  SCmd.addCommand("sardauscan",Identification);
  SCmd.addCommand("T",TableCommand);
  SCmd.addCommand("t",TableCommand);
  SCmd.addCommand("L",LaserCommand);
  SCmd.addCommand("l",LaserCommand);
  SCmd.addCommand("G01",G01);
  SCmd.addCommand("g01",G01);
  SCmd.addCommand("M04",Mcode);
  SCmd.addCommand("m04",Mcode);
  SCmd.addCommand("M17",Mcode);
  SCmd.addCommand("m17",Mcode);
  SCmd.addCommand("M18",Mcode);
  SCmd.addCommand("m18",Mcode);
  SCmd.addCommand("M19",Mcode);
  SCmd.addCommand("m19",Mcode);
  SCmd.addCommand("M20",Mcode);
  SCmd.addCommand("m20",Mcode);
  SCmd.addCommand("M21",Mcode);
  SCmd.addCommand("m21",Mcode);
  SCmd.addCommand("M22",Mcode);
  SCmd.addCommand("m22",Mcode);
  SCmd.addCommand("M100",Mcode);
  SCmd.addCommand("m100",Mcode);
  SCmd.addDefaultHandler(Hun);
  Serial.println(FIRMWARE_VERSION);
  Serial.flush();
}


void loop() {
	SCmd.readSerial();     // We don't do much, just process serial commands
        Serial.flush();
}



