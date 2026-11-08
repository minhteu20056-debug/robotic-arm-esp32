// ESP32 + TCA9548A + 5 x AS5600  ->  Serial: "a1,a2,a3,a4,a5\n" (độ, 0..360)
// Kênh TCA9548A: 0=đế, 1=vai, 2=khuỷu, 3=cổ tay, 4=kẹp
// Dây: ESP32 SDA=GPIO21, SCL=GPIO22 -> TCA9548A SDA/SCL. A0,A1,A2 của TCA nối GND (địa chỉ 0x70).
//      Mỗi AS5600 nối vào cặp SDx/SCx của đúng kênh, cấp 3.3V, chân DIR nối GND (tất cả cùng một kiểu).
#include <Wire.h>

#define TCA_ADDR    0x70
#define AS5600_ADDR 0x36
#define N_SENSORS   5

const uint8_t CHANNEL[N_SENSORS] = {0, 1, 2, 3, 4};

void tcaSelect(uint8_t ch) {
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << ch);
  Wire.endTransmission();
}

// Đọc góc thô 12 bit (0..4095). Trả về false nếu lỗi I2C.
bool readRaw(uint8_t ch, uint16_t &raw) {
  tcaSelect(ch);
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(0x0C);                              // thanh ghi RAW ANGLE
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom((uint8_t)AS5600_ADDR, (uint8_t)2) != 2) return false;
  uint16_t hi = Wire.read();
  uint16_t lo = Wire.read();
  raw = ((hi << 8) | lo) & 0x0FFF;
  return true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  Wire.setClock(400000);
}

void loop() {
  for (int i = 0; i < N_SENSORS; i++) {
    uint16_t raw;
    if (readRaw(CHANNEL[i], raw)) Serial.print(raw * 360.0f / 4096.0f, 2);
    else                          Serial.print("nan");   // cảm biến lỗi/chưa nối
    Serial.print(i < N_SENSORS - 1 ? ',' : '\n');
  }
  delay(10);   // ~100 Hz
}
