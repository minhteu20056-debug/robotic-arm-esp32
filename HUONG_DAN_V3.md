# Robot Arm V3 - ANG theo thay đổi + lệnh góc bằng giọng nói

## Hai chương trình
- `live/RobotArm_QuickSetup_SW3_Voice.ino`: nạp Arduino IDE vào ESP32.
- `live/arm_live.py`: chạy trên máy tính với Conda `robot`, giao tiếp USB Serial.

## Dữ liệu góc
- Khi khởi động: ESP32 gửi 1 snapshot `ANG,nan,nan,nan,nan,nan` nếu chưa khởi tạo góc.
- Khi 1 hoặc nhiều kênh nhận góc mới: đánh dấu thay đổi; cuối lượt xử lý gửi 1 `ANG,...` gồm 5 kênh.
- Khi không đổi: không gửi.
- Trong chuyển động nội suy chặn vòng `loop`, snapshot được gửi khi kết thúc chuyển động; joystick có thể gửi từng lần cập nhật. Đây là góc LỆNH, không phải góc thực đo.
- `nan` nghĩa là chưa biết góc; không nên đoán thay bằng 0.

## Lệnh giọng nói có góc tuyệt đối
- CH0: `nâng CH0 đến 120 độ`, `hạ CH0 đến 110 độ`.
- CH1: `duỗi CH1 đến 130 độ`, `gập CH1 đến 100 độ`.
- CH2: `quay đế đến 90 độ`, `xoay CH2 đến 90 độ`.
- CH3: `xoay cổ tay đến 80 độ`, `xoay CH3 đến 80 độ`.
- CH4: `mở kẹp đến 70 độ`, `đóng kẹp đến 110 độ`.
- Các số chỉ là ví dụ cú pháp, KHÔNG phải góc an toàn được xác nhận.
- `mở kẹp`, `đóng kẹp` không có số vẫn dùng giá trị cấu hình GRIP_OPEN_CH4, GRIP_CLOSE_CH4.
- Câu giọng nói phải qua parser, kiểm tra giới hạn 0..180 độ và bước xác nhận, rồi mới gửi `SET ch goc` đến ESP32.
- Nên hiệu chuẩn cơ cấu và giới hạn thực tế trước khi thử CH0/CH1 (cơ cấu 4 thanh).
- Vosk offline chỉ được gợi ý các cụm góc thông dụng; Google có thể nhận nhiều cách đọc hơn, không đảm bảo nhận đúng hết.

## Chạy chương trình
1. Tải mô hình Vosk tiếng Việt vào `live/vosk-model-small-vn-0.4` nếu dùng offline (không có trong ZIP do dung lượng).
2. Đóng Arduino Serial Monitor sau khi nạp firmware.
3. Trong PowerShell, tại thư mục dự án, chạy:

```
& "$HOME\miniforge3\envs\robot\python.exe" .\live\arm_live.py --port COM3 --no-info
```

Thay COM3 bằng cổng ESP32 thực tế. SW3 GPIO27 bật/tắt Voice. Nhấn `V` để thử thủ công.

**Quan trọng:** `SET 2 90` là lệnh góc TUYỆT ĐỐI; nó có thể làm robot chuyển động ngay sau khi xác nhận. Bảo đảm khu vực chuyển động thông thoáng và có phương án ngắt nguồn servo độc lập.

Lệnh `GETANGLES` yêu cầu một snapshot tức thì; nếu chưa xác lập góc thì vẫn là `nan`. Trong nội suy servo, cập nhật tối đa khoảng 10 lần/giây khi đang di chuyển, gửi góc cuối khi hoàn tất. Không gửi khi không đổi.
