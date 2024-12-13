#include <Arduino.h>

// Định nghĩa các chân SPI
#define DIN 11  // Chân MOSI (Dữ liệu vào MAX7219)
#define CLK 13  // Chân SCK (Xung nhịp)
#define LOAD 10 // Chân CS (Chọn chip)

// Số lượng MAX7219 (2 ma trận LED)
#define NUM_MAX 2

#define SW1 4
#define SW2 5
#define SW3 6
#define SW4 7
#define SW5 8
#define SW6 9

// Bảng dữ liệu để hiển thị các số từ 0 đến 9
byte digits[10][8] = {
    {0x3c, 0x66, 0x66, 0x6e, 0x76, 0x66, 0x66, 0x3c}, // Số 0
    {0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e}, // Số 1
    {0x3c, 0x66, 0x06, 0x0c, 0x18, 0x30, 0x66, 0x7e}, // Số 2
    {0x3c, 0x66, 0x06, 0x1c, 0x06, 0x06, 0x66, 0x3c}, // Số 3
    {0x0c, 0x1c, 0x3c, 0x6c, 0x7e, 0x0c, 0x0c, 0x0c}, // Số 4
    {0x7e, 0x60, 0x60, 0x7c, 0x06, 0x06, 0x66, 0x3c}, // Số 5
    {0x3c, 0x66, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x3c}, // Số 6
    {0x7e, 0x06, 0x06, 0x0c, 0x18, 0x30, 0x30, 0x30}, // Số 7
    {0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x66, 0x3c}, // Số 8
    {0x3c, 0x66, 0x66, 0x3e, 0x06, 0x06, 0x66, 0x3c}  // Số 9
};

// Dữ liệu cho mũi tên đi lên
byte arrowUp[8] = {0x00, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x00};

// Dữ liệu cho mũi tên đi xuống
byte arrowDown[8] = {0x00, 0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18, 0x00};

byte letterG[8] = {0x3e, 0x60, 0x60, 0x60, 0x6e, 0x66, 0x66, 0x3e};

unsigned long previousMillis = 0;
const long interval = 10; // Thời gian thay đổi số (1 giây)
int arrowDelay = 200;     // Thời gian delay cho hiệu ứng mũi tên

// Hàm gửi dữ liệu SPI đến MAX7219
void sendToMax(int chip, byte address, byte data)
{
  digitalWrite(LOAD, LOW);
  for (int i = 0; i < NUM_MAX; i++)
  {
    if (i == chip)
    {
      shiftOut(DIN, CLK, MSBFIRST, address);
      shiftOut(DIN, CLK, MSBFIRST, data);
    }
    else
    {
      shiftOut(DIN, CLK, MSBFIRST, 0);
      shiftOut(DIN, CLK, MSBFIRST, 0);
    }
  }
  digitalWrite(LOAD, HIGH);
}

// Khởi tạo MAX7219
void initMax()
{
  for (int i = 0; i < NUM_MAX; i++)
  {
    sendToMax(i, 0x09, 0x00); // Decode mode: Tắt
    sendToMax(i, 0x0A, 0x08); // Độ sáng
    sendToMax(i, 0x0B, 0x07); // Hiển thị 8 hàng
    sendToMax(i, 0x0C, 0x01); // Chế độ hoạt động
    sendToMax(i, 0x0F, 0x00); // Tắt chế độ kiểm tra
  }
}

// Hiển thị một số trên LED ma trận
void displayNumber(int chip, int number)
{
  for (int i = 0; i < 8; i++)
  {
    sendToMax(chip, i + 1, digits[number][i]);
  }
}

// Hiệu ứng mũi tên chạy lên trên LED ma trận
void animateArrowUp(int chip)
{
  byte temp[8]; // Sao chép dữ liệu của mũi tên
  memcpy(temp, arrowUp, 8);

  for (int step = 0; step < 8; step++) // Lặp lại hiệu ứng 8 lần
  {
    // Gửi từng dòng dữ liệu đến ma trận LED
    for (int i = 0; i < 8; i++)
    {
      sendToMax(chip, i + 1, temp[i]);
    }

    // Di chuyển mũi tên lên một dòng
    byte firstRow = temp[0]; // Lưu dòng đầu tiên
    for (int i = 0; i < 7; i++)
    {
      temp[i] = temp[i + 1];
    }
    temp[7] = firstRow; // Đưa dòng đầu tiên xuống dòng cuối

    delay(arrowDelay); // Thời gian chờ giữa các bước
  }
}

// Hiệu ứng mũi tên đi xuống trên LED ma trận
void animateArrowDown(int chip)
{
  byte temp[8]; // Sao chép dữ liệu của mũi tên
  memcpy(temp, arrowDown, 8);

  for (int step = 0; step < 8; step++) // Lặp lại hiệu ứng 8 lần
  {
    // Gửi từng dòng dữ liệu đến ma trận LED
    for (int i = 0; i < 8; i++)
    {
      sendToMax(chip, i + 1, temp[i]);
    }

    // Di chuyển mũi tên xuống một dòng
    byte lastRow = temp[7]; // Lưu dòng cuối cùng
    for (int i = 7; i > 0; i--)
    {
      temp[i] = temp[i - 1];
    }
    temp[0] = lastRow; // Đưa dòng cuối cùng lên dòng đầu

    delay(arrowDelay); // Thời gian chờ giữa các bước
  }
}

void setup()
{
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LOAD, OUTPUT);

  digitalWrite(LOAD, HIGH);

  initMax();

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
  pinMode(SW5, INPUT);
  pinMode(SW6, INPUT);
}

void loop()
{
  unsigned long currentMillis = millis();

  // Nếu đến thời gian thay đổi số
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    // Kiểm tra trạng thái của các công tắc và hiển thị số tương ứng trên ma trận LED
    if (digitalRead(SW1) == LOW)
    {
      displayNumber(0, 1); // Hiển thị số 1 trên ma trận LED đầu tiên khi SW1 nhấn
    }
    else if (digitalRead(SW2) == LOW)
    {
      displayNumber(0, 2); // Hiển thị số 2 trên ma trận LED đầu tiên khi SW2 nhấn
    }
    else if (digitalRead(SW3) == LOW)
    {
      displayNumber(0, 3); // Hiển thị số 3 trên ma trận LED đầu tiên khi SW3 nhấn
    }
    else if (digitalRead(SW4) == LOW)
    {
      displayNumber(0, 4); // Hiển thị số 4 trên ma trận LED đầu tiên khi SW4 nhấn
    }
    else
    {
      for (int i = 0; i < 8; i++)
      {
        sendToMax(0, i + 1, letterG[i]); // Hiển thị chữ G trên ma trận LED đầu tiên
      }
    }
  }

  if (digitalRead(SW5) == LOW)
    animateArrowUp(1);
  else if((digitalRead(SW6) == LOW))
    animateArrowDown(1); // Chạy hiệu ứng mũi tên trên ma trận LED thứ hai
}
