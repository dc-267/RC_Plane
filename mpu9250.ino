#include <MPU9250.h>
#include <Wire.h>


MPU9250 IMU(Wire,0x68);

float AccelX,AccelY,AccelZ;
float GyroX,GyroY,GyroZ;
float GyroX_offset=0,GyroY_offset=0,GyroZ_offset=0;
float a,f;
float time_prev,time_curr,time_elapsed;
float pitch_accel,roll_accel,pitch_gyro,roll_gyro,pitch,roll, pitch_c, roll_c;
const float r2d = 180*7/22;
float MagX,MagY,MagZ,Xh,Yh,heading,heading_c;

void readSensors();
void printSensor();
void callibrateSensor();

void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {Serial.print("Serial port not found");}

  IMU.begin();

  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_2G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_250DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);
  a=-0.85;f=90/7;
  callibrateSensor();
}


void loop() {
  /////////////////////////////I M U/////////////////////////////////////
    
    time_curr = millis();  // actual time read
    time_elapsed = (time_curr - time_prev) / 1000; 
    time_prev = time_curr;  // the previous time is stored before the actual time read
  // read the sensor
  readSensors();
  printSensor();
  
 
}

void callibrateSensor()
{
  int i,j;
  Serial.print("Callibrating\n");
  for(i=0;i<1000;i++)
  {
    j=i%20;
    IMU.readSensor();
    GyroX=IMU.getGyroX_rads();
    GyroX_offset += GyroX;
    GyroY=IMU.getGyroY_rads();
    GyroY_offset += GyroY;
    GyroZ=IMU.getGyroZ_rads();
    GyroZ_offset += GyroZ;
    
   Serial.println(i);
  
  }
  
  GyroX_offset /= i;
  GyroY_offset /= i;
  GyroZ_offset /= i;

  Serial.println(GyroX_offset);
  Serial.println(GyroY_offset);
  Serial.println(GyroZ_offset);
}

void readSensors()
{
  IMU.readSensor();
  
  AccelX = IMU.getAccelX_mss();
  AccelY = IMU.getAccelY_mss();
  AccelZ = IMU.getAccelZ_mss();

  pitch_accel = atan(AccelY/sqrt(pow(AccelX,2)+pow(AccelZ,2)));
  roll_accel = atan(-1*AccelX/sqrt(pow(AccelY,2)+pow(AccelZ,2)));

GyroX = IMU.getGyroX_rads()-GyroX_offset ;
  GyroY = IMU.getGyroY_rads()-GyroY_offset ;
  GyroZ = IMU.getGyroZ_rads()-GyroZ_offset ;

  pitch_gyro = (GyroX * time_elapsed);
  roll_gyro = GyroY *time_elapsed; 
 
  pitch = 0.96*(pitch+pitch_gyro*time_elapsed)+0.04*(pitch_accel);
  roll = 0.96*(roll+roll_gyro*time_elapsed)+0.04*(roll_accel);

  pitch_c=(pitch*f)-(roll*f) * sin(GyroZ * 0.000001066); // corrected values
  roll_c=(roll*f)+(pitch*f) * sin(GyroZ * 0.000001066);
 MagX = IMU.getMagX_uT();
 MagY = IMU.getMagY_uT();
 MagZ = IMU.getMagZ_uT();


 //Xh = MagX*cos(pitch_accel)+MagY*sin(roll_accel)*sin(pitch_accel)-MagZ*cos(roll_accel)*sin(pitch_accel);
 //Yh = MagY*cos(roll_accel)+MagZ*sin(roll_accel);

 Yh = MagX*sin(roll_c)*sin(pitch_c)+MagY*cos(roll_c)-MagZ*sin(roll_c)*cos(pitch_c);
 Xh = MagX*cos(pitch_c)+MagZ*sin(pitch_c);

 

/* if(Xh<0)
  heading = 180-atan(Yh/Xh)*r2d;
 else if(Xh>0)
  {
    if(Yh<0)
      heading = -atan(Yh/Xh)*r2d;
    else if(Yh>0)
      heading = 360 - atan(Yh/Xh)*r2d;
  }
 else if(Xh == 0)
  {
    if(Yh>0)
      heading = 270;
    if(Yh<0)
      heading = 90;
  }*/

  heading = atan2(Yh,Xh)*r2d;

  
}


void printSensor()
{

  Serial.print(pitch_c*r2d);
  Serial.print("\t");
  Serial.print(roll_c*r2d);
  Serial.print("\t");
  Serial.print(MagX);
  Serial.print("\t");
  Serial.print(MagY);
  Serial.print("\t");
  Serial.print(MagZ);
  Serial.print("\t");
  Serial.println(heading);/**/


 // Serial.println(heading);

 
  

  
}
