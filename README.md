# Cánh tay robot 5 servo – ESP32 + PCA9685 + PyBullet

Đồ án: điều khiển cánh tay robot 5 bậc tự do (5×MG996R) bằng ESP32, joystick, giao diện Web và giọng nói tiếng Việt; mô phỏng thời gian thực bằng Python/PyBullet.

**Tác giả:** Hoàng Nhật Minh (minhteu20056-debug)

## Cấu trúc
- `live/RobotArm_QuickSetup_SW3_Voice/` – firmware ESP32 (Arduino)
- `live/arm_live.py` – mô phỏng PyBullet, giao tiếp Serial, điều khiển giọng nói
- `arm5.urdf`, `meshes/` – mô hình robot
- `HUONG_DAN_*.md` – hướng dẫn sử dụng

Bản quyền © Hoàng Nhật Minh. Kho lưu trữ riêng tư, chưa cho phép sao chép hay phân phối lại.
