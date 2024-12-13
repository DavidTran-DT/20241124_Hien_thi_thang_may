// // #include <Arduino.h>

// // Định nghĩa các chân SPI
// #define DIN 11  // Chân MOSI (Dữ liệu vào MAX7219)
// #define CLK 13  // Chân SCK (Xung nhịp)
// #define LOAD 10 // Chân CS (Chọn chip)

// // Số lượng MAX7219 (2 ma trận LED)
// #define NUM_MAX 2

// // Bảng dữ liệu để hiển thị các số từ 0 đến 9
// byte digits[10][8] = {
//     {0x3c, 0x66, 0x66, 0x6e, 0x76, 0x66, 0x66, 0x3c}, // Số 0
//     {0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e}, // Số 1
//     {0x3c, 0x66, 0x06, 0x0c, 0x18, 0x30, 0x66, 0x7e}, // Số 2
//     {0x3c, 0x66, 0x06, 0x1c, 0x06, 0x06, 0x66, 0x3c}, // Số 3
//     {0x0c, 0x1c, 0x3c, 0x6c, 0x7e, 0x0c, 0x0c, 0x0c}, // Số 4
//     {0x7e, 0x60, 0x60, 0x7c, 0x06, 0x06, 0x66, 0x3c}, // Số 5
//     {0x3c, 0x66, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x3c}, // Số 6
//     {0x7e, 0x06, 0x06, 0x0c, 0x18, 0x30, 0x30, 0x30}, // Số 7
//     {0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x66, 0x3c}, // Số 8
//     {0x3c, 0x66, 0x66, 0x3e, 0x06, 0x06, 0x66, 0x3c}  // Số 9
// };

// // Hàm gửi dữ liệu SPI đến MAX7219
// void sendToMax(int chip, byte address, byte data)
// {
//   digitalWrite(LOAD, LOW);
//   for (int i = 0; i < NUM_MAX; i++)
//   {
//     if (i == chip)
//     {
//       shiftOut(DIN, CLK, MSBFIRST, address);
//       shiftOut(DIN, CLK, MSBFIRST, data);
//     }
//     else
//     {
//       shiftOut(DIN, CLK, MSBFIRST, 0);
//       shiftOut(DIN, CLK, MSBFIRST, 0);
//     }
//   }
//   digitalWrite(LOAD, HIGH);
// }

// // Khởi tạo MAX7219
// void initMax()
// {
//   for (int i = 0; i < NUM_MAX; i++)
//   {
//     sendToMax(i, 0x09, 0x00); // Decode mode: Tắt
//     sendToMax(i, 0x0A, 0x08); // Độ sáng
//     sendToMax(i, 0x0B, 0x07); // Hiển thị 8 hàng
//     sendToMax(i, 0x0C, 0x01); // Chế độ hoạt động
//     sendToMax(i, 0x0F, 0x00); // Tắt chế độ kiểm tra
//   }
// }

// // Hiển thị một số trên LED ma trận
// void displayNumber(int chip, int number)
// {
//   for (int i = 0; i < 8; i++)
//   {
//     sendToMax(chip, i + 1, digits[number][i]);
//   }
// }

// void setup()
// {
//   pinMode(DIN, OUTPUT);
//   pinMode(CLK, OUTPUT);
//   pinMode(LOAD, OUTPUT);

//   digitalWrite(LOAD, HIGH);

//   initMax();
// }

// void loop()
// {
//   for (int i = 0; i <= 16; i++)
//   {
//     int tens = i / 10;  // Hàng chục
//     int units = i % 10; // Hàng đơn vị

//     // Hiển thị hàng chục trên ma trận 1
//     if (i >= 10)
//     {
//       displayNumber(0, tens); // Ma trận 1
//     }
//     else
//     {
//       // Xóa ma trận 1 nếu không cần hiển thị
//       for (int j = 0; j < 8; j++)
//       {
//         sendToMax(0, j + 1, 0x00);
//       }
//     }

//     // Hiển thị hàng đơn vị trên ma trận 2
//     displayNumber(1, units); // Ma trận 2

//     delay(1000); // Dừng 1 giây trước khi tăng số
//   }
// }
