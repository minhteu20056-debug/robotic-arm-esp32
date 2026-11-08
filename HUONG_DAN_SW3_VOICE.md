# Robot Arm: SW3 điều khiển voice Google/Vosk

## Thay đổi
- Nút **SW của Joystick 3** nối GPIO27 theo sơ đồ cũ. SW được nối xuống GND khi nhấn; `INPUT_PULLUP`; có chống dội 55 ms.
- Nhấn 1 lần: ESP32 gửi `VOICE ON` qua USB Serial; chương trình Python bắt đầu các lượt nghe liên tiếp.
- Nhấn lần nữa: ESP32 gửi `VOICE OFF`; Python dừng **sau lượt ghi âm đang thực hiện**, không bắt đầu lượt mới và hủy kế hoạch chờ xác nhận.
- Chọn Google nếu kết nối được; nếu Google lỗi hoặc ngoại tuyến, thử Vosk. Google không luôn nhận chính xác và không hiểu/cho phép tùy ý thực hiện mọi lời nói.
- Firmware phát dòng `ANG,a0,a1,a2,a3,a4` 5 lần/giây, dùng `nan` khi kênh chưa được điều khiển. Không có lệnh `STREAM ON`, không đưa servo về góc 0 lúc khởi động.
- Lệnh **mở/đóng kẹp** không yêu cầu SETALL cả 5 kênh. Nếu dữ liệu đầu vào thiếu, hình xem trước chỉ có tính tham khảo; Python không tự sinh vị trí robot thật. Lệnh **xoay tương đối** vẫn cần biết góc CH2 hiện tại (hoặc thiết kế lệnh xoay tuyệt đối).

## Cách dùng
1. Mở `RobotArm_QuickSetup_SW3_Voice.ino` trong Arduino IDE, chọn đúng **ESP32 Dev Module**, cổng COM đang kết nối và upload. **Sao lưu firmware đang nạp trước khi thay**. Chỉ nối dây đúng điện áp 3.3V/GND cho Joystick 3.
2. Dùng `arm_live.py`, `robot_voice_commands.json`, `arm5.urdf` cùng thư mục `meshes`. Giữ nguyên mô hình Vosk đã tải trong `live/vosk-model-small-vn-0.4/`.
3. Mở VS Code terminal tại thư mục gốc rồi chạy:
```
& "$HOME\miniforge3\envs\robot\python.exe" .\live\arm_live.py --port COM5 --no-info
```
4. Bấm SW3 một lần: Terminal báo `VOICE ON`. Nói “mở kẹp”; chương trình nhận dạng, lập kế hoạch và yêu cầu xác nhận. Bấm SW3 lần hai: báo `VOICE OFF`.
5. Kiểm tra giá trị `GRIP_OPEN_CH4` / `GRIP_CLOSE_CH4` là góc *thực tế đã kiểm chứng an toàn* trước khi xác nhận cho robot chuyển động. Nếu chưa kiểm chứng, chỉ thử nhận diện giọng nói, không xác nhận gửi lệnh.

## Giới hạn
- SW3 **không phải công tắc ngắt nguồn/dừng khẩn cấp**. Khi VOICE OFF, phần ghi âm đang chạy có thể hoàn tất nhưng không mở thêm lượt nghe mới; công tắc cũng không dừng ngay chuyển động đang diễn ra.
- GPIO27 là tín hiệu digital, GND phải chung. Không đưa nguồn servo 5V vào chân ESP32.
- Dữ liệu ANG khi có `nan` nghĩa là firmware không biết góc hiện tại, không phải robot ở 0 độ. AS5600 chưa được tích hợp trong firmware này.
- Chỉ lệnh có trong từ điển được gửi qua giọng nói, sau xác nhận; Google nhận **ngôn ngữ tự do ở mức chuyển thành văn bản**, không bảo đảm nhận đúng mọi tiếng nói và không phải bộ hiểu lệnh robot.
