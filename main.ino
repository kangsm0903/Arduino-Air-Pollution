#include <DFRobotHCHOSensor.h>
#include <SoftwareSerial.h>        
#include <dht11.h>                 // dht11.h 라이브러리를 불러옵니다

// 온습도
dht11 DHT11;                                          // DHT11이라는 객체를 만들고 dht11의 내용을 넣어줍니다.
#define DHT11PIN 3                                // DHT11PIN을 3로 설정합니다.

// 프롬알데히드
#define SensorSerialPin 10

// 블루투스
#define BT_RXD 8
#define BT_TXD 7

SoftwareSerial sensorSerial(SensorSerialPin, SensorSerialPin);
DFRobotHCHOSensor hchoSensor(&sensorSerial);

SoftwareSerial bluetooth(BT_RXD, BT_TXD);        // 블루투스 설정 BTSerial(Tx, Rx)

float porem;

int Vo=A0; // A0
int V_LED=2; // 적외선
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
  sensorSerial.begin(9600);
  sensorSerial.listen();
  Serial.begin(9600);
  bluetooth.begin(9600); 
  pinMode(V_LED,OUTPUT);
  pinMode(Vo,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(True){ // 프롬알데히드 값을 받아옴
    if(hchoSensor.available()>0)
    {
      porem=hchoSensor.uartReadPPM(); // 프롬알데히드
      Serial.println(battery);
      break;
    }  
  }
  
  digitalWrite(V_LED,LOW); // 적외선 on
  delayMicroseconds(280);
  Vo_value=analogRead(Vo); // 전압값을 읽음
  delayMicroseconds(40);
  digitalWrite(V_LED,HIGH); // 적외선 off
  delayMicroseconds(9680);

  Voltage=Vo_value*5.0/1023.0; // 원래의 전압값으로 변환해줌
  dustDensity=(Voltage-0.3)/0.005; // 전압값 - 먼지가 없을 때의 초기전압값을 초기값(0.3)으로 설정 -- 일단 완벽한 초기값은 아니기에 재설정이 필요해보임

  int chk = DHT11.read(DHT11PIN);                // DHT11PIN에서 받은 값을 chk에 저장
  float a = DHT11.humidity; // 습도
  float b = DHT11.temperature; // 온도

  float sum=0;
  float average=0;
  Serial.println(dustDensity);

  if(porem>0.08){
    String c = "포름알데히드 나쁨";
    bluetooth.println(c);
  }
  
  if (dustDensity<30 && type!=good){ // 미세먼지 좋음
    type=good;
    String alpha = "미세먼지 좋음";
    String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(porem);
    // 미세먼지 좋음, 습도, 온도, 미세먼지 농도, 프롬알데히드
    bluetooth.println(c);
    Serial.println(c);
  }
  else if(dustDensity<80 && type!=normal){
    type=normal;
    String alpha = "미세먼지 보통";
    String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(porem);
    bluetooth.println(c);
    Serial.println(c);
  }
  else if(dustDensity>=80 && dustDensity<=150 && type!=bad){
    type=bad;
    for(int i=0; i<5; i++){ // 5초동안 5번의 데이터의 평균값을 산출
      Voltage=Vo_value*5.0/1023.0; // 원래의 전압값으로 변환해줌
      dustDensity=(Voltage-0.01)/0.005; 
      sum=sum+dustDensity;
      delay(1000);
    }
    average=sum/5;
    if (average>=80 && average<=150){
      String alpha = "미세먼지 나쁨";
      String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(porem);
      bluetooth.println(c);
      Serial.println(c);
    }
  }
  else if(dustDensity>151 && type!=terrible){
    type=terrible;
    for(int i=0; i<5; i++){ // 5초동안 5번의 데이터의 평균값을 산출
      Voltage=Vo_value*5.0/1023.0; // 원래의 전압값으로 변환해줌
      dustDensity=(Voltage-0.01)/0.005; 
      sum=sum+dustDensity;
      delay(1000);
    }
    average=sum/5;
    if (average>151){
      String alpha = "미세먼지 매우 나쁨";
      String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(porem);
      bluetooth.println(c);
      Serial.println(c);
    }
  }
  String c = alpha + "," + String(a) + "," + String(b) + "," + String(dustDensity) + "," + String(porem);
  bluetooth.println(c);
  delay(1000);
  
}