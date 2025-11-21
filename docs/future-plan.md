# 🚀 Future Improvements / 未來擴充方向

Below are potential upgrades for the ESP32 Smart Door Lock System.  
以下為可加入的系統擴充與升級功能。

---

## 📡 Telegram Remote Notification / Telegram 遠端通知

### 📌 Description 說明
透過 Wi-Fi 連線，ESP32 可將 **成功解鎖** 或 **錯誤三次** 的資訊傳送至 Telegram Bot。

| Event 事件 | Message 訊息 |
|-----------|--------------|
| 密碼正確 | 🔓 Door unlocked successfully! |
| 錯誤三次 | 🚨 Warning: 3 failed attempts detected! |

### 📬 API Example 範例網址
https://api.telegram.org/bot<你的TOKEN>/sendMessage?chat_id=<CHAT_ID>&text=Hello
> ESP32 可使用 **HTTPS GET/POST** 傳送訊息。

---

## 🌐 Wi-Fi Remote Unlock / Wi-Fi 遠端開鎖

📌 使用 **ESP32 WebServer** 或 HTTP API  
使用者可透過手機 App 或瀏覽器進行開門操作。

💡 可新增：
- Admin Page（管理者界面）
- 修改密碼功能
- 查詢錯誤紀錄

---

## 💾 EEPROM/SPIFFS Password Storage / 密碼永久儲存

📎 密碼透過 EEPROM 或 SPIFFS 保存，下次開機仍有效  
📌 建議加上 **管理者設定模式**

---

## 🆔 RFID or Fingerprint Unlock / RFID 或指紋開門

📌 可加入模組：
- RC522 RFID Reader
- R503 Fingerprint Sensor

👉 增加安全性及多模式驗證。

---

## 🔐 Multi-Factor Authentication / 多重驗證

📎 可結合 **密碼 + RFID** 或 **密碼 + 指紋**  
✔ 更高安全等級  
✔ 更適合實際門鎖使用

---

### 🎯 Summary / 總結

- Telegram 讓門鎖變成「可監控」
- Wi-Fi 提供「遠端操作」
- EEPROM 設定可「永久保存」
- RFID / 指紋 + 密碼「提升安全性」
