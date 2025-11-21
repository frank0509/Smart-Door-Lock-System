#include <Keypad.h>            // 4x4 矩陣鍵盤函式庫
#include <ESP32Servo.h>        // ESP32 專用 Servo 函式庫（避免衝突）
#include <LiquidCrystal_I2C.h> // I2C LCD 顯示器函式庫

// ==================== LCD ====================
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 設定 LCD 地址 0x27、顯示 16x2 文字

// ==================== SERVO (伺服馬達) ====================
Servo servo;                 // 宣告伺服物件
const int servoPin = 19;     // 伺服訊號線接 ESP32 GPIO 19

// ==================== BUZZER (蜂鳴器) ====================
const int buzzer = 23;       // 只有鎖定時才會鳴叫，接 GPIO 23

// ==================== RGB LED（共陽）====================
const int redLed = 18;       // 紅色 LED 接 GPIO 18（經 220Ω 電阻）
const int greenLed = 5;      // 綠色 LED 接 GPIO 5（經 220Ω 電阻）

// ==================== PASSWORD 設定 ====================
String password = "1234";    // 預設密碼，可自行更改
String input = "";           // 使用者目前輸入的密碼字串
int attempts = 0;            // 錯誤次數紀錄（3 次鎖定）

// ==================== Keypad 腳位設定 ====================
const byte ROWS = 4;         // 4 列
const byte COLS = 4;         // 4 行

// 鍵盤配置（對應硬體按鍵）
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// 鍵盤 Row 腳位（與 Wokwi 實體一致）
byte rowPins[ROWS] = {32, 33, 25, 26};
// 鍵盤 Column 腳位
byte colPins[COLS] = {27, 14, 12, 13};

// 建立鍵盤物件
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ==================== 初始化 ====================
void setup() {
  // ------ LCD ------
  lcd.init();                // 初始化 LCD
  lcd.backlight();           // 打開背光
  lcd.print("Enter Password:");// 顯示輸入提示

  // ------ 伺服馬達 ------
  servo.attach(servoPin, 500, 2400);  // 連接伺服腳位，設定 PWM 範圍
  servo.write(0);          // 初始關門狀態（0度）

  // ------ LED ------
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(redLed, HIGH);     // 共陽 LED -> HIGH = 關閉
  digitalWrite(greenLed, HIGH);   // 所以一開始兩個都熄滅
}

// ==================== 密碼成功 ====================
void success() {
  lcd.clear();
  lcd.print("Access Granted"); // 顯示成功訊息

  digitalWrite(greenLed, LOW);   // 綠燈亮 (LOW = 亮)
  servo.write(90);               // 門打開 (90度)
  delay(2000);                   // 停留 2 秒
  servo.write(0);                // 門關閉

  digitalWrite(greenLed, HIGH);  // 綠燈關 (HIGH = 關)
}

// ==================== 密碼錯誤（不響） ====================
void failed() {
  lcd.clear();
  lcd.print("Wrong Password");   // 顯示錯誤訊息

  digitalWrite(redLed, LOW);     // 紅燈亮
  delay(600);
  digitalWrite(redLed, HIGH);    // 紅燈關
}

// ==================== 鎖定（錯 3 次才響） ====================
void alarmLock() {
  lcd.clear();
  lcd.print("LOCKED!");           // 顯示鎖定

  // 鎖定警報閃爍 + 蜂鳴器叫
  for(int i = 0; i < 6; i++) {
    digitalWrite(redLed, LOW);   // 紅燈亮
    tone(buzzer, 800, 200);      // 蜂鳴器叫 200ms
    delay(300);
    digitalWrite(redLed, HIGH);  // 紅燈關
    delay(200);
  }

  input = "";                    // 清空輸入
  attempts = 0;                  // 重置錯誤次數
  lcd.clear();
  lcd.print("Enter Password:");
}

// ==================== 主程式 ====================
void loop() {
  char key = keypad.getKey();    // 取得單次按鍵輸入（沒有按就回傳 0）

  if (key) {                     // 如果有按鍵
    if (key == '#') {            // # 表示送出檢查
      if (input == password) {   // 密碼正確
        success();
        attempts = 0;            // 重置錯誤次數
      } else {                   
        attempts++;              // 錯誤次數+1
        failed();                // 顯示錯誤
        if (attempts >= 3) alarmLock(); // 超過 3 次 → 鎖定
      }
      input = "";                // 清空輸入
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else if (key == '*') {       // * 表示清除輸入
      input = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else {                       // 其它按鍵表示輸入密碼
      input += key;              // 加入字串中
      lcd.setCursor(0, 1);
      lcd.print(input);          // 顯示目前輸入內容
    }
  }
}
