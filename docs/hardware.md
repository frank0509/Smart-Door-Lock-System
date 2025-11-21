# 🧰 Hardware Used / 使用元件與用途

This document lists all components of the ESP32 Smart Door Lock System, their functions, and notes.  
本文件列出智慧門鎖所使用的所有硬體元件、功能與注意事項。

---

| Component 元件 | Purpose 用途 | Notes 備註 |
|----------------|--------------|------------|
| **ESP32 DevKit V1** | 主控制器，用於處理密碼驗證、驅動 LCD、鍵盤、伺服與蜂鳴器 | 支援 Wi-Fi，可擴充 Telegram 遠端通知 |
| **4×4 Keypad** | 密碼輸入裝置 | 需接 8 條 GPIO，使用 Keypad Library |
| **16×2 I2C LCD** | 顯示密碼輸入與解鎖狀態 | 使用 I2C 僅需 SDA/SCL 兩條資料線 |
| **SG90 Servo Motor** | 控制門鎖開/關 | 需使用 5V 供電，訊號腳接 PWM (GPIO19) |
| **Active Buzzer 有源蜂鳴器** | 輸入錯誤提示與警報 | 無需音階控制，通電即可鳴叫 |
| **RGB LED（Common Anode 共陽）** | 成功/錯誤狀態指示燈 | 共陽，COM 接 5V，LOW = 亮燈 |
| **220Ω Resistors（x2）** | 限制紅色與綠色 LED 電流 | 避免 LED 燒毀 |
| **USB 5V Power** | 供應整套系統電力 | 可直接由 ESP32 USB 提供 |

---

### ⚠ Power Notes / 電源注意事項

- Servo、LED、LCD、ESP32 **全部使用 5V**
- **Servo 不可接 3.3V**
- **所有 GND 必須共地**

---

### 🌈 RGB LED Special Note / 共陽 LED 特性

| LED Type 類型 | COM 連接 | 控制方式 |
|--------------|----------|----------|
| 共陽 Common Anode | 5V | `LOW = ON`、`HIGH = OFF` |
| 共陰 Common Cathode | GND | `HIGH = ON`、`LOW = OFF` |

👉 本專案使用 **共陽 LED**

---

### 🎯 Summary / 總結

- ESP32 負責控制全部裝置  
- 伺服實際模擬「門鎖開啟」  
- LCD 與 RGB + Buzzer 作為 **使用者回饋介面**
