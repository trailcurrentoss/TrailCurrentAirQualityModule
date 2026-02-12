#pragma once
#include <Arduino.h>
#include <driver/twai.h>
#include <DHT.h>


class Dht22Sensor {
public:
  explicit Dht22Sensor(uint8_t pin);

  void begin();
  void readAndSend();

private:
  void sendTwaiMessage(float temperatureC, float humidity);

  DHT _dht;
};
