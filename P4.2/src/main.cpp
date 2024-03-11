#include <Arduino.h>

const int ledPin = 13;  // Pin del LED
bool encender = true;   // Variable compartida para controlar la tarea

void encenderLED(void *parameter);
void apagarLED(void *parameter);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  // Crear las tareas
  xTaskCreate(encenderLED, "Encender LED", 1000, NULL, 1, NULL);
  xTaskCreate(apagarLED, "Apagar LED", 1000, NULL, 1, NULL);
}

void loop() {
  // El loop no se utiliza en el contexto de FreeRTOS
}

void encenderLED(void *parameter) {
  for (;;) {
    if (encender) {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED encendido");
      encender = false;
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // Esperar 1 segundo
  }
}

void apagarLED(void *parameter) {
  for (;;) {
    if (!encender) {
      digitalWrite(ledPin, LOW);
      Serial.println("LED apagado");
      encender = true;
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // Esperar 1 segundo
  }
}
