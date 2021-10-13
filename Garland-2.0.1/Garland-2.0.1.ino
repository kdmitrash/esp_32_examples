/*
   Гирлянда на ESP8266 v2.01
   Страница проекта: https://arduino-tex.ru/news/29/elochnaya-girlyanda-na-esp8266-esp32-upravlenie-s-prilozheniya.html
   Сайт разработчика https://portal-pk.ru/
   Проекты на Arduino https://portal-pk.ru/page-17/proekty-na-arduino.html
   Проекты на ESP https://portal-pk.ru/page-18/proekty-na-nodemcu-esp8266-esp-01.html
*/
#if defined(ESP8266)
#include <ESP8266WiFi.h>        //Содержится в пакете
#include <ESP8266WebServer.h>   //Содержится в пакете
#endif
#if defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#endif

/* для Led */
#include "FastLED.h"
FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
/* Переменные */
// можно менять //
#ifdef ESP8266
#define DATA_PIN    6     // пин для вывода на гирлянду
byte button_rejim = D2;  // пин подключения кнопки
#else
#define DATA_PIN    19   // пин для вывода на гирлянду
byte button_rejim = 21;  // пин подключения кнопки
#endif

#define LED_TYPE WS2812B        // What kind of strip are you using (APA102, WS2801 or WS2812B)?
#define COLOR_ORDER GRB         // It's GRB for WS2812B
#define NUM_LEDS    270          // кол-во светодиодов в гирлянде 33 
#define NUM_LEDS_STAR    15      // + 5 звезда
CRGB leds[NUM_LEDS + NUM_LEDS_STAR];

#define TIMER_MS 60      // время длительности одного эффекта 
                          //в сек. для авто режима

/* настройка wi-fi */
IPAddress apIP(192, 168, 4, 1);
// Web интерфейс для устройства
#ifdef ESP8266
// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
#else
// Web интерфейс для устройства
WebServer HTTP(80);
#endif
// Определяем переменные wifi
String _ssid     = "Wi-Fi"; // Для хранения SSID
String _password = "12345678"; // Для хранения пароля сети
String _ssidAP = "ATGarland";   // SSID AP точки доступа
String _passwordAP = "012345678"; // пароль точки доступа

String Effect(int n)  // Название эффектов выводиться в приложении
{
  char* effects[] = {
    "конфетти 2","Радуга с блестками","жонглирование 2","синелон 2",
    "конфетти","синелон", "радуга","жонглирование","синелон 3","bpm",
    "полное заполнение", "жонглирование 3", "мерцание","три цвета","матрица"  };

  return effects[n];
}
// массив функций эффектов
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { confetti2, rainbowWithGlitter, juggle2, sinelon2, 
confetti, sinelon, rainbow, juggle, sinelon3, bpm, 
cylonfill,juggle3,twinkle,three_sin,matrix };


// Не менять //
uint8_t gCurrentPatternNumber = 0; // порядковый номер эффекта
uint8_t gHue = 0; // "базовый цвет" используется многими эффектами
uint8_t i = 0; // счётчик индекса в массиве эффектов
uint8_t j = 0; // Счечик яркости
boolean auto_rejim = false; // авто режим выкл.
unsigned long last_change = 0; // предыдущее значениее времени
unsigned long now = 0; //текущее значениее времени
boolean lastButten = LOW;     // предыдущее состояние кнопки
boolean currentButten = LOW;  // текущее состояние кнопки
long prestroMillis = 0;        // время для кнопки, до
int interval = 4000;// Время изменения яркости после выход
byte flag = 0;      // состояние кнопки

void setup() {

  pinMode(button_rejim, INPUT); // настроить пин кнопки

  Serial.begin(115200);
  Serial.println("");

  Serial.println("Start WIFI");
  //Запускаем WIFI
  WIFIinit();
  //Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start WebServer");
  HTTP_init();
  
  //Инициализируем работу со светодиодами. 
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS + NUM_LEDS_STAR).setCorrection(TypicalLEDStrip);
  
  // Источник питания 1A 5v 
   FastLED.setMaxPowerInVoltsAndMilliamps(5,2000); 
   
  // set master brightness control
  FastLED.setBrightness(160);
  
  for (int i = NUM_LEDS; i < (NUM_LEDS + NUM_LEDS_STAR); i++) {
    // Set the i'th led to red
    leds[i] = CRGB::Red;
    // Show the leds
    FastLED.show();
  }
}


void loop() {
  HTTP.handleClient();
  delay(2);
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }

  if (auto_rejim)
  {
    EVERY_N_SECONDS( TIMER_MS ) {
      nextPattern();
    }
  }
  #if defined(ESP8266)
      Led();
  #endif
  
}
