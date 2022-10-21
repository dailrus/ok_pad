#include <DigiKeyboard.h>
#include <Adafruit_NeoPixel.h>

#define led_pin         2 //Пин к которому подключена лента
#define len             24 //Количество светодиодов
#define max_bright    255 //Яркость светодиодов
#define key_1_pin       0 //Пин первой кнопки
#define key_2_pin       1 //Пин второй кнопки
#define brightness 255 //Яркость

//####################
#define red 0
#define green 1
#define blue 2
//#################### Для массива
int time_now;
int bright[3] = {0, 0, 0};
unsigned long last_time;
bool state_1;
bool state_2;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(len, led_pin, NEO_GRB + NEO_KHZ800);


void setup() {
  DigiKeyboard.delay(2000);
  pinMode(key_1_pin, INPUT);
  pinMode(key_2_pin, INPUT);


  strip.begin();
  strip.show();
  time_now = millis();
}
void blinker() {
  if (millis() - last_time >= 5) {
    if (bright[red] > 0) {
      bright[red] = bright[red] - 1;
    }
    if (bright[green] > 0) {
      bright[green] = bright[green] - 1;
    }
    if (bright[blue] > 0) {
      bright[blue] = bright[blue] - 1;
    }
    last_time = millis();
  }
  if (state_1 == 0) {
    if (bright[red] < brightness - 5) {
      bright[red] = bright[red] + 5;
    }
  }
  if (state_2 == 0) {
    if (bright[blue] < brightness - 5) {
      bright[blue] = bright[blue] + 5;
    }

  }
  for (int i = 0; i < 4; i++) {
    strip.setPixelColor(i, bright[red], bright[green], 0);
  }

  for (int i = 4; i < len; i++) {
    strip.setPixelColor(i, 0, bright[green], bright[blue]);
  }
  strip.show();


}
void keyCheck() {
  state_1 = digitalRead(key_1_pin);
  state_2 = digitalRead(key_2_pin);
  DigiKeyboard.update();

  if (state_2 == 0) {
    DigiKeyboard.sendKeyPress(KEY_X);
  }
  else if (state_1 == 0) {
    DigiKeyboard.sendKeyPress(KEY_Z);
  }
  else if(state_1 == 0 and state_2 == 0){
    DigiKeyboard.sendKeyPress(KEY_X,KEY_Z);
  }
  if (state_1 == 1 and state_2 == 1) {
    DigiKeyboard.sendKeyPress(0, 0);
  }
}
void loop()
{
  keyCheck();
  //blinker();
  delay(2);
}
