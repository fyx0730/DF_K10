// #include <Wire.h>      // 导入 Wire 库，支持 I2C 通信
#include <SC7A20H.h>  // 导入 SC7A20H 库

// 创建 SC7A20H 对象，传入 Wire 对象
SC7A20H sensor;

void setup() {
    // 初始化串口通讯
    Serial.begin(115200);
    pinMode(0, OUTPUT);  // suppress the noise
    digitalWrite(0, LOW);

    // 初始化 I2C 通信
    Wire.begin(47, 48);

    Wire.beginTransmission(sensor._sc7a20hAddr);
    uint8_t ret = Wire.endTransmission();
    if (ret != 0) {
        printf(
            "SC7A20H Device not found, please check if the device is "
            "connected.");
    }
    // 初始化 SC7A20H 传感器
    sensor.initSC7A20H();

    // 输出初始化成功消息
    Serial.println("SC7A20H Sensor Initialized");
}

void loop() {
    // 获取加速度计的 X, Y, Z 轴数据
    sensor.updateAccelerometerData();
    int x = sensor.getAccelerometerX();
    int y = sensor.getAccelerometerY();
    int z = sensor.getAccelerometerZ();

    // 打印 X, Y, Z 轴数据
    Serial.print("X: ");
    Serial.print(x);
    Serial.print("\tY: ");
    Serial.print(y);
    Serial.print("\tZ: ");
    Serial.println(z);

    // 计算并打印三轴加速度的强度
    int strength = sensor.getStrength();
    Serial.print("Strength: ");
    Serial.println(strength);

    // 延迟 1 秒
    delay(100);
}
