#include <TFT_eSPI.h> 
#include <Arduino.h> 

int LDR_PIN = 17;  // 조도 센서를 연결한 핀
int LuxValue = 0;  // 조도 센서 값 저장 변수
float EMAValue = 0;  // EMA 값 저장 변수
float alpha = 0.1; // EMA를 위한 알파 값(가중치)

TFT_eSPI tft = TFT_eSPI(); 

void setup() { 
    Serial.begin(115200);
    tft.init(); 
    tft.setRotation(1); 
    tft.fillScreen(TFT_BLACK); 
    tft.setTextColor(TFT_WHITE); 
}

void loop(){
    LuxValue = analogRead(LDR_PIN); // 조도 센서 값 읽기
    
    // EMA(t) = alpha * Lux(t) + (1 - alpha) * EMA(t-1)
    EMAValue = alpha * LuxValue + (1 - alpha) * EMAValue;  // EMA 계산

    // 시리얼 모니터에 Lux와 EMA 값 출력
    Serial.print("Lux: ");
    Serial.print(LuxValue);
    Serial.print(", EMA: ");
    Serial.println(EMAValue, 2);  // 소수점 이하 2자리로 출력


    // LCD에 Lux와 EMA 값 출력
    String Lux = "Lux: " + String(LuxValue); // 조도 값을 문자열로 변환
    String EMA = "EMA: " + String(EMAValue, 2); // EMA 값을 문자열로 변환
    
    tft.fillScreen(TFT_BLACK);
    tft.drawString(Lux, 10, 40, 4);
    tft.drawString(EMA, 10, 70, 4);
    
    delay(500); // 0.5초 간격으로 값 읽기
}
