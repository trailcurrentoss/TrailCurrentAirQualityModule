#include "Dht22Sensor.h"
#include "Globals.h"
#include "TwaiTaskBased.h"

#include <Adafruit_Sensor.h>
#include <DHT_U.h>

#define DHTTYPE DHT22

Dht22Sensor::Dht22Sensor(uint8_t pin)
  : _dht(pin, DHTTYPE) {}

void Dht22Sensor::begin() {
  _dht.begin();
}

void Dht22Sensor::readAndSend() {
  float humidity = _dht.readHumidity();
  float temperatureC = _dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    debugln("Failed to read from DHT22 sensor");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Temp: ");
  Serial.print(temperatureC);
  Serial.println(" Celsius");

  sendTwaiMessage(temperatureC, humidity);

  delay(1000); // DHT22 minimum read interval
}

void Dht22Sensor::sendTwaiMessage(float temperatureC, float humidity) {
  uint16_t humidityScaled = static_cast<uint16_t>(humidity * 100.0f);
  uint8_t humidityWhole = (humidityScaled >> 8) & 0xFF;
  uint8_t humidityDecimal = humidityScaled & 0xFF;

  int temperatureCInt = static_cast<int>(temperatureC);
  int temperatureFInt = ((temperatureCInt * 9) + 3) / 5 + 32;

  debugln(temperatureFInt);

  twai_message_t msg = {};
  msg.identifier = 0x01F;
  msg.data_length_code = 4;
  msg.data[0] = temperatureCInt;
  msg.data[1] = temperatureFInt;
  msg.data[2] = humidityWhole;
  msg.data[3] = humidityDecimal;

  TwaiTaskBased::send(msg);
}
