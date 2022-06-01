const int S_analog = 1023.0;

int CO, NH3;
float NO2;

void setup(){

  Serial.begin(9600);
  Serial.println("MiCS 6814 simple test");
}

void loop(){
  CO = map(analogRead(A3), 0, S_analog, 1, 1000);
  NH3 = map(analogRead(A1), 0, S_analog, 1, 500);
  NO2 = (map(analogRead(A2), 0, S_analog, 1, 1000))/100.0;

  Serial.print("NH3: ");
  Serial.println(NH3);
  Serial.print("NO2: ");
  Serial.println(NO2);
  Serial.print("CO: ");
  Serial.println(CO);        
  Serial.println();
  
  delay(5000);
}

// ------------------------------------------------------------------------

// MiCS 6814 simple test
// NH3: 236, NO2: 294, CO: 290

int NH3=0;
int NO2=1;
int CO=2;

void setup(){
  pinMode(NH3,OUTPUT);
  pinMode(NO2,OUTPUT);
  pinMode(CO,OUTPUT);

  Serial.begin(9600);
  Serial.println("MiCS 6814 simple test");
}

void loop(){
  int sense_val_1 = analogRead(NH3);
  int sense_val_2 = analogRead(NO2);
  int sense_val_3 = analogRead(CO);

  Serial.print("NH3: ");
  Serial.println(sense_val_1);
  Serial.print("NO2: ");
  Serial.println(sense_val_2);
  Serial.print("CO: ");
  Serial.println(sense_val_3);        

  delay(1000);
}