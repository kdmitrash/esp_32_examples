/*
   Гирлянда на ESP8266 v2.01
   Страница проекта: https://arduino-tex.ru/news/29/elochnaya-girlyanda-na-esp8266-esp32-upravlenie-s-prilozheniya.html
   Сайт разработчика https://portal-pk.ru/
   Проекты на Arduino https://portal-pk.ru/page-17/proekty-na-arduino.html
   Проекты на ESP https://portal-pk.ru/page-18/proekty-na-nodemcu-esp8266-esp-01.html
*/
/*
    Набо эффектов 
*/ 
int x = 1;
// Initialize global variables for sequences
int thisdelay = 150;                                           // A delay value for the sequence(s)
int thishue = 50;
int thissat = 255;
int thisdir = 20;
bool huerot = 70; 

// Does the hue rotate? 1 = yes
// Routine specific variables
uint8_t numdots = 8;                                          // Number of dots in use.
uint8_t faderate = 1;                                         // How long should the trails be. Very low value = longer trails.
uint8_t hueinc = 6;                                          // Incremental change in hue between each dot.
//uint8_t thishue = 20;                                          // Starting hue.
uint8_t curhue = 10;                                           // The current hue
//uint8_t thissat = 255;                                        // Saturation of the colour.
uint8_t thisbright = 255;                                     // How bright should the LED/display be.
uint8_t basebeat = 1;   // Higher = faster movement.

int wave1=5;                                            // Current phase is calculated.
int wave2=0;
int wave3=0;

uint8_t inc1 = 2;                                       // Phase shift. Keep it low, as this is the speed at which the waves move.
uint8_t inc2 = -11;
uint8_t inc3 = -2;

uint8_t lvl1 = 180;                                      // Any result below this value is displayed as 0.
uint8_t lvl2 = 80;
uint8_t lvl3 = 80;

uint8_t mul1 = 2;                                      // Frequency, thus the distance between waves
uint8_t mul2 = 5;
uint8_t mul3 = 22;

// 1 //
void confetti2() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

// 2 //
void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow2();
  addGlitter(80);
  //addGlitter(10);
}
void rainbow2() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 2);
}
void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
    //leds[ random16(NUM_LEDS) ] += 0xFFFFFF;
  }
}
// end 2 //

// 3 //
void cyclon() { 
  static uint8_t hue = 0;
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    //leds[i] = CHSV(hue++, 255, 255);
    leds[i] = 0xAAAAAA;
    // Show the leds
    FastLED.show(); 
    //leds[i] = CHSV(hue++, 255, 255); FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    leds[i] = CRGB::Black;
    leds[i] = CHSV(hue++, 255, 255); FastLED.show();
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red 
    //leds[i] = 0xAAAAAA;
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(30);
  }
}
void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }
// end 3 //

// 4 //
void juggle2() { 
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  //fadeToBlackBy( leds, NUM_LEDS, 5);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

// 5 //
void sinelon2() 
{
  // a colored dot sweeping back and forth, with fading trails
  //fadeToBlackBy( leds, NUM_LEDS, 20);
  fadeToBlackBy( leds, NUM_LEDS, 2);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

// 6 //
void confetti()  
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 5);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
  delay(30);
}

// 7 //
void sinelon() 
{
  // a colored dot sweeping back and forth, with fading trails
  //fadeToBlackBy( leds, NUM_LEDS, 20);
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

// 8 //
void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

// 9 //
void juggle() { 
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 3);
  //fadeToBlackBy( leds, NUM_LEDS, 5);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 50;
  }
}

// 10 //
void sinelon3() 
{
  // a colored dot sweeping back and forth, with fading trails
  //fadeToBlackBy( leds, NUM_LEDS, 20);
  fadeToBlackBy( leds, NUM_LEDS, 5);
  int pos = beatsin16( 3, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

// 11 //
void bpm() 
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
//12 //
void cylonfill(){
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS-x; i++) {
    // Set the i'th led to red 
    leds[i] = CRGB::Blue;
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    leds[i] = CRGB::Green;
    // Wait a little bit before we loop around and do it again
    delay(16);
   }
        
        leds[NUM_LEDS -x] = CRGB::Orange;
        FastLED.show();
        x++;
        if (x ==NUM_LEDS){
          x =1;
        }
        Serial.println(x);
  // Now go in the other direction.  
  for(int i = NUM_LEDS-x; i >= 2; i--) {
    // Set the i'th led to red 
    leds[i] = CRGB::Purple;
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    leds[i] = CRGB::Black;
    // Wait a little bit before we loop around and do it again
  //  delay(1);
  }
}

//13//
void juggle3() {                                               // Several colored dots, weaving in and out of sync with each other
  curhue = thishue;                                          // Reset the hue values.
  fadeToBlackBy(leds, NUM_LEDS, faderate);
  for( int i = 0; i < numdots; i++) {
    leds[beatsin16(basebeat+i+numdots,0,NUM_LEDS)] += CHSV(curhue, thissat, thisbright);   //beat16 is a FastLED 3.1 function
    curhue += hueinc;
  }
} // juggle()

//14//
void twinkle() {
  int i = random(NUM_LEDS);                                           // A random number. Higher number => fewer twinkles. Use random16() for values >255.
  if (i < NUM_LEDS) leds[i] = CHSV(random(255), random(255), random(255));              // Only the lowest probability twinkles will do. You could even randomize the hue/saturation. .
  for (int j = 0; j < NUM_LEDS; j++) leds[j].fadeToBlackBy(8);
  
  LEDS.show();                                                // Standard FastLED display
  //show_at_max_brightness_for_power();                          // Power managed FastLED display

  //delay(10);                                            // Standard delay
  LEDS.delay(50);                                     // FastLED delay 
  //delay_at_max_brightness_for_power(thisdelay);              // Power managed FastLED delay
} // twinkle()

//15//
void three_sin() {
  wave1 += inc1;
  wave2 += inc2;
  wave3 += inc3;
  for (int k=0; k<NUM_LEDS; k++) {
    leds[k].r = qsub8(sin8(mul1*k + wave1/128), lvl1);         // Another fixed frequency, variable phase sine wave with lowered level
    leds[k].g = qsub8(sin8(mul2*k + wave2/128), lvl2);         // A fixed frequency, variable phase sine wave with lowered level
    leds[k].b = qsub8(sin8(mul3*k + wave3/128), lvl3);         // A fixed frequency, variable phase sine wave with lowered level
  }
} // three_sin()

//16//
void matrix() {                                               // One line matrix

  if (huerot) thishue=thishue+5;

  if (random16(90) > 80) {
    if (thisdir == 0) leds[0] = CHSV(thishue, thissat, 255); else leds[NUM_LEDS-1] = CHSV(thishue, thissat, 255);
  }
  else {leds[0] = CHSV(thishue, thissat, 0);}

  if (thisdir == 0) {
    for (int i = NUM_LEDS-1; i >0 ; i-- ) leds[i] = leds[i-1];
  } else {
    for (int i = 0; i < NUM_LEDS ; i++ ) leds[i] = leds[i+1];
  }
} // matrix()

/*
   Код упровления светодиодами 
*/ 
void Led() {  // Авто режим и переключение кнопкой

  currentButten = debvance (lastButten); // Передаем функции дребезга значение по умолчанию LOW
  if (lastButten == LOW && currentButten == HIGH ) // Проверяем отпускали мы кнопку или нет
  {
    prestroMillis = millis();
    interval = 1000;
  }
  if (currentButten == HIGH) // Проверяем отпускали мы кнопку или нет
  {
    unsigned long curstroMillis = millis();  // устанавливаем время в сейчас
    if ((curstroMillis - prestroMillis) > interval) // проверяем интервал
    {
      if ( flag == 1)
      {
        j=j+5;
        if (j > 250)
          j = 1;
        FastLED.setBrightness(j);
        prestroMillis = curstroMillis;
      }
      else
      {
        flag = 1;
        interval = 100;
      }
    }
  }

  if (lastButten == HIGH && currentButten == LOW) // Проверяем отпускали мы кнопку или нет
  {
    if (flag == 1)
      flag = 0;
    else
    {
      nextPattern();  // change patterns periodically
      //Serial.println(modes[i]);
      auto_rejim = false;
    }
  }
  lastButten =  currentButten;  // Переприсваеваем прошлое состояние кнопки

}


boolean debvance (boolean last) //убираем дребизг
{
  boolean current = digitalRead (button_rejim); // считываем данные с кнопки
  if (last != current) // Если текущее состояни еотличететься от предыдущего
  {
    delay (5);   // Ждем 5 милисек.
    current = digitalRead (button_rejim); // Присваеваем текущее состояние кнопки
    return current;
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0])) // подчет эффектов

void nextPattern() // переключение на следующий эффект
{
  if (gCurrentPatternNumber  == (ARRAY_SIZE( gPatterns)-1))
    gCurrentPatternNumber = 0;
  else
    gCurrentPatternNumber = (gCurrentPatternNumber + 1);
  Serial.println(gCurrentPatternNumber);
  HTTP.send(200, "text/plain", Effect(gCurrentPatternNumber));
}

void prevPattern() // переключение на предыдущий эффект
{
  if (gCurrentPatternNumber  == 0)
    gCurrentPatternNumber = ARRAY_SIZE( gPatterns)-1;
  else
    gCurrentPatternNumber = (gCurrentPatternNumber - 1);
  Serial.println(gCurrentPatternNumber);
  HTTP.send(200, "text/plain", Effect(gCurrentPatternNumber));
}
