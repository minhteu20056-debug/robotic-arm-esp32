# Robot Arm V5 – Mở rộng câu nói ngắn

Giữ nguyên firmware V3. Không cần nạp Arduino lại. Giữ `live/offsets.json`, `live/poses.json` nếu đã hiệu chuẩn, và thư mục `live/vosk-model-small-vn-0.4` khi giải nén/cập nhật.

Những câu bổ sung:
- "Vị trí một", "về vị trí số hai" → GO 1 / GO 2, chỉ khi Python đã biết góc vị trí lưu.
- "Lưu vị trí một" → SAVE 1, đợi "đồng ý" rồi mới gửi; KHÔNG chuyển động servo. SAVE đòi hỏi ESP32 đã có trạng thái góc của đủ 5 kênh. Firmware hỗ trợ vị trí 0–4.
- "Xem góc" → GETANGLES; "Trạng thái robot" → STATUS; "Kiểm tra joystick" → JOYSTICK STATUS. Các lệnh này chỉ truy vấn.
- "Quay đế trái" / "quay đế phải" → xoay tương đối, cần góc CH2 hợp lệ.
- "Đế đến 90 độ", "Cổ tay đến 80 độ", "Vai đến 120 độ", "Tay đến 130 độ", "Kẹp đến 70 độ" → góc servo tuyệt đối; yêu cầu xác nhận. Các số chỉ minh họa, KHÔNG phải giới hạn an toàn.
- "Nâng vai đến [góc] độ", "Duỗi tay đến [góc] độ", "Mở kẹp đến [góc] độ" vẫn dùng như bản V4.

Google nhận diện tự do; Vosk dùng grammar danh sách cụm từ. Với câu có độ bất kỳ, Google thường phù hợp hơn. Câu nhận diện không hợp lệ bị từ chối. `STOP` firmware có thể không ngắt chuyển động thực, nên không dùng làm dừng khẩn cấp. Việc xem trước PyBullet không bảo đảm tránh va chạm cơ cấu thật. Lệnh SAVE/GO và các giới hạn phải được thử thủ công trước.

**Chạy:** `& "$HOME\miniforge3\envs\robot\python.exe" .\live\arm_live.py --port COM3 --no-info` (thay COM3 theo máy).
