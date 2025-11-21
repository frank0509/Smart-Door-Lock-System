#include <Arduino.h>
#include <Keypad.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

// === LCD ===
LiquidCrystal_I2C lcd(0x27, 16, 2);

// === SERVO (腳位 19) ===
Servo servo;
const int servoPin = 19;

// === BUZZER (23) - 只有鎖定才響 ===
const int buzzer = 23;

// === RGB LED (共陽極) ===
const int redLed = 18;
const int greenLed = 5;

// === PASSWORD ===
String password = "1234";
String input = "";
int attempts = 0;

// === KEYPAD ===
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {32, 33, 25, 26};
byte colPins[COLS] = {27, 14, 12, 13};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Enter Password:");

  // SERVO
  servo.attach(servoPin, 500, 2400);
  servo.write(0);

  // LED
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(redLed, HIGH);    // 共陽關閉
  digitalWrite(greenLed, HIGH);
}

// ============ SUCCESS ============
void success() {
  lcd.clear();
  lcd.print("Access Granted");

  digitalWrite(greenLed, LOW);   // 綠燈亮

  servo.write(90);              // 開門
  delay(2000);
  servo.write(0);               // 關門

  digitalWrite(greenLed, HIGH); // 綠燈關
}

// ============ FAIL (不響) ============
void failed() {
  lcd.clear();
  lcd.print("Wrong Password");

  digitalWrite(redLed, LOW);
  delay(600);
  digitalWrite(redLed, HIGH);
}

// ============ ALARM LOCK (響！！) ============
void alarmLock() {
  lcd.clear();
  lcd.print("LOCKED!");

  for(int i = 0; i < 6; i++) {
    digitalWrite(redLed, LOW);
    tone(buzzer, 800, 200);     // 🔔 只有這裡響！
    delay(300);
    digitalWrite(redLed, HIGH);
    delay(200);
  }

  input = "";
  attempts = 0;
  lcd.clear();
  lcd.print("Enter Password:");
}

// ============ MAIN LOOP ============
void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {                // submit
      if (input == password) {
        success();
        attempts = 0;
      } else {
        attempts++;
        failed();
        if (attempts >= 3) alarmLock();
      }
      input = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else if (key == '*') {           // clear
      input = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else {                           // typing
      input += key;
      lcd.setCursor(0, 1);
      lcd.print(input);
    }
  }
}
