#include <Wire.h>
#define SENSOR_ID 32

int hitung=0;

void setup() {
	// put your setup code here, to run once:
	Wire.begin();
}

void loop() {
	line_follow();

}

int dtSensor[7];
int i2c_read(int id)

{
	Wire.requestFrom(id, 1);        // request 1 bytes from slave device #ID
	int data = 0;
	while (Wire.available()) 
  	{   						            	// slave may send less than requested
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
  if(speedL > 0) {
    analogWrite(L_1, speedL);
    digitalWrite(L_2, LOW);
  }
  else {
    analogWrite(L_2, -speedL);
    digitalWrite(L_1, LOW);
  }

  if(speedR > 0) {
    digitalWrite(R_2, LOW);
    analogWrite(R_1, speedR);
  }
  else {
    digitalWrite(R_1, LOW);
    analogWrite(R_2, -speedR);
  }
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

int dot;
void intersectionLR(){
    line_follow();
    //kondisi non ideal...
    while (dtSensor != 0b00000000) {
       line_follow();
    }
    motor(0, 0); delay(500);
}

void intersectionR(int jumlahCabang){
    line_follow();
    //kondisi non ideal...
    while (!dtSensor[6]) {
       line_follow();
    }
    if (dtSensor[6]==1)
    {
      if (hitung>200)
        {hitung=200;}
      hitung++;

         if (hitung < 9) line_follow();
            else intersectionLR();
      }
    else hitung=0; 
}

void intersectionL(int jumlahCabang){
    line_follow(); 
    //kondisi non ideal...
    while (!dtSensor[1]) {
       line_follow();
    }
    if (dtSensor[1]==1)
    {
      if (hitung>200){hitung=200;}
      hitung++;

        if (hitung < 9) line_follow();
           else intersectionLR();
      }
    else hitung=0;
}

//belok kiri sampai "sensorNumb" ketemu garis, ex: turnLeft(-100,100,4);
void turnLeft(){
	  intersectionL(3);
    motor(50 ,  120 );
    if(dtSensor[3]&&dtSensor[4]==1)
      line_follow();
    }

//belok kanan sampai "sensorNumb" ketemu garis, ex: turnRight(100,-100,3);
void turnRight(){
  while(!dtSensor[2])
    line_follow();
  while(dtSensor[3]&&dtSensor[4]==1)
    motor(120 ,  50 );
  while(dtSensor[3]&&dtSensor[4]!=1)
    motor(120 ,  50 );
  line_follow();
}
//
//int tanda;
//void tetap_lurus(){
//  if(dtSensor[1]&&dtSensor[6]==1)
//    motor(100,100);
//  else
//    line_follow();  
//  }
//
//void tiga_intersectionR(){
//  oi:
//  if (tetap_lurus()='1') tanda+1;
//  goto oi;
//  if (tanda==3)  
//    turnRight();
//    }
