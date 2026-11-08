// ESP32 điều khiển 5 servo và gửi góc đang ra lệnh lên máy tính để mô hình 3D xoay theo.
// Thư viện cần cài (Arduino IDE -> Library Manager): "ESP32Servo" của Kevin Harrington.
// Mỗi 20 ms in 1 dòng: "g1,g2,g3,g4,g5\n"  (độ, lệch so với vị trí giữa 90 độ, nên 0 = giữa).
// Thứ tự: đế, vai, khuỷu, cổ tay, kẹp.
//
// LƯU Ý NGUỒN: servo MG995 ăn dòng lớn (có thể trên 1 A mỗi con khi chịu tải).
// Cấp 5-6 V riêng cho servo, KHÔNG lấy từ chân 5V/3V3 của ESP32, và nối GND chung với ESP32.
#include <ESP32Servo.h>

#define DEMO 1   // 1 = tự chạy chuyển động thử, 0 = bạn tự gọi setTarget() ở nơi khác

const int   PIN[5]     = {13, 14, 25, 26, 27};   // chân tín hiệu servo, đổi theo cách bạn nối
const float MIN_DEG[5] = {0, 0, 0, 0, 0};        // giới hạn an toàn cơ khí cho từng servo
const float MAX_DEG[5] = {180, 180, 180, 180, 180};
const float MAX_SPEED  = 60.0;                   // độ/giây, giới hạn tốc độ để chuyển động mượt

Servo sv[5];
float cur[5]    = {90, 90, 90, 90, 90};          // góc đang ra lệnh thực tế
float target[5] = {90, 90, 90, 90, 90};          // góc đích

void setTarget(int i, float deg) {               // dùng hàm này để ra lệnh góc (0..180)
  target[i] = constrain(deg, MIN_DEG[i], MAX_DEG[i]);
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) {
    sv[i].setPeriodHertz(50);
    sv[i].attach(PIN[i], 500, 2400);
    sv[i].writeMicroseconds(map((long)cur[i], 0, 180, 500, 2400));
  }
}

void loop() {
  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last < 20) return;                   // vòng lặp 50 Hz
  float dt = (now - last) / 1000.0f;
  last = now;

#if DEMO
  float t = now / 1000.0f;
  setTarget(0, 90 + 40 * sin(t * 0.5));
  setTarget(1, 90 + 25 * sin(t * 0.7));
  setTarget(2, 90 + 25 * sin(t * 0.9));
  setTarget(3, 90 + 40 * sin(t * 1.1));
  setTarget(4, 90 + 20 * sin(t * 1.5));
#endif

  for (int i = 0; i < 5; i++) {
    float step = MAX_SPEED * dt;
    cur[i] += constrain(target[i] - cur[i], -step, step);
    sv[i].writeMicroseconds((int)(500 + cur[i] * (1900.0f / 180.0f)));
  }

  for (int i = 0; i < 5; i++) {
    Serial.print(cur[i] - 90.0f, 1);
    Serial.print(i < 4 ? ',' : '\n');
  }
}
