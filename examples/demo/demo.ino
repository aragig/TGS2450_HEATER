#include <Arduino.h>
#include "TGS2450_HEATER.h"


TGS2450_HEATER sensor(2, 4, 5);

void setup() {
    Serial.begin(115200);
    sensor.init();
}


void loop() {
    uint16_t odor = sensor.readOdor();
    Serial.println(odor);
    delay(1000);
}
