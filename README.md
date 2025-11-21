# 🔐 Smart Door Lock System (ESP32)  
**智慧電子密碼門鎖（ESP32）**

A smart password-protected lock based on **ESP32**, featuring **4×4 keypad input**, **LCD display**, **servo motor**, **buzzer alert**, and **RGB LED indicator (common anode)**.  
本系統使用 **ESP32** 搭配 **4×4 鍵盤、LCD 顯示、伺服馬達、蜂鳴器與 RGB 共陽 LED**，實作具安全警告功能的智慧密碼門鎖，可於 **Wokwi 完整模擬或實體部署**。

---

## 📌 Features / 功能介紹

| Feature 功能 | Description 說明 |
|--------------|------------------|
| 🔢 Password Input | 使用 **4×4 矩陣鍵盤**輸入密碼 |
| 📺 LCD Status Display | 顯示「輸入中 / 成功 / 錯誤 / 鎖定」 |
| 🔓 Servo Unlock | 密碼正確時伺服馬達旋轉解鎖 |
| 🔔 Buzzer Feedback | 利用蜂鳴器提供提示與警報 |
| 🌈 RGB LED Indicator | 共陽 RGB LED 顯示成功(綠) / 錯誤(紅) |
| 🚨 Intruder Lockdown | 密碼錯誤 **連續 3 次** 觸發鎖定與警報 |
| 💻 Wokwi Simulation | 可於 Wokwi 線上完整模擬，無需實體裝置 |

---

## 🧑‍💻 Author / 作者  
**Wu Fu-Min (吳富民)**  
Department of Computer Science and Information Engineering  
Kun Shan University / 崑山科技大學資工系

---

## 🧱 Hardware Components / 硬體元件

| Component 元件 | Qty 數量 |
|----------------|---------|
| ESP32 DevKit V1 | 1 |
| 4×4 Keypad 矩陣鍵盤 | 1 |
| 16×2 I2C LCD (0x27) | 1 |
| SG90 Servo 伺服馬達 | 1 |
| Buzzer 蜂鳴器 | 1 |
| RGB LED（共陽 Common Anode）| 1 |
| 220Ω Resistor（R / G）| 2 |
| Breadboard & Jumper Wires 麵包板與杜邦線 | 若干 |

🔌 Full wiring diagram / 完整接線圖：`docs/wiring.md`

---

## 🔌 Pin Mapping / 腳位對應

### 📺 LCD (I2C)

| LCD Pin | ESP32 GPIO |
|--------|-----------|
| VCC    | 5V        |
| GND    | GND       |
| SDA    | 21        |
| SCL    | 22        |

### 🔢 Keypad 4×4

| Keypad | ESP32 GPIO |
|--------|-----------|
| R1 | 32 |
| R2 | 33 |
| R3 | 25 |
| R4 | 26 |
| C1 | 27 |
| C2 | 14 |
| C3 | 12 |
| C4 | 13 |

### 🔓 Servo

| Servo | ESP32 GPIO |
|-------|-----------|
| VCC   | 5V        |
| GND   | GND       |
| SIG   | 19        |

### 🔔 Buzzer

| Buzzer | ESP32 GPIO |
|--------|-----------|
| +      | 23        |
| -      | GND       |

### 🌈 RGB LED（共陽 Common Anode）

| LED Pin 腳位 | ESP32 GPIO |
|--------------|-----------|
| COM(+) | 5V |
| R + 220Ω | 18 |
| G + 220Ω | 5 |
| B | (not used) 未使用 |

> ⚠ **Common Anode RGB LED**  
> HIGH = OFF，LOW = ON  
> 共陽 LED **亮燈時輸出 LOW**、關燈輸出 HIGH。

---

## 🧾 Default Password / 預設密碼

- Default password / 預設密碼：`1234`
- Key Usage / 鍵盤操作：
  - `0–9, A–D`：輸入數字
  - `#`：Confirm / 送出
  - `*`：Clear / 清除輸入

---

## 🧠 System Logic / 系統流程

1. LCD 顯示 `Enter Password:`  
2. 使用者輸入密碼，LCD 第二行顯示輸入內容  
3. 按下 `#`：
   - 若密碼正確：
     - 顯示 `Access Granted`  
     - 亮綠燈（RGB G = LOW）  
     - 伺服馬達開啟 90°  
   - 若密碼錯誤：
     - 顯示 `Wrong Password`
     - 亮紅燈（RGB R = LOW）
     - 錯誤次數 +1  
4. 若錯誤次數 ≥ 3：
   - 顯示 `LOCKED!`
   - 紅燈閃爍、蜂鳴器警報多次
   - 鎖定後重置輸入與錯誤次數

---

## 💻 Source Code / 程式碼位置

📁 Path 路徑：`/src/SmartDoorLock_ESP32.ino`

- Keypad 密碼輸入
- LCD 顯示
- Servo 控制開鎖
- Buzzer 警示音效
- RGB 成功 / 失敗顯示
- 三次錯誤安全鎖定

---

## 🌐 Wokwi Simulation / 線上模擬

🔗 Link / 連結：https://wokwi.com/projects/448227263625126913 

📌 You can / 你可以：
- Press keypad buttons / 模擬按鍵輸入  
- Watch LCD messages / 查看 LCD 顯示  
- Observe servo & LED / 觀察伺服與燈號  
- Hear buzzer alert / 模擬蜂鳴器音效  

---

## 🚀 Future Improvements / 未來可改進方向

| Feature | 說明 |
|---------|------|
| 📡 Telegram Notification | 密碼成功 / 失敗三次 → 傳給 Telegram Bot |
| 🌐 Wi-Fi Remote Unlock | 支援遠端手機或網頁操作開門 |
| 💾 EEPROM/SPIFFS Storage | 密碼永久儲存，不因斷電消失 |
| 🔑 Admin Password Mode | 支援管理者修改密碼 |
| 🆔 RFID/Fingerprint | 加入 RFID 或指紋辨識模組提升安全性 |

📬 **Telegram Notification Preview / 訊息範例**  
- 🔓 `Door unlocked successfully!`（密碼解鎖成功）  
- 🚨 `Warning: 3 failed attempts detected!`（錯誤三次，疑似入侵）

---

## 📄 License 授權

This project is for academic and personal learning use.  
本專案開放作為學習用途，禁止未授權商業使用。
