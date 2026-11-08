# Robot Arm V4 – lệnh giọng nói dễ nhớ + xác nhận

Không thay firmware Arduino V3. File `live/arm_live.py` chạy trên VS Code; giữ file `live/RobotArm_QuickSetup_SW3_Voice.ino` nạp trong ESP32 (nếu đã nạp V3).

## Thiết lập
- Giữ `live/offsets.json` đã hiệu chuẩn từ dự án cũ, và `live/poses.json` nếu có. KHÔNG nhấn Z để hiệu chuẩn lại không cần thiết.
- Giữ thư mục `live/vosk-model-small-vn-0.4` đã tải (không đóng gói trong ZIP).
- Chạy `& "$HOME\miniforge3\envs\robot\python.exe" .\live\arm_live.py --port COM3 --no-info` (thay COM3 bằng cổng đúng).
- SW3 (GPIO27) bật Voice; nói câu lệnh, chờ xem trước, sau đó nói `đồng ý` hoặc `hủy`.
- Thử trước bằng cách GÕ vào terminal: `nâng vai đến 120 độ` và `n` để hủy, chỉ dùng góc đã xác nhận.

## Câu lệnh mục tiêu
- CH0: nâng vai đến ... độ; hạ vai đến ... độ
- CH1: duỗi tay đến ... độ; gập tay đến ... độ
- CH2: quay đế đến ... độ
- CH3: xoay cổ tay đến ... độ
- CH4: mở kẹp đến ... độ; đóng kẹp đến ... độ
- Vị trí đã lưu: về vị trí không (SAVE 0); việc gọi vị trí đã lưu cần Python biết dữ liệu tư thế đó qua `poses.json` hoặc phản hồi SAVE; lệnh firmware GO 0 được gửi sau xác nhận.

Lệnh `đồng ý` chỉ thực thi khi đang có kế hoạch chờ xác nhận; `hủy` bỏ kế hoạch. Google không đảm bảo nhận đúng tuyệt đối, nên kiểm tra góc được hiển thị trên màn hình. Không dùng câu lệnh thay thế nút dừng phần cứng. Với CH0/CH1 cần giới hạn cơ cấu liên kết đã xác nhận.

**Lưu ý:** Các từ nâng/hạ, duỗi/gập mô tả ý định, nhưng góc nói là góc servo tuyệt đối, không xác nhận chiều thực tế.
