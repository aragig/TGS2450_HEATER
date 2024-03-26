#include <Arduino.h>

#define LED_PIN_1 9   // 1秒ごとに点滅するLEDのピン
#define LED_PIN_2 10  // 2秒ごとに点滅するLEDのピン

volatile unsigned long timer1_counter = 0;

void setup() {
    Serial.begin(115200);

    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);

    noInterrupts(); // 割り込みを無効化

    // タイマー1の設定
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    OCR1A = 31249; // 0.5秒ごとに割り込み（16MHz / 256 prescale / 2 = 31250）
    TCCR1B |= (1 << WGM12); // CTCモード
    TCCR1B |= (1 << CS12);  // 256のプリスケーラを設定
    TIMSK1 |= (1 << OCIE1A); // タイマー比較割り込みAを有効化

    interrupts(); // 割り込みを有効化
}

ISR(TIMER1_COMPA_vect) {
        // タスク処理はできるだけ短くする
        timer1_counter++; // タイマーカウンタをインクリメント

        // 1秒ごとにLED 1の状態を切り替える
        if (timer1_counter % 2 == 0) {
            Serial.println("\nBlink LED 1");
            digitalWrite(LED_PIN_1, !digitalRead(LED_PIN_1));
        }

        // 2秒ごとにLED 2の状態を切り替える
        if (timer1_counter % 4 == 0) {
            Serial.println("\nBlink LED 2");
            digitalWrite(LED_PIN_2, !digitalRead(LED_PIN_2));
        }
}

void loop() {
    // メインループでは何もしない
    while (true) {
        Serial.print(".");
        delay(100);
    }
}
