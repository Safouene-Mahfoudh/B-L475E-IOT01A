#include <Servo.h>

#include <Wire.h>
#include <vl53l0x_class.h>


TwoWire WIRE1(PB11, PB10);  //SDA=PB11 & SCL=PB10
VL53L0X sensor_vl53l0x(&WIRE1, PC6, PC7); //XSHUT=PC6 & INT=PC7
Servo servo;

void setup() {
    int status;
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    
  //****************************** Initialize I2C bus*************************************************//
  WIRE1.begin();

  // Switch off VL53L0X component.
  sensor_vl53l0x.VL53L0X_Off();

  // Initialize VL53L0X top component.
  status = sensor_vl53l0x.InitSensor(0x10);


  
  servo.attach(8);
  servo.write(90);
}
void loop() 
{ 
  //*******************************************Read_Range***********************************************//
  uint32_t distance;
  int status;
  status = sensor_vl53l0x.GetDistance(&distance);

  if (status == VL53L0X_ERROR_NONE)
  {
    // Output data.
    char report[64];
    snprintf(report, sizeof(report), "| Distance [mm]: %ld |", distance);
    Serial.println(report);
     servo.write(distance);               
     // delay(15);
   // When the value of distance is between 0 and 180 the LED will blink 
    if ( (distance > 1) && (distance < 181)) 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
    }
  }
