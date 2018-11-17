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
Servo digitOne;
Servo digitTwo;
Servo digitThree;
Servo digitFour;
Servo digitFive;
// Port 3 and 4 are broken.

int headPos = 0;
int jawPos = 0;
int NeckPos = 0;
int SwitchPin = 8;
boolean isReady = false;
boolean LastButton = LOW;
boolean RobotOn = false;
boolean handMode = false;
boolean neckMode = false;
boolean printMode = false;

#define NECKPIN 7
#define HEADPIN 6
#define DIGITFIV 5
#define DIGITFOR 4
#define DIGITTHR 3
#define DIGITTWO 2
#define DIGITONE 1



void setup() {
 myNeck.attach(NECKPIN);
 myHead.attach(HEADPIN);
 digitOne.attach(DIGITONE);
 digitTwo.attach(DIGITTWO);
 digitThree.attach(DIGITTHR);
 digitFour.attach(DIGITFOR);
 digitFive.attach(DIGITFIV);
 Serial.begin(9600);

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
      delay(20);
    }
  }
  else{
    for (pos = myHead.read(); pos >= thePos; pos -= 1){
      myHead.write(pos);
      delay(20);      
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
    }
  }
  else{
    for (pos = myNeck.read(); pos >= thePos; pos -= 1){
      // Serial.println(pos);
      myNeck.write(pos);
      delay(20);      
      increment++;

    }
  }
}


void moveToHand(int thePos){
  int pos = 0;
  int increment = 0;
  if(thePos == 10){
    // thumb up
    for(pos = 0; pos <=180; pos += 1){
      digitOne.write(pos);
      digitTwo.write(pos);
      digitThree.write(pos);
      digitFour.write(pos);
      digitFive.write(pos);
      delay(5);
    }
  }
  else{
    // thumb down
    for(pos = 180; pos >=0; pos -= 1){
      digitOne.write(pos);
      digitTwo.write(pos);
      digitThree.write(pos);
      digitFour.write(pos);
      digitFive.write(pos);
      delay(5);
    }
  }
}

void loop() {

  if (Serial.available() > 0){

    int per = Serial.parseInt();

    if(!handMode && !neckMode && (per >=20 && per <= 160)){
      moveToHead(per);
      if(printMode){
       Serial.print("moved ");
       Serial.println(per);
       Serial.print("Head Pos: ");
       Serial.println(myHead.read());
      }
    }

    else if(!handMode && neckMode && (per >=20 && per <= 160)){
      moveToNeck(per);
      if(printMode){
       Serial.print("moved ");
       Serial.println(per);
       Serial.print("Neck Pos: ");
       Serial.println(myNeck.read());
      }
    }
    
    else if(handMode && !neckMode && (per == 9 || per == 10)){
      moveToHand(per);
      if(printMode){
       Serial.print("moved ");
       Serial.println(per);
       Serial.print("Hand Pos: ");
      }
    }

    else if(per == 2){
      if(printMode){
       Serial.println("Hand Mode");
      }
      neckMode = false;
      handMode = true;
    }
    else if(per == 1){
      if(printMode){
       Serial.println("Neck Mode");
      }
      neckMode = true;
      handMode = false;
    }
    else if(per == 0){
      if(printMode){
       Serial.println("Head Mode");
      }
      handMode = false;
      neckMode = false;
    }
    else if(per == -99){
      Serial.println("Toggle Print Mode");
      printMode = !printMode;
    }

  }

}
