#include<Wire.h>//this library is used for communications with the accel/gyro

//Global Variables
float oldvalue;//establishes each value to be used later in the code, a float is an integer that has decimals
float newvalue;
float oldvalueAccelX;
float oldvalueAccelY;
float oldvalueAccelZ;
float oldvalueGyroX;
float oldvalueGyroY;
float oldvalueGyroZ;
float oldvalueTemp;
float newvalueAccelX;
float newvalueAccelY;
float newvalueAccelZ;
float newvalueGyroX; 
float newvalueGyroY;
float newvalueGyroZ;
float newvalueTemp;

unsigned long timevalue;//establishes these two values
unsigned long timevalue1;

#include<Wire.h>//this library is used for communications with the accel/gyro
const int MPU6050_addr=0x68;//gives the address of the accel/gyro for the Arduino so that it can relay information 
int16_t AccX,AccY,AccZ,Temp,GyroX,GyroY,GyroZ;//all of your integer values are established here, "int's" are integers without decimals

void getValues(){//this is a function that does everything below when the command "getValues" is used
  Wire.beginTransmission(MPU6050_addr);//begins the transmission with the accel/gyro
  Wire.write(0x3B);//^
  Wire.endTransmission(false);//^
  Wire.requestFrom(MPU6050_addr,14,true);//^  
  AccX=Wire.read()<<8|Wire.read();//acquires acceleration in the x direction from the sensor
  AccY=Wire.read()<<8|Wire.read();//acquires acceleration in the y direction from the sensor
  AccZ=Wire.read()<<8|Wire.read();//acquires acceleration in the z direction from the sensor
  Temp=Wire.read()<<8|Wire.read();//acquires tilt in the x direction from the sensor
  GyroX=Wire.read()<<8|Wire.read();//acquires tilt in the y direction from the sensor
  GyroY=Wire.read()<<8|Wire.read();//acquires tilt in the z direction from the sensor
  GyroZ=Wire.read()<<8|Wire.read();//acquires temperature in celsius from the sensor
}
void setup() {
  // put your setup code here, to run once:
  Wire.begin();//same as code in the getValues function
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);//begins serial command with a baud rate of 9600, which is the frequency with which the Arduino "talks"
}

void loop() {
  // put your main code here, to run repeatedly:
  
   
  getValues(); //gets all values and names them "oldvalue"
  oldvalueAccelX = AccX;
  oldvalueAccelY = AccY;
  oldvalueAccelZ = AccZ;
  oldvalueGyroX = GyroX;
  oldvalueGyroY = GyroY;
  oldvalueGyroZ = GyroZ;
  oldvalueTemp = Temp;

  timevalue = millis();//gets an initial starting value for time in milliseconds
  for(int avg = 0;avg < 50;avg++){//for loop averages the acc/gyro data (50 times in this case), ++ the previous value plus one
    getValues();//gets values again and names them "newvalue"
    newvalueAccelX = AccX;
    newvalueAccelY = AccY;
    newvalueAccelZ = AccZ;
    newvalueGyroX = GyroX;
    newvalueGyroY = GyroY;
    newvalueGyroZ = GyroZ;
    newvalueTemp = Temp;
    oldvalueAccelX = (oldvalueAccelX + newvalueAccelX)/2;//adds the old and new values together then divides by two to create a new oldvalue that is the average of two values, this new "oldvalue" is then plugged back into the for loop which runs 50 times.
    oldvalueAccelY = (oldvalueAccelY + newvalueAccelY)/2;//the for loop essentially averages each value 50 times
    oldvalueAccelZ = (oldvalueAccelZ + newvalueAccelZ)/2;
    oldvalueGyroX = (oldvalueGyroX + newvalueGyroX)/2;
    oldvalueGyroY = (oldvalueGyroY + newvalueGyroY)/2;
    oldvalueGyroZ = (oldvalueGyroZ + newvalueGyroZ)/2;
    oldvalueTemp = (oldvalueTemp + newvalueTemp)/2;
}
timevalue1 = millis();//gets a second value of time in milliseconds after the averaging is done
Serial.print("Time :");//https://techneconomyblog.com/tag/latency/- source says that any longer than 330ms in delay is inaccurate
Serial.println(timevalue1-timevalue);//prints the difference btw the two times which tells how long the averaging takes, the average duration is then printed. Gives a delay for the sensor transmission into tactile information.
Serial.print("AccX :");//prints the words within the quotations
Serial.println(oldvalueAccelX);//prints the averaged Accx value and then "hits" enter after because of the println, println prints the value and then starts a new line after.
Serial.print("AccY :");
Serial.println(oldvalueAccelY);
Serial.print("AccZ :");
Serial.println(oldvalueAccelZ);
Serial.print("GyroX :");
Serial.println(oldvalueGyroX);
Serial.print("GyroY :");
Serial.println(oldvalueGyroY);
Serial.print("GyroZ :");
Serial.println(oldvalueGyroZ);
Serial.print("Temp :");
Serial.println(oldvalueTemp/340.00+19.53);
}
