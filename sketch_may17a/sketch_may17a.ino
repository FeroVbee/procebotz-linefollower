#include <Wire.h>
#define SENSOR_ID 31

void setup() 
{
  // put your setup code here, to run once:
  Wire.begin();
}

void loop() 
{
  // put your main code here, to run repeatedly:
 
}

int dtSensor[7];
int i2c_read(int id)
{
  Wire.requestFrom(id, 1);        // request 1 bytes from slave device #ID
  int data = 0;
  while (Wire.available()) {      // slave may send less than requested
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

int L_1 = 4;
int L_2 = 5;
int R_1 = 6;
int R_2 = 7;

void motor(int speedL, int speedR)
{

    if(speedL > 0)
  {
    analogWrite(L_1, speedL);
    digitalWrite(L_2, LOW);
  }
  else
  {
    analogWrite(L_2, -speedL);
    digitalWrite(L_1, LOW);
  }
  if(speedR > 0)
  {
    digitalWrite(R_2, LOW);
    analogWrite(R_1, speedR);
  }
  else
  {
    digitalWrite(R_1, LOW);
    analogWrite(R_2, -speedR);
  }
  
/*  if (speedL<speedR)turnLeft(speedL,speedR,5);
    else if (speedL>speedR)turnRight(speedL,speedR,2);
    else turnForard(speedL,speedR); */
}

int dtSensorAll;
void line_follow(){
    dtSensorAll = i2c_read(SENSOR_ID);
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
}

void intersectionR(int jumlahCabang){
    line_follow();
    //kondisi ideal...
    while (!dtSensor[6]) {
       line_follow();
    }
    motor(0, 0); delay(500);
}

void intersectionL(int jumlahCabang){
    line_follow(); 
    //kondisi ideal...
    while (!dtSensor[1]) {
       line_follow();
    }
    motor(0, 0); delay(500);
}


void intersectionLR(int jumlahCabang){
    line_follow();
    //kondisi ideal...
    while (dtSensor != 0b00000000) {
       line_follow();
    }
    motor(0, 0); delay(500);
}


//belok kiri sampai "sensorNumb" ketemu garis, ex: turnLeft(-100,100,4);
void turnLeft(int speedL, int speedR, int sensorNumb){
    intersectionL(2);
    intersectionLR(2);
    
}
//belok kanan sampai "sensorNumb" ketemu garis, ex: turnRight(100,-100,3);
void turnRight(int speedL, int speedR, int sensorNumb){
    intersectionLR(2);
}
void turnForward(int speedL, int speedR){
  intersectionL(2);
  
  }
