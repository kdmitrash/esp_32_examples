/*
   Гирлянда на ESP8266 v2.01
   Страница проекта: https://arduino-tex.ru/news/29/elochnaya-girlyanda-na-esp8266-esp32-upravlenie-s-prilozheniya.html
   Сайт разработчика https://portal-pk.ru/
   Проекты на Arduino https://portal-pk.ru/page-17/proekty-na-arduino.html
   Проекты на ESP https://portal-pk.ru/page-18/proekty-na-nodemcu-esp8266-esp-01.html
*/

void HTTP_init(void) {
  HTTP.onNotFound(handleNotFound); // Сообщение если нет страницы. Попробуйте ввести http://192.168.0.101/restar?device=ok&test=1&led=on
  HTTP.on("/led", handle_Led); // Упровляем Led http://192.168.0.101/led?status=auto
  HTTP.on("/light", handle_Light);  /// Яркасть
  HTTP.on("/effect", handle_Effect); /// вывод текущего эффекта
  HTTP.on("/color", handle_Color);  // выбор цвета
  // Запускаем HTTP сервер
  HTTP.begin();

}

// Ответ если страница не найдена
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += HTTP.uri();
  message += "\nMethod: ";
  message += (HTTP.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += HTTP.args();
  message += "\n";
  for (uint8_t i = 0; i < HTTP.args(); i++) {
    message += " " + HTTP.argName(i) + ": " + HTTP.arg(i) + "\n";
  }
  HTTP.send(404, "text/plain", message);
}

// Переключение режимов http://192.168.0.101/led?status={переменная}
void handle_Led() {
  String status = HTTP.arg("status");
  if (status == "next")
  {
    nextPattern();  // change patterns periodically
    //Serial.println(modes[i]);
    auto_rejim = false;
    //HTTP.send(200, "text/plain", Effect(gCurrentPatternNumber));
  }

  if (status == "prev")
  {
    prevPattern();  // change patterns periodically
    auto_rejim = false;
    HTTP.send(200, "text/plain", Effect(gCurrentPatternNumber));
  }

  if (status == "auto")
  {
    auto_rejim = true;
    Serial.println("auto");
    HTTP.send(200, "text/plain", Effect(gCurrentPatternNumber));
  }
}

void handle_Light()
{
  String num = HTTP.arg("num");
  Serial.println(num);
  if (num)
  {
    int intNum = num.toInt();
    if (intNum > 0)
    {
      j = map(intNum, 1, 100, 0, 255);
      FastLED.setBrightness(j);
      HTTP.send(200, "text/plain",  Effect(gCurrentPatternNumber));

    }
    else
      HTTP.send(200, "text/plain", "0");

  }
}

void handle_Color()
{
  String num = HTTP.arg("num");
  Serial.println(num);
  if (num)
  {
    int intNum = num.toInt();
    if (intNum > 0)
    {
      if (intNum == 4)
      {
        for (int i = NUM_LEDS; i < (NUM_LEDS + NUM_LEDS_STAR); i++) {
          // Set the i'th led to red
          leds[i] = CRGB::Red;
          // Show the leds
          FastLED.show();
        }
      }
      if (intNum == 5)
      {
        for (int i = NUM_LEDS; i < (NUM_LEDS + NUM_LEDS_STAR); i++) {
          // Set the i'th led to red
          leds[i] = CRGB::Blue;
          // Show the leds
          FastLED.show();
        }
      }
      if (intNum == 6)
      {
        for (int i = NUM_LEDS; i < (NUM_LEDS + NUM_LEDS_STAR); i++) {
          // Set the i'th led to red
          leds[i] = CRGB::Green;
          // Show the leds
          FastLED.show();
        }
      }
      if (intNum == 7)
      {
        for (int i = NUM_LEDS; i < (NUM_LEDS + NUM_LEDS_STAR); i++) {
          // Set the i'th led to red
          leds[i] = CRGB::Orange;
          // Show the leds
          FastLED.show();
        }
      }
      if (intNum == 8)
      {
        for (int i = NUM_LEDS; i < (NUM_LEDS + NUM_LEDS_STAR); i++) {
          // Set the i'th led to red
          leds[i] = CRGB::Yellow;
          // Show the leds
          FastLED.show();
        }
      }
      if (intNum == 9)
      {
        for (int i = NUM_LEDS; i < (NUM_LEDS + NUM_LEDS_STAR); i++) {
          // Set the i'th led to red
          leds[i] = CRGB::Purple;
          // Show the leds
          FastLED.show();
        }
      }

      HTTP.send(200, "text/plain", Effect(gCurrentPatternNumber));
    }
    else
      HTTP.send(200, "text/plain", "0");
  }
}

void handle_Effect()
{
  String ef = HTTP.arg("ef");
  if (ef)
  {
    int intEf = ef.toInt();
    if (intEf > 0)
    {
      String str = "[" + String(intEf - 1) + "] " ;
      HTTP.send(200, "text/plain", Effect(gCurrentPatternNumber));
    }
  }
}
