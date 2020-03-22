// put your setup code here, to run once:
#define A_Dir  12
#define B_Dir  13
#define A_PWM  3
#define B_PWM  11
#define A_I  0
#define B_I  1
#define A_Break  9
#define B_Break  0

#define BallSize 10
int A;
int B;


void setup() {
 Serial.begin(9600);
 Serial.println("starting setup");
 pinMode(A_Dir, OUTPUT);
 pinMode(B_Dir, OUTPUT);
 pinMode(A_PWM, OUTPUT);
 pinMode(B_PWM, OUTPUT);
 pinMode(A_Break, OUTPUT);
 pinMode(B_Break, OUTPUT);
 digitalWrite(A_Break, LOW);
 digitalWrite(B_Break, LOW);
 A = 0;
 B = 0;
}
void enterArena() {

}
void findBall() {

    if ( upperFrontSensor - lowerFrontSensor >= BallSize){
      digitalWrite(A_dir, High);
      digitalWrite(B_dir, Low);
      A = 255;
      B = 255;
      while(upperFrontSensor - lowerFrontSensor >= BallSize ) {
        delay(10);
      }
    }
  return;
}

void fetchBall() {
  //Kör framåt
  digitalWrite(A_dir, High);
  digitalWrite(B_dir, HIGH);
  A = 200;
  B = 200;
  digitalWrite(A_PWM, A);
  digitalWrite(B_PWM, B);
  // till roboten krockar med väggen
  while(upperFrontSensor <= safeWallDistance ) {
    delay(10);
  }
  return;

}

void findNet() {
  //Kolla om nätet är bakom roboten
  if (upperBackSensor - lowerBackSenor < 10) {
    //om nätet är bakom roboten
    return;
  }
  // annars Börja rotera
  digitalWrite(A_dir, High);
  digitalWrite(B_dir, LOW);
  A = 200;
  B = 200;
  digitalWrite(A_PWM, A);
  digitalWrite(B_PWM, B);
  // rotera tills nätet är bakom roboten
  while( upperBackSensor - lowerBackSenor < 10) {
    delay(10);
  }
  return;
}

void throwBall() {
  //Kör bakåt
  digitalWrite(A_dir, High);
  digitalWrite(B_dir, HIGH);
  A = 200;
  B = 200;
  digitalWrite(A_PWM, A);
  digitalWrite(B_PWM, B);
  // till roboten krockar med nätet
  while(upperFrontSensor <= safeWallDistance ) {
    delay(10);
  }

}


void loop() {

  findBall();
  fetchBall();
  findNet();
  throwBall();


}
