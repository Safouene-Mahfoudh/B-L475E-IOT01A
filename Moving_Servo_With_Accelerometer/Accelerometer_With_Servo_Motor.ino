#include <Servo.h>
#include <LSM6DSLSensor.h>
#include <SPI.h>
#include <Wire.h>

SPIClass SPI_3(PC12, PC11, PC10);

#define I2C2_SCL    PB10
#define I2C2_SDA    PB11

LSM6DSLSensor *AccGyr;
TwoWire *dev_i2c;// Create components.


int32_t accelerometer[3];

Servo servo;

void setup() {
    int status;

    Serial.begin(9600);
//*********************_Initialisation_Hum_Temp_Mag_Acc***********************
// Initialize I2C bus.
  dev_i2c = new TwoWire(I2C2_SDA, I2C2_SCL);
  dev_i2c->begin();
  
  // Initlialize components.
  AccGyr = new LSM6DSLSensor(dev_i2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW);
  AccGyr->Enable_X();
    
  servo.attach(8);
  servo.write(90);
}
void loop() 
{ 
  //*******************************Read_Acc***********************************************//
  AccGyr->Get_X_Axes(accelerometer);
  char* msg2 = new char[123];
  int offsett = 0;
  memcpy(msg2 + offsett, reinterpret_cast<char*>(&accelerometer), sizeof(int32_t));


  Serial.print(accelerometer[1]);
  Serial.print(" ");
  Serial.println();

      if ((accelerometer[1] > 0) && (accelerometer[1]<181))  
    {    accelerometer[1] = map(accelerometer[1], -180,0, 180,90);                     
    servo.write(accelerometer[1]);               
    delay(15); }

     if ((accelerometer[1] < 0) && (accelerometer[1]> (-180)))                   
   { accelerometer[1] = map(accelerometer[1], 0,180, 90,0);
    servo.write((accelerometer[1]));               
    delay(15);} 


}
