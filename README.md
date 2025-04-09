# Oiiai Cat

一個互動式的貓咪裝置，當有人靠近時會播放聲音並旋轉。


https://github.com/user-attachments/assets/7f15e341-0452-4a34-bb66-ef9512a18ff1


![IMG_6395](https://github.com/user-attachments/assets/3e7aedf7-5704-477e-8ee5-a2015b82d16d)
![IMG_6394](https://github.com/user-attachments/assets/5ef4d071-1be4-4a01-a70e-5784b95faca6)
<img width="785" alt="截圖 2025-04-09 晚上11 41 30" src="https://github.com/user-attachments/assets/1eb3f0c4-c485-4721-873d-4dc06b61377a" />


## 硬體需求

- Arduino 開發板 (如 Arduino Uno)
- DFPlayer Mini MP3 播放器模組
- HC-SR04 超音波感測器
- 伺服馬達 (Servo Motor)
- 喇叭 (3W 8Ω)
- 電源供應 (5V)

## 接線說明

### DFPlayer Mini MP3 播放器
- VCC -> 5V
- GND -> GND
- RX -> Arduino Pin 11
- TX -> Arduino Pin 10
- SPK_1, SPK_2 -> 喇叭

### HC-SR04 超音波感測器
- VCC -> 5V
- GND -> GND
- TRIG -> Arduino Pin 8
- ECHO -> Arduino Pin 9

### 伺服馬達
- 紅線 (VCC) -> 5V
- 棕線 (GND) -> GND
- 橙線 (Signal) -> Arduino Pin 6

## 功能說明

1. 當有人靠近裝置 50cm 以內時，會觸發以下動作：
   - 播放預設的 MP3 音檔 (0001.mp3)
   - 伺服馬達開始旋轉
2. 音檔播放結束後，馬達會自動停止
3. 具有防抖動機制，避免重複觸發 (5秒冷卻時間)

## 使用說明

1. 將程式碼上傳至 Arduino 開發板
2. 在 MP3 播放器的 SD 卡中放入名為 "0001.mp3" 的音檔
3. 確保所有硬體正確連接
4. 開啟電源，系統會自動開始運作

## 注意事項

- 請確保 SD 卡格式為 FAT32
- MP3 檔案必須放在 SD 卡的根目錄
- 音檔命名必須為 "0001.mp3"
- 建議使用穩定的 5V 電源供應
