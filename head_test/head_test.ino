//For Neck - 100 to 50 and then 50 to 100
//Head - 80 to 180

 //Finger 4 - Pin 2
 //Finger 5 - Pin 3
 //Finger 3 - Pin 5
 //Finger 2 - Pin 6
 //Finger 1 - Pin 4

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myJaw;
Servo myHead;
Servo myNeck;
// Port 3 and 4 are broken.

int headPos = 0;
int jawPos = 0;
int NeckPos = 0;
int SwitchPin = 8;
boolean isReady = false;
boolean LastButton = LOW;
boolean RobotOn = false;
boolean jawMode = false;
boolean neckMode = false;

void setup() {
 myNeck.attach(3);
 myHead.attach(5);
 myJaw.attach(7);
 Serial.begin(9600);
  //As of current connection, finger connected to pin 6 of the arduino, finger number 2, does not work.
  ;  // attaches the servo on pin 9 to the servo object
// Serial.println("HELLO");
}

void NeckRight(void){
  for (NeckPos = 230; NeckPos >= 40; NeckPos -=1){
      myNeck.write(NeckPos);
      delay(20);
      }
  }

void JawUp(void){
  for(jawPos=0; jawPos <= 100; jawPos+=2){
      myJaw.write(jawPos);
      delay(15);
  }
}
void NeckLeft(void){
  for (NeckPos = 40; NeckPos <= 230; NeckPos += 1){
      myNeck.write(NeckPos);
      delay(20);
  }
}

void JawDown(void){
   for (jawPos = 100 ; jawPos >= 0; jawPos-=2){
    myJaw.write(jawPos);
    delay(15);
    }
  }

void resetHead(){
  myHead.write(0);
}

void HeadDown(void){
  // Serial.println("HeadDown Start");
  for (headPos = 90; headPos >= 0; headPos -= 1) { // MAYBE 120 MAX
    myHead.write(headPos);
    delay(200);
  }
}
void HeadUp(void){
  // Serial.println("HeadUp Start");
  int pos = 0;
  for (pos = 0; pos <= 90; pos += 1) { // MAYBE 120 MAX
    // in steps of 1 degree
    myHead.write(pos);              // tell servo to go to position in variable 'pos'
    delay(200);
  }
}


// HEAD IMPORTANT!!!
// 90 is "looking forward"
// 150 is "looking right"
// 30 is "looking left"
// DO NOT GO TO 180, 0, OR >180/<0!!!!!

void moveToHead(int thePos){
  int pos = 0;
  if( thePos > myHead.read()){
    for (pos = myHead.read(); pos <= thePos; pos+=1){
      myHead.write(pos);
      delay(100);
    }
  }
  else{
    for (pos = myHead.read(); pos >= thePos; pos -= 1){
      myHead.write(pos);
      delay(100);      
    }
  }
}

void moveToJaw(int thePos){
  int pos = 0;
  if( thePos > myJaw.read()){
    for (pos = myJaw.read(); pos <= thePos; pos+=1){
      myJaw.write(pos);
      delay(200);
    }
  }
  else{
    for (pos = myJaw.read(); pos >= thePos; pos -= 1){
      myJaw.write(pos);
      delay(200);      
    }
  }
}

// NECK IMPORTANT!!!
// 90 is "looking forward"
// 150 is "looking down"
// 50 is "looking up"
// DO NOT GO TO 180, 0, OR >180/<0!!!!!

void moveToNeck(int thePos){
  int pos = 0;
  int increment = 0;
  if(thePos > myNeck.read()){
    for (pos = myNeck.read(); pos <= thePos; pos+=1){
      // Serial.println(pos);
      myNeck.write(pos);
      delay(20);
      increment++;
//      if (increment == 10){
//        delay(500);
//        increment = 0;
//      }
    }
  }
  else{
    for (pos = myNeck.read(); pos >= thePos; pos -= 1){
      // Serial.println(pos);
      myNeck.write(pos);
      delay(20);      
      increment++;
//      if (increment == 10){
//        delay(500);
//        increment = 0;
//      }
    }
  }
}

void loop() {

  //TODO: Make the "moveTo"s move in increments of 10 to avoid servo problems
  //TODO: Make the delay shorter  

  if (Serial.available() > 0){

    int per = Serial.parseInt();

    if(!jawMode && !neckMode && (per >=30 && per <= 150)){
      moveToHead(per);
      // Serial.print("moved ");
      // Serial.println(per);
      // Serial.print("Head Pos: ");
      // Serial.println(myHead.read());
    }

    else if(jawMode && !neckMode && (per >=30 && per <= 150)){
      moveToJaw(per);
      // Serial.print("moved ");
      // Serial.println(per);
      // Serial.print("Jaw Pos: ");
      // Serial.println(myJaw.read());
    }

    else if(!jawMode && neckMode && (per >=50 && per <= 150)){
      moveToNeck(per);
      // Serial.print("moved ");
      // Serial.println(per);
      // Serial.print("Neck Pos: ");
      // Serial.println(myNeck.read());
    }
    
    else if(per == 2){
      // Serial.println("Neck Mode");
      neckMode = true;
      jawMode = false;
    }
    else if(per == 1){
      // Serial.println("Jaw Mode");
      jawMode = true;
      neckMode = false;
    }
    else if(per == 0){
      // Serial.println("Head Mode");
      jawMode = false;
      neckMode = false;
    }

  }
//  if(isReady){
//    // Serial.println(myHead.read());
//    HeadUp();
//    delay(1000);  
//    HeadDown();
//    isReady = false;
//  }

//    HeadUp();
//    // Serial.println(myHead.read());
//    delay(2000);
//    HeadDown();
//    // Serial.println(myHead.read());
//    delay(2000);
    //NeckRight();
    //JawUp();
    //HeadUp();
    //NeckLeft();
    //JawDown();
}
