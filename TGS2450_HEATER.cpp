//
// Created by Toshihiko Arai on 2024/03/26.
//

#include "TGS2450_HEATER.h"

volatile unsigned long timer1_counter = 0;
volatile uint16_t val = 0;

// クラスの静的メンバ変数の宣言
volatile static uint8_t OUT_PIN;
volatile static uint8_t SEN_PIN;
volatile static uint8_t HTR_PIN;


TGS2450_HEATER::TGS2450_HEATER(uint8_t out_pin, uint8_t sen_pin, uint8_t htr_pin) {
    OUT_PIN = out_pin;
    SEN_PIN = sen_pin;
    HTR_PIN = htr_pin;

    pinMode(OUT_PIN, OUTPUT);
    pinMode(SEN_PIN, INPUT);
    pinMode(HTR_PIN, OUTPUT);

}

void TGS2450_HEATER::init() {
    noInterrupts(); // 割り込みを無効化

    // タイマー1の設定
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    OCR1A = 63; // 1msごとに割り込み（16MHz / 256 prescale / 2 = 31250）
    TCCR1B |= (1 << WGM12); // CTCモード
    TCCR1B |= (1 << CS12);  // 256のプリスケーラを設定
    TIMSK1 |= (1 << OCIE1A); // タイマー比較割り込みAを有効化

    interrupts(); // 割り込みを有効化
};

ISR(TIMER1_COMPA_vect) {
        timer1_counter++; // タイマーカウンタをインクリメント

        if (timer1_counter == 237) {
            digitalWrite(SEN_PIN, HIGH); // Sensor Pullup On
        } else if(timer1_counter == 240) {
//            Serial.println("Get Sensor Voltage");
            val = analogRead(OUT_PIN);  // Get Sensor Voltage
        } else if(timer1_counter == 242) {
            digitalWrite(SEN_PIN,LOW); // Sensor Pullup Off
            digitalWrite(HTR_PIN,LOW); // Heater On
        } else if(timer1_counter == 250) {
            digitalWrite(HTR_PIN,HIGH); // Heater Off
            timer1_counter = 0;
        }
};

uint16_t TGS2450_HEATER::readOdor(){
    return val;
};
