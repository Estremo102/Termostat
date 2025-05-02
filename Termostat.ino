#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_ST7735.h> 
#include <SPI.h>
#include <Wire.h>

#define TFT_CS 10
#define TFT_RST 8
#define TFT_DC 9
#define ENC_A 2  // S1
#define ENC_B 4  // S2
#define ENC_SW 3 // KEY
#define SWITCH 7

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_AHTX0 aht;
sensors_event_t humidity, temp;

float T_aht, hum_aht, T_min = 19, T_max = 19.5, hysteresis = 0.5;
bool heating = false, refreshGUI = false;

int bpc = 0, language = 0;

void setup(){
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  printCopyright();
  Serial.begin(9600);
  aht.begin();
  pinMode(SWITCH, OUTPUT);
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  pinMode(ENC_SW, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENC_A), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_SW), handleEncoderButton, CHANGE);
  drawGUI();
}

void loop() {
  aht.getEvent(&humidity, &temp);
  T_aht = temp.temperature;
  hum_aht = humidity.relative_humidity;

  if(heating && (T_aht > T_max)) 
  {
    heating = false;
    digitalWrite(SWITCH, LOW);
    tft.fillCircle(65, 50, 3, ST7735_BLACK);
  }
  else if(!heating && (T_aht < T_min)) 
  {
    heating = true;
    digitalWrite(SWITCH, HIGH);
    tft.fillCircle(65, 50, 3, ST7735_RED);
  }
  if(refreshGUI){
    refreshGUI = false;
    drawGUI();
  }
  showData();
}

void drawGUI(){
  tft.fillScreen(ST7735_BLACK);

  for(int i = 0; i < 3; i++){
    tft.drawRoundRect(i, i, 78 - 2*i, 62 - 2*i, 5, ST7735_RED);
    tft.drawRoundRect(i, 64 + i, 78 - 2*i, 62 - 2*i, 5, ST7735_BLUE);
    tft.drawRoundRect(80+i, i, 78 - 2*i, 62 - 2*i, 5, ST7735_GREEN);
    tft.drawRoundRect(80 + i, 64 + i, 78 - 2*i, 62 - 2*i, 5, ST7735_YELLOW);
  }
  
  switch(abs(language%3)){
    case 0:
      drawPolishGUI();
      break;
    case 1:
      drawEnglishGUI();
      break;
    case 2:
      drawSpanishGUI();
      break;
  }
  
  tft.drawCircle(65, 50, 5, ST7735_RED);
  tft.drawCircle(145, 50, 5, ST7735_GREEN);
  tft.drawCircle(65, 114, 5, ST7735_BLUE);
  tft.drawCircle(145, 114, 5, ST7735_YELLOW);
  
  drawSelectedCircle();
  showData();
}

void drawPolishGUI(){
  tft.setTextSize(1);

  tft.setTextColor(ST7735_RED, ST7735_BLACK);
  tft.setCursor(6, 5);
  tft.print("TEMPERATURA");

  tft.setTextColor(ST7735_BLUE, ST7735_BLACK);
  tft.setCursor(10, 69);
  tft.print("WILGOTNOSC");
  tft.setCursor(22, 110);
  tft.print("POLSKI");

  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(86, 5);
  tft.print("TEMPERATURA");
  tft.setCursor(100, 14);
  tft.print("ZADANA");

  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  tft.setCursor(92, 69);
  tft.print("HISTEREZA");
}

void drawEnglishGUI(){
  tft.setTextSize(1);

  tft.setTextColor(ST7735_RED, ST7735_BLACK);
  tft.setCursor(6, 5);
  tft.print("TEMPERATURE");

  tft.setTextColor(ST7735_BLUE, ST7735_BLACK);
  tft.setCursor(16, 69);
  tft.print("HUMIDITY");
  tft.setCursor(16, 110);
  tft.print("ENGLISH");


  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(86, 5);
  tft.print("TEMPERATURE");
  tft.setCursor(110, 14);
  tft.print("SET");

  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  tft.setCursor(90, 69);
  tft.print("HYSTERESIS");
}

void drawSpanishGUI(){
  tft.setTextSize(1);

  tft.setTextColor(ST7735_RED, ST7735_BLACK);
  tft.setCursor(6, 5);
  tft.print("TEMPERATURA");

  tft.setTextColor(ST7735_BLUE, ST7735_BLACK);
  tft.setCursor(16, 69);
  tft.print("HUMEDAD");
  tft.setCursor(16, 110);
  tft.print("ESPANOL");

  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(86, 5);
  tft.print("TEMPERATURA");
  tft.setCursor(86, 14);
  tft.print("ESTABLECIDA");

  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  tft.setCursor(90, 69);
  tft.print("HISTERESIS");
}

void showData(){
  tft.setTextSize(2);

  tft.setTextColor(ST7735_RED, ST7735_BLACK);
  tft.setCursor(10,25);
  tft.print(String(T_aht, 1) + "C");

  tft.setTextColor(ST7735_BLUE, ST7735_BLACK);
  tft.setCursor(10,90);
  tft.print(String(hum_aht, 1) + "%");

  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(90,25);
  if(T_min > 0 && T_min < 10){
    tft.print(" " + String(T_min, 1) + "C");
  }else{
    tft.print(String(T_min, 1) + "C");
  }

  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  tft.setCursor(95,90);
  tft.print(String(hysteresis, 1) + "C");
}

void printCopyright() {
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.println("TERMOSTAT 1.2.0");
  delay(250);
  tft.println("DOMINIK MOZDZEN");
  delay(250);
  tft.println("PODZIEKOWANIA DLA");
  delay(250);
  tft.println("MARCIN MLYNARCZYK");
  delay(250);
  tft.println("2024-2025");
  delay(1000);
}

void drawSelectedCircle(){
  tft.fillCircle(65, 114, 3, ST7735_BLACK);
  tft.fillCircle(145, 114, 3, ST7735_BLACK);
  tft.fillCircle(145, 50, 3, ST7735_BLACK);
  switch(bpc%3){
    case 0:
      tft.fillCircle(145, 50, 3, ST7735_GREEN);
      break;
    case 1:
      tft.fillCircle(145, 114, 3, ST7735_YELLOW);
      break;
    case 2:
      tft.fillCircle(65, 114, 3, ST7735_BLUE);
      break;
  }
}

void updateEncoder() {
  switch(bpc%3)
  {
    case 0:
      if(digitalRead(ENC_A)){
        if(digitalRead(ENC_B)){
          if(T_min < 99.8){
            T_min += 0.1;
          }
        }
        else{
          if(T_min > -9.9)
          T_min -= 0.1;
        }
      T_max = T_min + hysteresis;
      }
      break;
    case 1:
    if(digitalRead(ENC_A)){
        if(digitalRead(ENC_B)){
          if(hysteresis <= 9.9){
            hysteresis += 0.1;
          }
        }
        else if(hysteresis > 0.1){
          hysteresis -= 0.1;
        }
      T_max = T_min + hysteresis;
      }
      break;
    case 2:
      if(digitalRead(ENC_A)){
        if(digitalRead(ENC_B)){
          language++;
        }
        else{
          language--;
        }
        refreshGUI = true;
      }
      break;
  }
}

void handleEncoderButton() {
  if (digitalRead(ENC_SW)==0) {
    bpc++;
  }
  drawSelectedCircle();
}