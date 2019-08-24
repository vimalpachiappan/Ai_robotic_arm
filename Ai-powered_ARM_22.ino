#include <LobotServoController.h>


LobotServoController myse(Serial);


// create servo object to control a servo.
//Servo counting goes from 0 to 4
//Grip = 0  Wrist = 1  Elbow = 2   Shoulder = 3  Base = 4

int pos, CurrentAngle;
int i;
int x[5]={90,90,90,90,90};

//****** Setup IK variables ******
#define PI 3.14159265

float ShoulderLength =10;
float ElbowLength = 10;
float WristLength = 13;
float Hypot, Slope, CirclePointX, CirclePointY;
float x1 = 0.0;//Target end point.10.6
float y1 = 0.0;//Target end point.7.5
float x2 = 0.0;//origin start point.
float y2 = 0.0;//origin start point.
float z1,z2 = 0.0;
float w1 = 0.0;
float A, B, C,
      PosXAnswer,   //positive X portion of Quadratic Equation.
      PosYAnswer,   //positive Y portion of Qudratic Equation.
      NegXAnswer,   //negative X portion of Quadratic Equation.
      NegYAnswer,   //negative Y portion of Quadratic Equation.
      Angle_A,      //Angle located at origin (0,0).
      Angle_A_Temp, //Second 1/2 of Angle located at origin (0,0).Shoulder servo setting.
      Angle_B,      //Elbow servo setting.
      Angle_C;      //Wrist servo setting subtracted from 180.



void setup()
{

  Serial.begin(9600);

  LobotServo servo[6];
  servo[0].ID=1;
  
  servo[1].ID=2;
  
  servo[2].ID=3;
  
  servo[3].ID=4;
  
  servo[4].ID=5;
  
  servo[5].ID=6;


  // Initialize servos...
  Serial.println("Initializing Servos...");
  ResetServos();

}//end setup.


void loop()
{

   Serial.println("enter Theta_1.1");
   while(Serial.available()==0);
   {
    x1=Serial.parseInt();
    }

    
   Serial.println("Theta_1.2");
   while(Serial.available()==0);
   {
     y1=Serial.parseInt();
    
    }
//    
//   Serial.println("Theta_3");
//   while(Serial.available()==0);
//   {
//     w1=Serial.parseInt();
//    
//    }
  
  Serial.println("enter x1 ");
   while(Serial.available()==0);
   {
    z1=Serial.parseInt();
    }

    
   Serial.println("enter Theta_1.2");
   while(Serial.available()==0);
   {
    x2=Serial.parseInt();
    }

    
   Serial.println("Theta_2.2");
   while(Serial.available()==0);
   {
     y2=Serial.parseInt();
    
    }
    Serial.println("enter x2 ");
   while(Serial.available()==0);
   {
    z2=Serial.parseInt();
    }

    //y1 = 15;
   // z1 = 15;
   
      Serial.print("Point: (");
      Serial.print(x1);
      Serial.print(",");
      Serial.print(y1);
      Serial.println(")");
    

        z1 = map(z1,-20,20,500,2500);
        myse.moveServo(6,z1,1000);
        delay(500);

      if (x1 < 180){
        delay(1000);
        
    int  five=map(x1,180,0,500,2400);
     myse.moveServo(5,five,2000); 
     Serial.println(five);
     delay(1000);
     int four=map(y1,-90,90,650,2500);
     myse.moveServo(4,four,2000);
     Serial.println(four);
     delay(2000);
     //int one = map(w1,90,-90,500,2373);
     myse.moveServo(1,2450,2000);
     delay(2000);
          myse.moveServo(5,1500,1000); 
     delay(2000);
     
          myse.moveServo(4,1500,1000); 
     delay(2000);
          myse.moveServo(2,1500,1000);
          delay(2000);
                  z2 = map(z2,-20,20,500,2500);

               myse.moveServo(6,z2,1000); 
              delay(2000);
                        myse.moveServo(2,2400,1000);
                delay(2000);
                
    int  five1=map(x2,180,0,500,2400);
     myse.moveServo(5,five1,2000); 
     Serial.println(five1);
     delay(1000);
     int four1=map(y2,-90,90,650,2500);
     myse.moveServo(4,four1,2000);
     Serial.println(four1);
     delay(2000);
               myse.moveServo(1,1500,1000);
               delay(2000);
               myse.moveServo(5,1500,2000); 
     delay(2000);
               
myse.moveServos(5,1500,1,1500,2,2400,3,1500,4,1500,6,1500); 


     
        }

      //end if x1 & y1 < ShoulderLength.
      else {
            float d1 = x1 -180;
            float e1 = 90 - d1;
            float f1 = - y1;
            
    int  five=map(e1,0,180,500,2400);
     myse.moveServo(5,five,1000); 
     Serial.println(five);
     int four=map(y1,-90,90,650,2500);
     myse.moveServo(4,four,1000);
     Serial.println(four);
            
        

      }//end else.
    //end y1 for.
  //end x1 for.


}//end Loop.



void Special_Calc_Point() {

  Hypot = sqrt(sq(x1) + sq(y1)) + WristLength;
  Serial.print(Hypot);
  B = ElbowLength;//9;
  C = Hypot;//B_Value;//6.7; //check here for nan.
  A = ShoulderLength;//11.5;



  //*** Calculate angle A ***//
  Angle_A = acos((sq(B) + sq(C) - sq(A)) / (2 * B * C)) * (180 / PI);
      Angle_A_Temp = acos((sq(x1) + sq(Hypot) - sq(y1)) / (2 * x1 * Hypot))*(180 / PI); //Second 1/2 of Angle A from X axis upto Shoulder arm.
      Angle_A = Angle_A + Angle_A_Temp; //Second 1/2 of Angle A from X axis plus Shoulder arm angle.
Serial.print(Angle_A);

  //*** Calculate angle B ***//
  Angle_B =  acos((sq(C) + sq(A) - sq(B)) / (2 * A * C)) * (180 / PI);
Serial.print(Angle_B);
  //*** Calculate angle C ***//
  Angle_C = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B)) * (180 / PI);
 Serial.print(Angle_C); 



  if (!isnan(Angle_A)) {      //If Angle is a valid number.
    Serial.println(Angle_A);
    int four=map(Angle_A,0,180,500,2500);
    Serial.println(four);
    myse.moveServo(5,four,1000);
    
  }
  else {
    Serial.print("no");
    }


  if (!isnan(Angle_B)) { //If Angle is a valid number.

    CurrentAngle = 90;

    if (Angle_B > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i < Angle_B; i = i + 1) //if Angle_B > CurrentAngle.
      {

        int three=map(i,0,180,2500,500);
        myse.moveServo(4,three,500);
       
      }//end for CurrentAngle.

    }//end if Angle_B > CurrentAngle.

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i > Angle_B; i = i - 1) //if Angle_B < CurrentAngle.
      {
         int three=map(i,0,180,2500,500);
        myse.moveServo(4,three,500);
       
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.



  if (!isnan(Angle_C)) { //If Angle is a valid number.

    CurrentAngle = 90;

    if (Angle_C > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i < Angle_C; i = i + 1) //if Angle_C > CurrentAngle.
      {
        int five=map(i,0,180,1000,2500);
        myse.moveServo(3,five,500);
       
      }//end for CurrentAngle.

    }//end if Angle_C > CurrentAngle.

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i > Angle_C; i = i - 1) //if Angle_C < CurrentAngle.
      {
        int five=map(i,0,180,1000,2500);
        myse.moveServo(3,five,500);
       
      }//end for CurrentAngle.
    }//end else.

  } //end if isnan.


}//end Special_Calc_Circle.


void Calc_Point() {
  Slope = (y2 - y1) / (x2 - x1);
  Serial.print("Slope: ");
  Serial.println(Slope, 4);


  A = 1 + sq(y1 / x1);
  B = (-2 * x1) + (-2 * y1 * Slope);
  C = sq(y1) + sq(x1) - sq(WristLength);




  /*
  Use: sqrt (-1);  // Set to not a number...nan.
  */

  Serial.println();


  NegXAnswer = ((-1 * B) - (sqrt(sq(B) - (4 * A * C)))) / (2 * A); //Minus portion of Quadratic Equation.
  NegYAnswer = Slope * NegXAnswer;

  if (!isnan(NegXAnswer)) {

    Serial.print("Negative Point: ");
    Serial.print(NegXAnswer);
    Serial.print(",");
    Serial.println(NegYAnswer);
    Serial.println();

    Calc_Circle(NegXAnswer, NegYAnswer);
  }//end if Negative !isnan.

  else
  {



    PosXAnswer = ((-1 * B) + (sqrt(sq(B) - (4 * A * C)))) / (2 * A); //Plus portion of Quadratic Equation.
    PosYAnswer = Slope * PosXAnswer;

    if (!isnan(PosXAnswer)) {
      Serial.print("**** Positive Point: ");
      Serial.print(PosXAnswer);
      Serial.print(",");
      Serial.println(PosYAnswer);
      Serial.println();

      Calc_Circle(PosXAnswer, PosYAnswer);

    }//end if Positive !isnan.

  }//end else.

}//end Calc_Point.



void Calc_Circle(float BXValue, float BYValue) {

  Hypot = sqrt(sq(BXValue) + sq(BYValue));
  A = ElbowLength;//4;
  B = Hypot;//B_Value;//6.7; //check here for nan.
  C = ShoulderLength;//6;

Angle_A = acos((sq(B) + sq(C) - sq(A)) / (2 * B * C)) * (180 / PI);

  Angle_A_Temp = acos((sq(x1) + sq(Hypot) - sq(y1)) / (2 * x1 * Hypot)) * (180 / PI); //Second 1/2 of Angle A from X axis upto Shoulder arm.
  //Angle_A = Angle_A + Angle_A_Temp; //Second 1/2 of Angle A from X axis plus Shoulder arm angle.

  //*** Calculate angle B ***//
  Angle_B =  acos((sq(C) + sq(A) - sq(B)) / (2 * A * C)) * (180 / PI);


  //*** Calculate angle C ***//
  Angle_C = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B)) * (180 / PI);
  //Angle_C = 180 - Angle_C; //must calc larger opposite side angle.


  

  if (!isnan(Angle_A)) { //If Angle is a valid number.
    Serial.print("a  ");
    Serial.println(Angle_A);
    int four=map(Angle_A,0,180,1500,2500);
    myse.moveServo(5,four,1000);
    
  }

  if (!isnan(Angle_B)) { //If Angle is a valid number.

    CurrentAngle =90;

    if (Angle_B > CurrentAngle) {
      //Serial.print(CurrentAngle);
      Serial.print(" b   ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i < Angle_B; i = i + 1) //if Angle_B > CurrentAngle.
      {
        int three=map(i,0,180,500,2500);
        myse.moveServo(4,three,1000);
        
       
      }//end for CurrentAngle.

    }//end if Angle_B > CurrentAngle.

    else
    {
      //Serial.print(CurrentAngle);
      Serial.print(" b  ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i > Angle_B; i = i - 1) //if Angle_B < CurrentAngle.
      {
        int three=map(i,0,180,500,2500);
        myse.moveServo(4,three,1000);
         
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.



  if (!isnan(Angle_C)) { //If Angle is a valid number.

    CurrentAngle = 90;

    if (Angle_C > CurrentAngle) {
      //Serial.print(CurrentAngle);
      Serial.print(" c   ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i < Angle_C; i = i + 1) //if Angle_C > CurrentAngle.
      {
        int five=map(i,0,180,500,2500);
        myse.moveServo(3,five,1000);
       
      }//end for CurrentAngle.

    }//end if Angle_C > CurrentAngle.

    else
    {
      //Serial.print(CurrentAngle);
      Serial.print(" c   ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i > Angle_C; i = i - 1) //if Angle_C < CurrentAngle.
      {
        int five=map(i,0,180,500,2500);
        myse.moveServo(3,five,1000);
       
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.


}//end Calc_Circle.



void ResetServos()
{
myse.moveServos(5,1000,1,1500,2,2400,3,1500,4,1500,6,1500); 
  

} //End ResetServos.


