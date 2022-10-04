
//int pinLDR = 34;
//const int pinLDR = 34;
#define PIN_LDR 34
#define PIN_LM35 35

void setup() {
  Serial.begin(9600);

}

void loop() {
  //int m= analogRead (PIN_LDR);
  //Serial.println(m);
  
 Serial.println(analogRead(PIN_LDR));
 delay(100);
}
