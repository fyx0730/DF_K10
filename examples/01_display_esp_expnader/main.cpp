/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with M5Core sample source code
*                          配套  M5Core 示例源代码
* Visit for more information: https://docs.m5stack.com/en/unit/dlight
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/unit/dlight
*
* Describe: Ambient light detection BH1750FVI
* Date: 2023/3/24
*******************************************************************************
  Please connect the sensor to port A (22, 21), the Lux value will be displayed
  on the display after successful initialization
  请将传感器连接至端口A(22、21),成功初始化后显示屏上将显示Lux数值
  hp_BH1750.h Please download the file from the library management office
  hp_BH1750.h 文件请从库管理处下载
*/
#include "Adafruit_LTR329_LTR303.h"
#include "initBoard.h"
#include "Arduino_DriveBus_Library.h"
#include <ESP_IOExpander_Library.h>

#define _EXAMPLE_CHIP_CLASS(name, ...) ESP_IOExpander_##name(__VA_ARGS__)
#define EXAMPLE_CHIP_CLASS(name, ...)  _EXAMPLE_CHIP_CLASS(name, ##__VA_ARGS__)
Adafruit_LTR303 ltr = Adafruit_LTR303();

ESP_IOExpander *expander = NULL;
#include "Lcd_handler.hpp"
K10_Lcd display;
LGFX_Sprite canvas(&display);
char info[20];
void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);  // wait for serial port to open
    }
    pinMode(45,OUTPUT);
    digitalWrite(45,HIGH);
    Serial.println("Adafruit LTR-303 simple test");
    Wire.begin(47, 48);
    // init_board();
    expander =
        new EXAMPLE_CHIP_CLASS(TCA95xx_16bit, (i2c_port_t)0,
                               ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000, 48, 47);
    // expander->init();
    expander->begin();
    expander->reset();
    expander->pinMode(0, OUTPUT);
    expander->pinMode(1, OUTPUT);
    delay(20);
    expander->digitalWrite(0,HIGH) ;
    expander->digitalWrite(1, HIGH);
    // init_board();
    if (!ltr.begin()) {
        Serial.println("Couldn't find LTR sensor!");
        while (1) delay(10);
    }
    Serial.println("Found LTR sensor!");
    // Set gain of 1 (see advanced demo for all options!
    ltr.setGain(LTR3XX_GAIN_4);
    // Set integration time of 50ms (see advanced demo for all options!
    ltr.setIntegrationTime(LTR3XX_INTEGTIME_50);
    // Set measurement rate of 50ms (see advanced demo for all options!
    ltr.setMeasurementRate(LTR3XX_MEASRATE_50);
    display.init();
    display.initDMA();
    display.setRotation(1);
    // canvas.setTextDatum(MC_DATUM);
    // display.setColorDepth(0);
    // display.setFont(&fonts::Orbitron_Light_24);
    display.setTextSize(0);
    display.setTextColor(TFT_ORANGE);
    display.setTextDatum(MC_DATUM);
    display.fillScreen(TFT_RED);
    // canvas.setColorDepth(0);
    // canvas.setFont(&fonts::Orbitron_Light_24);
    canvas.setTextSize(2);
    canvas.setTextWrap(false);
    canvas.createSprite(300, 200);
    canvas.setTextDatum(MC_DATUM);
    canvas.setFont(&fonts::efontCN_16_b);
    canvas.setTextColor(TFT_MAGENTA);  
    // canvas.setPaletteColor(1, TFT_ORANGE);
    Serial.println("Sensor begin.....");
}

void loop() {
    bool valid;
    static uint16_t visible_plus_ir, infrared;
    static uint16_t ls_vs = 0, ls_in = 0;
    if (ltr.newDataAvailable()) {
        valid = ltr.readBothChannels(visible_plus_ir, infrared);
        if (valid) {
        }
    }

#if 1
    canvas.fillSprite(TFT_BLACK);
    // canvas.drawString("Hello World", 100, 50);
    canvas.setCursor(30,50);
    canvas.print("info");

    sprintf(info, "光照强度: %d", visible_plus_ir);
    canvas.setCursor(0, 120);
    canvas.print(info);
    canvas.pushSprite(10, 15);
#endif


    // delay(100);
}
