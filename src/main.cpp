#include <Arduino.h>
#include <Bounce2.h>

// Define pins
#define BTN 27
#define RED 26
#define YELLOW 25
#define GREEN 33
#define LDR 32

#define MIN_LDR 0
#define MAX_LDR 4095

int bits[3] = {0, 0, 0};
int pins[3] = {RED, YELLOW, GREEN};
Bounce debouncer = Bounce();

void add1tobit(){
  for(int i = 2; i >=0; i--)
  {
    if (bits[i] == 0)
    {
      bits[i] = 1;
      break;
    }
    bits[i] = 0;
  }

}

void setup() {
  Serial.begin(115200);
  ledcSetup(1, 5000, 8); // Main channel
  ledcSetup(0, 5000, 8); // Voided channel
  debouncer.attach(BTN, INPUT_PULLUP);
  debouncer.interval(25);
}

void loop() {
  debouncer.update();
  long pwm = map(analogRead(LDR), MIN_LDR, MAX_LDR, 0, 255);
  // Display LED
  ledcWrite(1, pwm);
  if (debouncer.fell()) {
    add1tobit();
    for (int i = 0; i < 3; i++) {
      ledcAttachPin(pins[i], bits[i]);
    }
  }
  delay(100);
}
