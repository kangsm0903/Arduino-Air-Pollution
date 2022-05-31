#include <SoftwareSerial.h>        // 블루투스 시리얼 통신 라이브러리 추가
#include <dht11.h>                 // dht11.h 라이브러리를 불러옵니다

dht11 DHT11;                                           // DHT11이라는 객체를 만들고 dht11의 내용을 넣어줍니다.
#define DHT11PIN 3                                // DHT11PIN을 3로 설정합니다.

#define BT_RXD 8
#define BT_TXD 7

SoftwareSerial bluetooth(BT_RXD, BT_TXD);        // 블루투스 설정 BTSerial(Tx, Rx)

int Vo=A0; // A0
int V_LED=2; // 적외선

float Vo_value=0; // 전압값
float Voltage=0;  // 
float dustDensity=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600); 
  pinMode(V_LED,OUTPUT);
  pinMode(Vo,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(V_LED,LOW); // 적외선 on
  delayMicroseconds(280);
  Vo_value=analogRead(Vo); // 전압값을 읽음
  delayMicroseconds(40);
  digitalWrite(V_LED,HIGH); // 적외선 off
  delayMicroseconds(9680);

  Voltage=Vo_value*5.0/1023.0; // 원래의 전압값으로 변환해줌
  dustDensity=(Voltage-0.45)/0.005; // 전압값 - 먼지가 없을 때의 초기전압값 초기값을 0.45로 설정 -- 일단 완벽한 초기값은 아니기에 재설정이 필요해보임

  int chk = DHT11.read(DHT11PIN);                // DHT11PIN에서 받은 값을 chk에 저장합니다.
  float a = DHT11.humidity;
  float b = DHT11.temperature;
  String c = String(dustDensity) + "," + String(a) + "," + String(b);
  bluetooth.println(c);
  Serial.println(c);

  delay(1000);
  
}