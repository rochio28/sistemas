#include <sd_defines.h>
#include <SD.h>
#include <sd_diskio.h>
#include <Adafruit_BMP280.h>

#define PIN_LED 32

Adafruit_BMP280 bmp;
File readings;
File read_me;
char payload[50]; // Datos a escribir en SD y serial

void setup() {
  Serial.begin(115200); //Inicilizar serial UART-USB
  bmp.begin(0x76); // Inicializar comunicación I2C con el sensor barométrico.
  SD.begin(); // Inicializar SD

  pinMode(PIN_LED, OUTPUT);

  //READ_ME
  read_me = SD.open("/README.txt", FILE_WRITE);
  read_me.print("Archivo de lecturas de sensor BMP280. \n"
                "Temperatura [ºC], Presion [Pa]");
  read_me.close();
 
}

void loop() {
  // Escribo las lecturas en payload
  sprintf(payload, "%.2f, %.2f", bmp.readTemperature(), bmp.readPressure());
  Serial.println(payload);

  //Abro archivo y escribo.
  digitalWrite(PIN_LED,HIGH);
  readings = SD.open("/readings.csv", FILE_APPEND);
  readings.println(payload);
  readings.close();
  digitalWrite(PIN_LED,LOW);
 
  delay(500);
}
