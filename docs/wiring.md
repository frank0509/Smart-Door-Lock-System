## 🔌 ESP32 Smart Door Lock — Wiring Diagram 接線說明

本系統使用 ESP32 搭配：4×4 Keypad、I2C LCD、SG90 Servo、共陽 RGB LED、與有源蜂鳴器。  
以下為 **可直接照圖與顏色接線** 的高可讀格式。

---

### 🔢 Keypad (4×4 Matrix) 矩陣鍵盤
📌 **8 根訊號線直接連接 ESP32，不需電阻**

| Row/Column | ESP32 | 線色 |
|---|---|---|
| R1 | GPIO 32 | 🔵 藍色 |
| R2 | GPIO 33 | 🔵 |
| R3 | GPIO 25 | 🔵 |
| R4 | GPIO 26 | 🔵 |
| C1 | GPIO 27 | 🔵 |
| C2 | GPIO 14 | 🔵 |
| C3 | GPIO 12 | 🔵 |
| C4 | GPIO 13 | 🔵 |

💡 Keypad 全部使用 **藍色資料線**。

---

### 📺 I2C LCD (16×2)
| Pin | ESP32 | 線色 |
|---|---|---|
| SDA | GPIO 21 | 🟢 綠色 |
| SCL | GPIO 22 | 🟡 黃色 |
| VCC | 5V | 🔴 紅色 |
| GND | GND | ⚫ 黑色 |

💡 透過 I2C 通訊，只需要 **2 條資料線 + 5V + GND**。

---

### 🔓 SG90 Servo Motor 伺服馬達
| Servo | ESP32 | 線色 |
|---|---|---|
| Signal | GPIO 19 | 🟣 **粉紅色** |
| VCC | 5V | 🔴 |
| GND | GND | ⚫ |

⚠ **必須接 5V，不可接 3.3V！**  
⚠ 如果轉不動，就是因為電壓錯誤或 USB 供電太弱。

---

### 🌈 RGB LED (Common Anode) 共陽 RGB LED
| LED Pin | ESP32 | 線色 |
|---|---|---|
| COM (+) | 5V | ⚫ 黑色 |
| Red (經 220Ω) | GPIO 18 | 🔴 |
| Green (經 220Ω) | GPIO 5 | 🟢 |
| Blue | 未使用 | — |

📌 **共陽接法**  
- **COM(+) 接到 5V**
- **LOW = 亮燈，HIGH = 熄滅**

---

### 🔔 Active Buzzer 有源蜂鳴器
| Pin | ESP32 | 線色 |
|---|---|---|
| + | GPIO 23 | 🟡 黃色 |
| – | GND | ⚫ 黑色 |

📌 有源蜂鳴器通電就會叫，用 `tone()`、`digitalWrite()` 皆可。

---

### ⚡ Power Notes 電源注意事項
- 所有模組都是 **5V 電源**
- **全部 GND 必須共地**
- ESP32 可由 **USB 供電** 帶動整套系統

---

### 🎨 Wire Color Summary 線材顏色統一
| 顏色 | 用途 |
|---|---|
| 🔴 紅色 | 5V、Servo VCC、LED R |
| ⚫ 黑色 | GND、LED 共陽、蜂鳴器 – |
| 🟣 粉紅色 | Servo 訊號 |
| 🟢 綠色 | LCD SDA、LED G |
| 🟡 黃色 | LCD SCL、蜂鳴器 + |
| 🔵 藍色 | Keypad 資料線 |

---
