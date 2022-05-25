
int L_1 = 4;
int L_2 = 5;
int R_1 = 6;
int R_2 = 7;

void setup() {
  pinMode(L_1, OUTPUT);
  pinMode(L_2, OUTPUT);
  pinMode(R_1, OUTPUT);
  pinMode(R_2, OUTPUT);

}

void loop() {
  motor(150, -250);
  delay(2000);
  motor(250, -150);
  delay(2000);
  motor(-150, 250);
  delay(2000);
  motor(-250, 150);
  delay(2000);
}

void motor(int mtr_L, int mtr_R){
  if(mtr_L > 0)
  {
    analogWrite(L_1, mtr_L);
    digitalWrite(L_2, LOW);
  }
  else
  {
    analogWrite(L_2, -mtr_L);
    digitalWrite(L_1, LOW);
  }
  if(mtr_R > 0)
  {
    digitalWrite(R_2, LOW);
    analogWrite(R_1, mtr_R);
  }
  else
  {
    digitalWrite(R_1, LOW);
    analogWrite(R_2, -mtr_R);
  }
  
}
