#include <Arduino.h>
#include <TGS2450_HEATER.h>
#include <SPI.h>
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789


TGS2450_HEATER sensor(A3, A1, A0);
Adafruit_ST7789 tft = Adafruit_ST7789(10, 8, 9);

uint16_t last_odor = -1;

void setup() {
    Serial.begin(115200);
    sensor.init();
    tft.init(240, 240, SPI_MODE2);
    tft.fillScreen(ST77XX_BLACK);
}

void loop() {
    uint16_t odor = sensor.readOdor();

    if(last_odor != odor) {
        Serial.print(last_odor);
        Serial.print(" ");
        Serial.println(odor);

        uint8_t odor_per = map(odor, 0, 1023, 0, 100);
//    tft.fillScreen(ST77XX_BLACK);
        // 数値表示
        tft.fillRect(0, 0, 240, 70,ST77XX_BLACK);
        tft.setCursor(10, 10);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextWrap(true);
        tft.setTextSize(4);
        char buf[11];
        sprintf(buf, "%d (%d%%)", odor, odor_per);
        tft.print(buf);

        // メーター
        tft.drawRect(10, 130, 220, 100,ST77XX_WHITE);
        uint8_t green_bar_width = 218 * odor_per / 100;
        uint8_t red_bar_width = 218 - green_bar_width;
        tft.fillRect(11, 131, green_bar_width, 98,ST77XX_GREEN);
        tft.fillRect(11 + green_bar_width, 131, red_bar_width, 98,ST77XX_ORANGE);

        last_odor = odor;
    }

    delay(500);

}
