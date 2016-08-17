#include <Servo.h>
#include <Average.h>

Servo Servo1;
Servo Servo2;

Average<float> ave(7);
Average<float> ave2(49);

int sensorRead1[180];
int movement_treshold = 1.8; //1 is constantly moving, 1.5 is like ideal 2 might not move at all
int movement_speed = 2; //1 is normal meaning delay 200 after every movement 2 gets faster meaning delay 100
float lightIndex;
 int Pos1;
 int Pos2;

int sensorPin = A0;
int sensorValue = 0;

//functions
void LOOK_AROUND(){
  //X
  int maxat = 0;
  int maxat2 = 0;
  
  for(int i = 0; i <= 6; i += 1){
    // 0 30 60 90 120 150 180
    Servo2.write(i*30);
   //delay(1);
    //sensorValue = analogRead(sensorPin);
    ave.push(i);
    //Serial.println(analogRead(sensorPin));
    delay(100);
    if(i%2 == 0){
    for(int z = 0; z <= 6; z += 1){
      Servo1.write(z*30);
      ave2.push(analogRead(sensorPin));
      //Serial.println(analogRead(A0));
      delay(200);
      }}
     if(i%2 == 1) {
      for(int a = 6; a >= 0; a -= 1){
      Servo1.write(a*30);
      ave2.push(analogRead(sensorPin));
      //Serial.println(analogRead(A0));
      delay(200);
      }
      }
    }
   lightIndex = (ave.mean()+ave2.mean())/2;
   
  ave.maximum(&maxat);
 ave2.maximum(&maxat2);
delay(1);


Serial.println("maxat1:         ");Serial.println(maxat); 
for (int i = 0; i < 7; i++) {
        Serial.print(ave.get(i));
        Serial.print(" ");
    }
Serial.println("makat2:          ");Serial.println(maxat2);
for (int i = 0; i < 49; i++) {
        Serial.print(ave2.get(i));
        Serial.print(" ");
    }
delay(1);
int maxAtNumber = maxat2+1;
int servoPos2 = ((maxAtNumber-(maxAtNumber%7))/7)*30;
int servoPos1;
if(((maxAtNumber-(maxAtNumber%7))/7)%2 == 0){
  servoPos1 = ((maxAtNumber)%7)*30;
}
else if (((maxAtNumber-(maxAtNumber%7))/7)%2 == 1){
  servoPos1 = (7-((maxAtNumber)%7))*30;
}
Serial.println(servoPos2);
Servo2.write(servoPos2);
Servo1.write(servoPos1);

   Pos1 = servoPos1;
   Pos2 = servoPos2;
delay(1);
}

void MOVE_AROUND(){

  int initialSensor = analogRead(sensorPin);
  int right1;
  int left1;
  int top1;
  int bot1;

  Servo1.write(Pos1);   delay(200/movement_speed);
  Servo2.write(Pos2);   delay(200/movement_speed);

//right1 
  Servo1.write(Pos1+5);   delay(200/movement_speed);
  right1 = analogRead(A0);
  //Servo1.write(Pos1);   delay(200/movement_speed);

//left1
  Servo1.write(Pos1-5);   delay(200/movement_speed);
  left1 = analogRead(A0);
  //Servo1.write(Pos1);   delay(200/movement_speed);
 
//top1
  Servo2.write(Pos2+5);   delay(200/movement_speed);
  top1 = analogRead(A0);
  //Servo2.write(Pos2);   delay(200/movement_speed);
  
//bottom1
  Servo2.write(Pos2-5);   delay(200/movement_speed);
  bot1 = analogRead(A0);
  //Servo2.write(Pos2);   delay(200/movement_speed);
  delay(50);
//choose New Pos
boolean rightA;
boolean leftA;
boolean topA;
boolean botA;

//right left
if(right1 > (initialSensor*movement_treshold)){
  
    //right is ascending
    rightA = true;
 
}
if(left1 > (initialSensor*movement_treshold)){
    //left is ascending
    leftA = true;  
}
//top bot
if(top1 > (initialSensor*movement_treshold)){
 
    //top is ascending
    topA = true;
  
}

if(bot1 > (initialSensor*movement_treshold)){
 
    //bot is ascending
    botA = true;
  
}
if(rightA && !leftA){
  //right
  if(Pos1 < 175){
  Pos1 += 5;
  }
}
if(!rightA && leftA){
  //left
  if(Pos1 > 5){
  Pos1 -= 5;
  }
}
if(topA && !botA){
  //top
  if(Pos2 < 150){
  Pos2 += 5;}
}
if(!topA && botA){
  //bot
  if(Pos2 >30){
  Pos2 -= 5;}
}
if(rightA && leftA){
  if(right1 > left1){
    //right
    if(Pos1 < 175){
      Pos1 += 5;
    }
  }
  else if(left1 > right1){
    //left
   if(Pos1 > 5){
    Pos1 -= 5;
   }
  }
}
if(topA && botA){
  if(top1 > bot1){
    //top
    if(Pos2 < 150){
     Pos2 += 5;}
  }
  else if(bot1 > top1){
    //bot
    if(Pos2 > 30){
     Pos2 -= 5;}
  }
}

}

//functions

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Servo1.attach(9);
Servo2.attach(8);
LOOK_AROUND();

}

void loop() {
MOVE_AROUND();
delay(50);

}

