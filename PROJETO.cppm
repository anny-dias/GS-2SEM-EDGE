#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 1      // Pino de dados do DHT22 conectado ao pino D1 no ESP32
#define DHTTYPE DHT22 // Tipo de sensor DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);
void setup() {
    Serial.begin(115200);
    dht.begin();
}
void loop() {
    sensors_event_t event;
    dht.temperature().getEvent(&event);

    if (isnan(event.temperature)) {
        Serial.println("Erro ao ler temperatura!");
    } else {
        Serial.print("Temperatura: ");
        Serial.print(event.temperature);
        Serial.println(" °C");
    }

    dht.humidity().getEvent(&event);

    if (isnan(event.relative_humidity)) {
        Serial.println("Erro ao ler umidade!");
    } else {
        Serial.print("Umidade: ");
        Serial.print(event.relative_humidity);
        Serial.println(" %");
    }

    delay(2000); // Espere 2 segundos antes de ler novamente
}
