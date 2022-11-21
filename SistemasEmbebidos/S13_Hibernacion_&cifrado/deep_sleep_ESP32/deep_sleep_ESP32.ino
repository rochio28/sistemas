RTC_DATA_ATTR int bootCount = 0; //Esta variable se guarda en la memoria de RTC. Esta memoria sí se mantiene tras un deep sleep.

#define uS_TO_S_FACTOR 1000000 //factor de conversión us a s
#define TIME_TO_SLEEP 5 //Tiempor que el ESP va a dormir en s  
#define LED_PIN 32 //led
#define BUTTON_PIN 33 // PUSH BUTTON

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(LED_PIN, OUTPUT);

  bootCount++;
  Serial.println("Boot number o Número de veces iniciado: " + String(bootCount));

  print_wakeup_reason();
  
  // Configuración Deep Sleep
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, HIGH);
  //esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, HIGH);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP*uS_TO_S_FACTOR);
  delay(5);
  
  Serial.println("Configurando ESP32 para dormir por " + String(TIME_TO_SLEEP) + " segundos.");

  if (bootCount%2 == 0){
    Serial.println("ESP32 se va a dormir ahora.");
    esp_deep_sleep_start();
  }
    Serial.println("Esta línea solo se imprime en impares");
}

void loop() {
  digitalWrite(LED_PIN, LOW);
  esp_light_sleep_start();

  digitalWrite(LED_PIN,HIGH);
  delay(500);

  print_wakeup_reason();
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0:
    Serial.println("Inicio causado por señal en el RTC_IO (Periféricos del RTC)");
    break;

    case ESP_SLEEP_WAKEUP_EXT1:
    Serial.println("Inicio causado por señal en el RTC_CNTL");
    break;

       case ESP_SLEEP_WAKEUP_TIMER:
    Serial.println("Inicio causado por señal en un timer");
    break;

       case ESP_SLEEP_WAKEUP_TOUCHPAD:
    Serial.println("Inicio causado por señal en un pin touch");
    break;

       case ESP_SLEEP_WAKEUP_ULP:
    Serial.println("Inicio causado por señal lanzada por el ULP Croprocessor");
    break;

    default:
      Serial.printf("El inicio no fue causado por ninguna razón conocida");

    
  }
}
