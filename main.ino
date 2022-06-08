#include <DFRobotHCHOSensor.h>
#include <SoftwareSerial.h>        
#include <dht11.h>                 // dht11.h 라이브러리를 불러옵니다
#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

// 온습도
dht11 DHT11;                                           // DHT11이라는 객체를 만들고 dht11의 내용을 넣어줍니다.
#define DHT11PIN 3                                // DHT11PIN을 3로 설정합니다.

// 프롬알데히드
#define SensorSerialPin 10

// 블루투스
#define BT_RXD 8
#define BT_TXD 7

SoftwareSerial sensorSerial(SensorSerialPin, SensorSerialPin);
DFRobotHCHOSensor hchoSensor(&sensorSerial);

SoftwareSerial bluetooth(BT_RXD, BT_TXD);        // 블루투스 설정 BTSerial(Tx, Rx)

// CO, NH3, NO2 초기 설정
int CO, NH3, CO2, TVOC;
float NO2;
const int S_analog=1023.0;

float po;

// 미세먼지 초기 설정
int Vo=A0; // A0
int V_LED=6; // 적외선
int good=1;
int normal=2;
int bad=3;
int terrible=4;
int type=-1;

float Vo_value=0; // 전압값
float Voltage=0;  // 
float dustDensity=0;

String alpha;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600); 
  sensorSerial.begin(9600);
  sensorSerial.listen();
  ccs.begin();
  
  sensorSerial.listen();
  
  pinMode(V_LED,OUTPUT);
  pinMode(Vo,INPUT);
 
  // Wait for the sensor to be ready
  while(!ccs.available());
    while(true){
      if (hchoSensor.available()>0){
         po=hchoSensor.uartReadPPM();
        Serial.print("포름:");
        Serial.println(po);
         break;
       }
    };
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(!ccs.readData()){
    CO2=ccs.geteCO2();
    TVOC=ccs.getTVOC();
  }

  digitalWrite(V_LED,LOW); // 적외선 on
  delayMicroseconds(280);
  Vo_value=analogRead(Vo); // 전압값을 읽음
  delayMicroseconds(40);
  digitalWrite(V_LED,HIGH); // 적외선 off
  delayMicroseconds(9680);

  Voltage=Vo_value*5.0/1023.0; // 원래의 전압값으로 변환해줌
  //dustDensity=(Voltage-0.5)/0.005; // 전압값 - 먼지가 없을 때의 초기전압값을 초기값(0.3)으로 설정 -- 일단 완벽한 초기값은 아니기에 재설정이 필요해보임
  dustDensity=30;
  int chk = DHT11.read(DHT11PIN);                // DHT11PIN에서 받은 값을 chk에 저장
  float a = DHT11.humidity; // 습도
  float b = DHT11.temperature; // 온도

  CO=map(analogRead(A3), 0, S_analog, 1, 1000);
  NH3=map(analogRead(A1), 0, S_analog, 1, 500);
  NO2=(map(analogRead(A2), 0, S_analog, 5, 1000))/100.0;
  Serial.print("NH3: ");
  Serial.println(NH3);
  Serial.print("NO2: ");
  Serial.println(NO2);
  Serial.print("CO: ");
  Serial.println(CO);        
  Serial.println();

  Serial.print("CO2: ");
  Serial.println(CO2);
  Serial.print("TVOC: ");
  Serial.println(TVOC);
  
  float sum=0;
  float average=0;
  Serial.println(dustDensity);
  
  if (dustDensity<30 && type!=good){ // 미세먼지 좋음
    type=good;
    String alpha = "미세먼지 좋음";
    String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(NH3) + "," + String(NO2) + "," + String(CO)+ "," + String(CO2)+ "," + String(TVOC);
    // 미세먼지 좋음, 습도, 온도, 미세먼지 농도, NH3, NO2, CO, CO2, TVOC, 포름알데히드
    bluetooth.println(c);
    Serial.println(c);
  }
  else if(dustDensity<80 && type!=normal){
    type=normal;
    String alpha = "미세먼지 보통";
    String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(NH3) + "," + String(NO2) + "," + String(CO)+ "," + String(CO2)+ "," + String(TVOC);
    bluetooth.println(c);
    Serial.println(c);
  }
  else if(dustDensity>=80 && dustDensity<=150 && type!=bad){
    type=bad;
    for(int i=0; i<50; i++){ // 5초동안 5번의 데이터의 평균값을 산출
      digitalWrite(V_LED,LOW); // 적외선 on
      delayMicroseconds(280);
      Vo_value=analogRead(Vo); // 전압값을 읽음
      delayMicroseconds(40);
      digitalWrite(V_LED,HIGH); // 적외선 off
      delayMicroseconds(9680);
      Voltage=Vo_value*5.0/1023.0; // 원래의 전압값으로 변환해줌
      dustDensity=(Voltage-0.4)/0.005; 
      sum=sum+dustDensity;
      delay(1);
    }
    average=sum/50;
    Serial.print("평균:");
    Serial.println(average);
    if (average>=80 && average<=150){
      String alpha = "미세먼지 나쁨";
      String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(NH3) + "," + String(NO2) + "," + String(CO)+ "," + String(CO2)+ "," + String(TVOC);
      bluetooth.println(c);
      Serial.println(c);
    }
  }
  else if(dustDensity>151 && type!=terrible){
    type=terrible;
    for(int i=0; i<50; i++){ // 5초동안 50번의 데이터의 평균값을 산출
      digitalWrite(V_LED,LOW); // 적외선 on
      delayMicroseconds(280);
      Vo_value=analogRead(Vo); // 전압값을 읽음
      delayMicroseconds(40);
      digitalWrite(V_LED,HIGH); // 적외선 off
      delayMicroseconds(9680);
      Voltage=Vo_value*5.0/1023.0; // 원래의 전압값으로 변환해줌
      dustDensity=(Voltage-0.4)/0.005; 
      sum=sum+dustDensity;
      delay(1);
    }
    average=sum/50;
    if (average>151){
      String alpha = "미세먼지 매우 나쁨";
      String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(NH3) + "," + String(NO2) + "," + String(CO)+ "," + String(CO2)+ "," + String(TVOC);
      bluetooth.println(c);
      Serial.println(c);
    } 
  }

  if(CO2<1000){
    type2=-1;
  }

  if (CO2>1000 && type2!=bad){
    Serial.println("1000 넘음!!!!!!!!!!!");
    type2=bad;
    long int sum1=0;
    for(int i=0; i<50;i++){ // 데이터 50번 입력 받음
      if(!ccs.readData()){
        CO2=ccs.geteCO2();
        TVOC=ccs.getTVOC();
        Serial.print("넘었을 때CO2:");
        Serial.println(CO2);
        sum1+=CO2;
      }
      delay(10);
    }

    float average1=sum1/50;
    if (average1>1000){
      Serial.println("평균 넘음!!!!!!!!!!!!!!!!!");
      String alpha = "이산화탄소 나쁨";
      String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(NH3) + "," + String(NO2) + "," + String(CO)+ "," + String(CO2)+ "," + String(TVOC);
      bluetooth.println(c);
    }

    if(hchoSensor.available()>0)
    {
      po=(hchoSensor.uartReadPPM());
      Serial.print("포름알데히드:");
      Serial.println(po);
    }

  String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(NH3) + "," + String(NO2) + "," + String(CO)+ "," + String(CO2)+ "," + String(TVOC);
  bluetooth.println(c);
  delay(1000);
  
}