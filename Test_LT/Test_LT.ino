
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT_PULLUP), (A1, INPUT_PULLUP),
          (A2, INPUT_PULLUP), (A3, INPUT_PULLUP),
          (A4, INPUT_PULLUP), (A5, INPUT_PULLUP);
  //(A15,INPUT);
  pinMode(13, OUTPUT), (11, OUTPUT), (10, OUTPUT),
          (9, OUTPUT), (8, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
//  if (digitalRead(A0) == LOW) {
//    digitalWrite(13, HIGH);
//    delay(90);
//    digitalWrite(13, LOW);
//  }
//  else if (digitalRead(A1) == LOW) {
//    motor(0,120);
//  }
//
//  else if (digitalRead(A2) == LOW) {
//    motor(120,0);
//  }
//
//  else if (digitalRead(A3) == LOW) {
//    motor(0,-120);
//  }
//
//  else if (digitalRead(A4) == LOW) {
//   motor(-120,0);
//  }
//  else if (digitalRead(A5) == LOW) {
//    for (int i = 0; i <= 255; i++) {
//      motor(i,i); delay(20);
//    }
//  }
//  else
//  {
//    motor(0,0);
//  }
motor(100,100);
}
void motor(int speedL, int speedR)
{
  if (speedL > 255)speedL = 255;
  else if (speedL < -255)speedL = -255;
  if (speedR > 255)speedR = 255;
  else if (speedR < -255)speedR = -255;

  if (speedL >= 0)
  {
    digitalWrite(10, HIGH); analogWrite(11, speedL);
  }
  else
  {
    digitalWrite(10, LOW); analogWrite(11, abs(speedL));
  }
  if (speedR >= 0)
  {
    digitalWrite(8, HIGH); analogWrite(9, speedR);
  }
  else
  {
    digitalWrite(8, LOW); analogWrite(9, abs(speedR));
  }
}

