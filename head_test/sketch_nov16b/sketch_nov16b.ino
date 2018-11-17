#include <Servo.h>
Servo test;
bool jawMode = false;
bool neckMode = false;

void setup() {
  // put your setup code here, to run once:
  test.attach(3);
  Serial.begin(9600);
}

void moveToNeck(int thePos){
  int pos = 0;
  int increment = 0;
  if(thePos > test.read()){
    for (pos = test.read(); pos <= thePos; pos+=1){
      // Serial.println(pos);
      test.write(pos);
      delay(20);
      increment++;
//      if (increment == 10){
//        delay(500);
//        increment = 0;
//      }
    }
  }
  else{
    for (pos = test.read(); pos >= thePos; pos -= 1){
      // Serial.println(pos);
      test.write(pos);
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
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){

    int per = Serial.parseInt();

    if(!jawMode && !neckMode && (per >=30 && per <= 150)){
      Serial.println("MOVED");
      moveToNeck(per);
       Serial.print("moved ");
       Serial.println(per);
       Serial.print("Head Pos: ");
       Serial.println(test.read());
    }
  }
}
