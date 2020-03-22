// Motorshield pins
#define A_Dir  12
#define B_Dir  13
#define A_PWM  3
#define B_PWM  11
#define A_I  0
#define B_I  1
#define A_Break  9
#define B_Break  0
//left right motor
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
 Serial.println("Finished setup");
}
boolean checkForBall() {
  //KOD för att läsa av fram sensorererna och avgöra om en boll är där
}
boolean checkForNet() {
  //kod för att läsa av baksensorer och avgöra om nätet är i den riktningen
}

boolean checkForWall() {
  //känn av en vägg på ett säkert avstånd
}

void enterArena() {
// kod för att gå in på planen
}
void findBall() {

    if ( checkForBall()){
      digitalWrite(A_dir, HIGH);
      digitalWrite(B_dir, Low);
      A = 200;
      B = 200;
      while(!checkForBall()) {
        delay(10);
      }
    }
  return;
}

void fetchBall() {
  //Kör framåt
  digitalWrite(A_dir, HIGH);
  digitalWrite(B_dir, HIGH);
  A = 200;
  B = 200;
  analogWrite(A_PWM, A);
  analogWrite(B_PWM, B);
  // till roboten krockar med väggen
  while(!checkForWall() ) {
    delay(10);
  }
  return;

}

void findNet() {
  //Kolla om nätet är bakom roboten
  if (checkForNet()) {
    //om nätet är bakom roboten
    return;
  }
  // annars Börja rotera
  digitalWrite(A_dir, HIGH);
  digitalWrite(B_dir, LOW);
  A = 200;
  B = 200;
  analogWrite(A_PWM, A);
  analogWrite(B_PWM, B);
  // rotera tills nätet är bakom roboten
  while( !checkForNet) {
    delay(10);
  }
  return;
}

void throwBall() {
  //Kör bakåt ..
  digitalWrite(A_dir, LOW);
  digitalWrite(B_dir, LOW);
  A = 200;
  B = 200;
  analogWrite(A_PWM, A);
  analogWrite(B_PWM, B);
  // .. till roboten krockar med nätet
  while(!checkForWall() ) {
    delay(10);
  }

  //TODO: kasta bollen

}

void backAndForth() {
  A = 200;
  B = 200;
  for(int i = 0; i < 5; i++;) {
    digitalWrite(A_Dir, HIGH);
    digitalWrite(B_Dir, HIGH);
    analogWrite( A_PWM, A);
    analogWrite( B_PWM, B);
    delay(1000);
    digitalWrite(A_Dir, LOW);
    digitalWrite(B_Dir, LOW);
    delay(1000);
  }
}

void rotate() {
  digitalWrite(A_dir, HIGH);
  digitalWrite(B_dir, LOW);
  A = 200;
  B = 200;
  analogWrite(A_PWM, A);
  analogWrite(B_PWM, B);
  delay(2000);
  digitalWrite(A_dir, LOW);
  digitalWrite(B_dir, HIGH);
}

void circle() {
  for(int i = 0; i < 2; i++;) {
    A = 200;
    B = 50;
    digitalWrite(A_Dir, HIGH);
    digitalWrite(B_Dir, HIGH);
    analogWrite( A_PWM, A);
    analogWrite( B_PWM, B);
    delay(1000);
    B = 200;
    A = 50;
    analogWrite( A_PWM, A);
    analogWrite( B_PWM, B);
    delay(1000);
  }
}


void loop() {
  Serial.println("starting loop");
  //findBall();
  //fetchBall();
  //findNet();
  //throwBall();
  //Upvisningskod
  //gitpill
  Serial.println("starting backAndForth");
  backAndForth();
  Serial.println("starting Rotate");
  rotate();
  Serial.println("starting Circle");
  circle();


}
