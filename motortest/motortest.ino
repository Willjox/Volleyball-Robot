#include <Servo.h>
Servo myservo1;  // create servo object to control a servo
Servo myservo2;

int pos, pos2;

// Motorshield pins
#define A_Dir  12 //RIGHT
#define B_Dir  13 //LEFT
#define A_PWM  3
#define B_PWM  11
#define A_I  0
#define B_I  1
#define A_Break  9
#define B_Break  0
#define led1 53
#define led2 23

#define trigPin_BackUp 26
#define echoPin_backUp 27

#define trigPin_BackLow 44
#define echoPin_backLow 45

//Pins for dReader
#define trigPin_upper  43
#define echoPin_upper 41

const int lower_dreader = 39;

long duration, upperCm, lowerCm, cm;

void setup() {
  Serial.begin(9600);

  // SERVO
  myservo1.attach(27);
  myservo2.attach(37);

 // MOTOR PINS
  pinMode(A_Dir, OUTPUT);
  pinMode(B_Dir, OUTPUT);
  pinMode(A_PWM, OUTPUT);
  pinMode(B_PWM, OUTPUT);
  pinMode(A_Break, OUTPUT);
  pinMode(B_Break, OUTPUT);

  // DISTANCE READER PINS
  pinMode(trigPin_upper, OUTPUT);
  pinMode(echoPin_upper, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(A_Break, LOW);
  digitalWrite(B_Break, LOW);
  pos2 = 0;
  pos = 90;

  for (pos; pos >= 0; pos -= 1) {// goes from 180 degrees to 0 degrees
    myservo1.write(pos);        // tell servo to go to position in variable 'pos'
    myservo2.write(pos2);
    pos2 += 1;
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  delay(3000);
}


void loop() {
  //enterArena();
  //ballstate();
  //drivetoball();
  //pickupball();
  //backup();
  netState();  //Använd kompass?
  drivetonet();
  //score();    //Använd servo
}

void enterArena() {
  digitalWrite(A_Dir, LOW);
  digitalWrite(B_Dir, LOW);
  unsigned long startTime = millis();
  while(startTime - millis() < 5000) {
    analogWrite(A_PWM, 255);
    analogWrite(B_PWM, 200 );
  }


}

void ballstate(){
  digitalWrite(A_Dir, HIGH);
  digitalWrite(B_Dir, LOW);
  delay(5);
  int x = 0;
  while(x < 7){
    x = 0;
    analogWrite(A_PWM, 255);
    analogWrite(B_PWM, 255 );
    delay(50);
    analogWrite(A_PWM, 0);
    analogWrite(B_PWM, 0);
    delay(1000);
    for(int i = 0; i < 10; i++) {
      x = x + findBall();
    }
  }
  digitalWrite(led2, LOW);
}

long ping(int trigPin , int echoPin) {
  if (trigPin == 39){
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
  } else{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
  }

  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  //Serial.println(cm);
  return(cm);
}

int findBall(){
  upperCm = ping(trigPin_upper, echoPin_upper);
  if (upperCm > 200) {
    upperCm = 200;
  }
  lowerCm = ping(lower_dreader, lower_dreader);
  Serial.print(upperCm);
  Serial.print(" ");
  Serial.println(lowerCm);
  delay(10);

  if(lowerCm < (upperCm - 4)){
    digitalWrite(led1, HIGH);
    return 1;

  } else{
    digitalWrite(led1, LOW);
    return 0;
  }
}

void drivetoball(){

  for (pos; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees// in steps of 1 degree
    myservo1.write(pos);// tell servo to go to position in variable 'pos'
    myservo2.write(pos2);
    pos2 -= 1;
    delay(5);                       // waits 15ms for the servo to reach the position
  }

  int x = 0;
  long dist;
  unsigned long startTime = millis();
  while(x < 3){
    x = 0;
    for(int i = 0; i < 3; i++) {
        dist = ping(trigPin_upper, echoPin_upper);
        if (dist < 30) {
          x++;
        }
      }
      if  (startTime - millis() > 20000) {
          break;
      }
    digitalWrite(A_Dir, LOW);
    digitalWrite(B_Dir, LOW);
    analogWrite(A_PWM, 255); //Ändrad
    analogWrite(B_PWM, 200 );
  }
  analogWrite(A_PWM, 0);
  analogWrite(B_PWM, 0);
  delay(500);
}

void pickupball(){

}

void backup(){
  int x = 0;
  long dist;
  unsigned long startTime = millis();
  while(x < 3){
    x = 0;
    for(int i = 0; i < 10; i++) {
        dist = ping(trigPin_upper, echoPin_upper);
        if (dist > 80 ) {
          x++;
        }
    }
    digitalWrite(A_Dir, HIGH);
    digitalWrite(B_Dir, HIGH);
    analogWrite(A_PWM, 255);
    analogWrite(B_PWM, 180);
    if (startTime - millis() > 20000) {
      break;
    }
  }

  while(true){
    analogWrite(A_PWM, 0);
    analogWrite(B_PWM, 0);
  }
}



int findNet() {
  upperCm = ping(trigPin_BackUp, echoPin_backUp);
  if (upperCm > 250) {
    upperCm = 250;
  }
  lowerCm = ping(trigPin_BackLow, echoPin_backLow);
  Serial.print(upperCm);
  Serial.print(" ");
  Serial.println(lowerCm);
  delay(10);

  if(lowerCm < (upperCm - 10)){
    digitalWrite(led1, HIGH);
    return 1;

  } else{
    digitalWrite(led1, LOW);
    return 0;
  }
}

void netState() {
  digitalWrite(A_Dir, HIGH);
  digitalWrite(B_Dir, LOW);
  delay(5);
  int x = 0;
  while(x < 7){
    x = 0;
    analogWrite(A_PWM, 255);
    analogWrite(B_PWM, 255 );
    delay(50);
    analogWrite(A_PWM, 0);
    analogWrite(B_PWM, 0);
    delay(1000);
    for(int i = 0; i < 10; i++) {
      x = x + findNet();
    }
  }
  digitalWrite(led2, LOW);
}

void drivetonet(){
  int x = 0;
  long dist;
  unsigned long startTime = millis();
  while(x < 3){
    x = 0;
    for(int i = 0; i < 3; i++) {
        dist = ping(trigPin_BackLow, echoPin_backLow);
        if (dist < 30) {
          x++;
        }
      }
      if  (startTime - millis() > 20000) {
          break;
      }
    digitalWrite(A_Dir, HIGH);
    digitalWrite(B_Dir, HIGH);
    analogWrite(A_PWM, 255); //Ändrad
    analogWrite(B_PWM, 200 );
  }
  analogWrite(A_PWM, 0);
  analogWrite(B_PWM, 0);
  delay(500);
}


//  Converts time in microseconds from distance readers and RETURNS value in cm.
//
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
