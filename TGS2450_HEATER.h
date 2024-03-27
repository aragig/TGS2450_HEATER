//
// Created by Toshihiko Arai on 2024/03/26.
//

#ifndef DEV_ESP32_LIBS_TGS2450_HEATER_H
#define DEV_ESP32_LIBS_TGS

#include <Arduino.h>

class TGS2450_HEATER {
public:
    TGS2450_HEATER(uint8_t out_pin, uint8_t sen_pin, uint8_t htr_pin);
    void init();
    uint16_t readOdor();


};


#endif //DEV_ESP32_LIBS_TGS2450_HEATER_H
