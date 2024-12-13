# 20241124_Hiển thị thang máy

## Giới thiệu
Dự án này sử dụng **Arduino Uno** và **2 module LED ma trận IC MAX7219** để hiển thị thông tin thang máy:
- **LED ma trận 1**: Hiển thị số tầng.
- **LED ma trận 2**: Hiển thị hướng di chuyển (Lên hoặc Xuống).

## Mục tiêu
- Hiển thị rõ ràng và dễ dàng theo dõi trạng thái hoạt động của thang máy.
- Tích hợp đơn giản, sử dụng linh kiện phổ biến và dễ lập trình.

## Yêu cầu phần cứng
- 1 x Arduino Uno.
- 2 x Module LED ma trận 8x8 (IC MAX7219).
- Dây nối jumper.
- Nguồn điện cho Arduino.

## Yêu cầu phần mềm
- Arduino IDE.

## Kết nối phần cứng
Kết nối các chân của module LED ma trận với Arduino Uno như sau:

### LED ma trận 1 (Hiển thị số tầng)
- **VCC** → 5V.
- **GND** → GND.
- **DIN** → Chân D11 (MOSI).
- **CS** → Chân D10.
- **CLK** → Chân D13 (SCK).

### LED ma trận 2 (Hiển thị chiều lên/xuống)
- **VCC** → 5V.
- **GND** → GND.
- **DIN** → Chân D11 (MOSI) (chung với LED 1).
- **CS** → Chân D9.
- **CLK** → Chân D13 (SCK) (chung với LED 1).