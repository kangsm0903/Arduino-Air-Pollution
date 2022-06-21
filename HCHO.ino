#include <DFRobotHCHOSensor.h>
#include <SoftwareSerial.h>

#define SensorSerialPin 10

SoftwareSerial sensorSerial(SensorSerialPin, SensorSerialPin);

DFRobotHCHOSensor hchoSensor(&sensorSerial);

void setup()
{
  sensorSerial.begin(9600);
  sensorSerial.listen();
  Serial.begin(9600);
}

void loop()
{
  
  if(hchoSensor.available()>0)
  {
    Serial.print(hchoSensor.uartReadPPM());
    Serial.println("ppm");
  }
}