// put your setup code here, to run once:
#define A_Dir  12
#define B_Dir  13
#define A_PWM  3
#define B_PWM  11
#define A_I  0
#define B_I  1
#define A_Break  9
#define B_Break  0
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
 A = 50;
 B = 50;
}

void loop() {

 digitalWrite(A_Dir, HIGH);
 digitalWrite(B_Dir, HIGH);
 analogWrite( A_PWM, A);
 analogWrite( B_PWM, B);
 delay(500);
 Serial.println("yo");
 //analogWrite( A_PWM, 100);
 Serial.println("no");
 //analogWrite( B_PWM, 100);

 digitalWrite(A_Dir, LOW);
 digitalWrite(B_Dir, LOW);
 delay(500);
 A++;
 B++;


}
