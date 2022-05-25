#include <Wire.h>
#define SENSOR_ID 31

int hitung = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Wire.begin();
  // put your setup code here, to run once:

  pinMode(13, OUTPUT), (11, OUTPUT), (10, OUTPUT),
          (9, OUTPUT), (8, OUTPUT);
  intersectionL();
  //motor(30 , 100 );
}

void loop() {
  //   put your main code here, to run repeatedly:
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
  //  line_follow();
}

int dtSensor[7];
int i2c_read(int id)

{
  Wire.requestFrom(id, 1);        // request 1 bytes from slave device #ID
  int data = 0;
  while (Wire.available())
  { // slave may send less than requested
    data = Wire.read();         // receive a byte as character
  }

  dtSensor[6] = ((data & 0b00100000) >> 5);
  dtSensor[5] = ((data & 0b00010000) >> 4);
  dtSensor[4] = ((data & 0b00001000) >> 3);
  dtSensor[3] = ((data & 0b00000100) >> 2);
  dtSensor[2] = ((data & 0b00000010) >> 1);
  dtSensor[1] =   data & 0b00000001;
  return data;
}

void motor(int speedL, int speedR)
{
  if (speedL > 255)speedL = 255;
  else if (speedL < -255)speedL = -255;
  if (speedR > 255)speedR = 255;
  else if (speedR < -255)speedR = -255;

  if (speedR>= 0)
  {
    digitalWrite(10, HIGH); analogWrite(11, 255-speedR);
  }
  else
  {
    digitalWrite(10, LOW); analogWrite(11, abs(speedR));
  }
  if (speedL >= 0)
  {
    digitalWrite(8, HIGH); analogWrite(9, speedL);
  }
  else
  {
    digitalWrite(8, LOW); analogWrite(9, abs(speedL));
  }
}

int dtSensorAll;
void line_follow() {
  dtSensorAll = i2c_read(SENSOR_ID);
  //    Serial.println(dtSensorAll,BIN);
  switch (dtSensorAll)
  {
    // 0bxx654321
    case 0b00000001 : motor(100 , -50 ); break;
    case 0b00000010 : motor(120 ,  50 ); break;
    case 0b00000110 : motor(150 , 100 ); break;
    case 0b00000100 : motor(150 , 130 ); break;
    case 0b00001100 : motor(150 , 150 ); break;
    case 0b00001000 : motor(130 , 150 ); break;
    case 0b00011000 : motor(100 , 150 ); break;
    case 0b00010000 : motor( 50 , 120 ); break;
    case 0b00100000 : motor(-50 , 100 ); break;
  }
  delay(8);
}

int dot;
void intersectionLR() {
  line_follow();
  //kondisi non ideal...
  while (dtSensor != 0b00000000) {
    line_follow();
  }
  motor(0, 0); delay(500);
}

void intersectionR() {
  line_follow();
  //kondisi non ideal...
  while (!dtSensor[6]) {
    line_follow();
  }
  if (dtSensor[6] == 1)
  {
    if (hitung > 200)
    {
      hitung = 200;
    }
    hitung++;

    if (hitung < 9) {
      line_follow();
      Serial.println("titik");
    }
    else {
      intersectionLR();
      Serial.println("intersectionR()");
    }
  }
  else hitung = 0;
}

void intersectionL() {
  int validCount=0;
  line_follow();line_follow();line_follow();line_follow();line_follow();line_follow();line_follow();
  //kondisi non ideal...
  Serial.println("find intersection L");
  while(validCount<20)
  {
    if(dtSensor[6]) validCount++;
    else validCount=0;
    line_follow();  
    
  }
  while (dtSensor[6]) {
    line_follow();    
  }
  
  Serial.println("intersection L detected");
  //  if (dtSensor[1] == 1)
  //  {
  //    if (hitung > 200) {
  //      hitung = 200;
  //    }
  //    hitung++;
  //
  //    if (hitung < 9) {
  //      line_follow();
  //      Serial.println("titik");
  //    }
  //    else {
  //      intersectionLR();
  //      Serial.println("intersectionL()");
  //    }
  //  }
  //  else hitung = 0;
  motor(0,0);
}
