#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelerometer;
int16_t ax;
int16_t ay;
int16_t az;
int16_t ac;
float acc;
float minimum;
float maximum;
float amp;
float amp_avg;
unsigned long long timer1s;
unsigned long long timer60s;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  accelerometer.initialize();
  accelerometer.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);

  minimum = 0;
  maximum = 0;
  timer1s = 0;
  timer60s = 0;
  
  delay(100);
}

void loop()
{
  
  accelerometer.getAcceleration(&ax, &ay, &az);
  
  ac = (abs(ax) + abs(ay) + abs(az));
  acc = float(ac) / 32768 * 20;
  //Serial.println(acc);

  if(acc > maximum){
    maximum = acc;
    }

  if(acc < minimum){
    minimum = acc;
    }

  if(millis() - timer1s >= 500){
    amp = maximum - minimum; 
    amp_avg += amp;
    Serial.println(amp);
    minimum = acc;
    maximum = acc;
    timer1s = millis();
    }

  if(millis() - timer60s >= 60000){
    amp_avg = amp_avg/120;
    Serial.print("Average ampl: ");
    Serial.println(amp_avg);
    amp_avg = 0;
    timer60s = millis();
    }
  
}
