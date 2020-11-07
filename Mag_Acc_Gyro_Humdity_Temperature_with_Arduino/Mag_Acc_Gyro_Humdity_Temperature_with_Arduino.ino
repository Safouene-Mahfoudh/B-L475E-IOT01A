#include <HTS221Sensor.h>
#include <LPS22HBSensor.h>
#include <LIS3MDLSensor.h>
#include <LSM6DSLSensor.h>

#include <SPI.h>


//***************************_Config_de_Temp-Hum_Press********************
#define I2C2_SCL    PB10
#define I2C2_SDA    PB11

HTS221Sensor  *HumTemp;
LPS22HBSensor *PressTemp;
LIS3MDLSensor *Magneto;
LSM6DSLSensor *AccGyr;
TwoWire *dev_i2c;

uint8_t Msg_hum;
uint8_t Msg_temp;
uint8_t Msg_mag_x;
uint8_t Msg_mag_y;
uint8_t Msg_mag_z;
uint8_t Msg_acc_x;
uint8_t Msg_acc_y;
uint8_t Msg_acc_z;

uint8_t All_Msg_to_send[64];

int32_t magnetometer[3];
int32_t accelerometer[3];
float pressure ,temperature ,humidity;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  
  Serial.begin(115200);
  
  
// Initialize I2C bus.
  dev_i2c = new TwoWire(I2C2_SDA, I2C2_SCL);
  dev_i2c->begin();
  
  // Initlialize components.
  HumTemp = new HTS221Sensor (dev_i2c);
  HumTemp->Enable();

  Magneto = new LIS3MDLSensor(dev_i2c);
  Magneto->Enable();

  AccGyr = new LSM6DSLSensor(dev_i2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW);
  AccGyr->Enable_X();
}


void loop() {
  
//*******************************Read_humidity*******************************************//
  HumTemp->GetHumidity(&humidity);
  int humidityy =(char )humidity ;

//*******************************Read_temperature*******************************************//
  HumTemp->GetTemperature(&temperature);
  int ttemperature =(char )temperature ;
  

//*******************************Read_Acc_and_convert***********************************************//
  AccGyr->Get_X_Axes(accelerometer);
  char* msg2 = new char[123];
  int offsett = 0;
  memcpy(msg2 + offsett, reinterpret_cast<char*>(&accelerometer), sizeof(int32_t));


//*******************************Read_Magneto_and_convert*******************************************//
Magneto->GetAxes(magnetometer);
char* msg = new char[123];
int offset = 0;
memcpy(msg + offset, reinterpret_cast<char*>(&magnetometer), sizeof(int32_t));


//*******************************Read_all_the_Msg***************************************//
sprintf((char *)Msg_acc_x,"%d",accelerometer[0]);
sprintf((char *)Msg_acc_y,"%d",accelerometer[1]);
sprintf((char *)Msg_acc_z,"%d",accelerometer[2]);
sprintf((char *)Msg_mag_x,"%d",magnetometer[0]);
sprintf((char *)Msg_mag_y,"%d",magnetometer[1]);
sprintf((char *)Msg_mag_z,"%d",magnetometer[2]);
sprintf((char *)Msg_hum,"%d",humidityy);
sprintf((char *)Msg_temp,"%d",ttemperature);

// Or send all the data using regrouped with sprintf
//sprintf((char *)All_Msg_to_send,"%d%d%d%d%d%d%d%d%d%d \n",accelerometer[0],accelerometer[1],accelerometer[2],magnetometer[0],magnetometer[1],magnetometer[2],humidityy,ttemperature); 
//Serial.print((char*)All_Msg_to_send);

 
Serial.print(accelerometer[0]);
Serial.print(" ");
Serial.print(accelerometer[1]);
Serial.print(" ");
Serial.print(accelerometer[2]);
Serial.print(" ");

Serial.print(magnetometer[0]);
Serial.print(" ");
Serial.print(magnetometer[1]);
Serial.print(" ");
Serial.print(magnetometer[2]);
Serial.print(" ");

Serial.print(humidityy);
Serial.print(" ");
Serial.print(ttemperature);
Serial.print(" ");

Serial.print("\n");
//Serial.println();
}
