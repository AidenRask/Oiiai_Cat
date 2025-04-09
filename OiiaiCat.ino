#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <Servo.h>

// === 超音波腳位設定 ===
const int trigPin = 8;
const int echoPin = 9;

// === 馬達腳位設定 ===
const int motorPin = 6;

// === 馬達與狀態控制 ===
Servo myServo;
bool isPlaying = false;
bool isDetected = false;
unsigned long lastTriggerTime = 0;
const unsigned long debounceDelay = 5000; // 毫秒

// === MP3 播放器回呼函數 ===
class Mp3Notify {
  public:
    static void OnError(DFMiniMp3<SoftwareSerial, Mp3Notify>& mp3, uint16_t errorCode) {
      Serial.print("MP3 Error: ");
      Serial.println(errorCode);
    }

    static void OnPlayFinished(DFMiniMp3<SoftwareSerial, Mp3Notify>& mp3, DfMp3_PlaySources source, uint16_t track) {
      Serial.print("MP3 播放完畢，曲目：");
      Serial.println(track);
      
      // 停止馬達
      myServo.writeMicroseconds(1500); // 回到停止狀態
      isPlaying = false;
    }

    static void OnPlaySourceOnline(DFMiniMp3<SoftwareSerial, Mp3Notify>& mp3, DfMp3_PlaySources source) {}
    static void OnPlaySourceInserted(DFMiniMp3<SoftwareSerial, Mp3Notify>& mp3, DfMp3_PlaySources source) {}
    static void OnPlaySourceRemoved(DFMiniMp3<SoftwareSerial, Mp3Notify>& mp3, DfMp3_PlaySources source) {}
};

// === 設定 DFPlayer Serial 與物件 ===
SoftwareSerial secondarySerial(11, 10); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

void setup() {
  Serial.begin(9600);
  secondarySerial.begin(9600);

  delay(1000); // 等 DFPlayer 穩定上電
  mp3.begin();
  mp3.setVolume(15); // 音量：0 ~ 30

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(motorPin);
  myServo.writeMicroseconds(1500); // 初始為停止

  Serial.println("系統啟動，準備感應...");
}

void loop() {
  mp3.loop(); // 處理非同步事件

  long distance = readDistance();

  if (distance > 0 && distance < 50 && !isPlaying && millis() - lastTriggerTime > debounceDelay) {
    Serial.println("偵測到觀眾靠近，開始播放與旋轉！");
    lastTriggerTime = millis();
    isPlaying = true;

    mp3.playMp3FolderTrack(1);              // 播放 MP3（0001.mp3）
    myServo.writeMicroseconds(1300);        // 馬達旋轉
  }
}

// === 超音波距離讀取 ===
long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 最多等 30ms
  if (duration == 0) return -1; // 無回應

  long distance = duration * 0.034 / 2;
  return distance;
}