// 샘플링이 너무 오래걸려서 추가하지는 않았음

#include "MQ131.h"

void setup() {
  Serial.begin(9600);
  MQ131.begin(2,A0, LOW_CONCENTRATION, 1000000);  

  Serial.println("Calibration in progress...");
  
  MQ131.calibrate();
  
  Serial.println("Calibration done!");
  Serial.print("R0 = ");
  Serial.print(MQ131.getR0());
  Serial.println(" Ohms");
  Serial.print("Time to heat = ");
  Serial.print(MQ131.getTimeToRead());
  Serial.println(" s");
}

void loop() {
  Serial.println("Sampling...");
  MQ131.sample();
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(PPM));
  Serial.println(" ppm");

}