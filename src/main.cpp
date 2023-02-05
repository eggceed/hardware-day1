#include <Arduino.h>

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
  ledcSetup(0, 5000, 8); // Main channel
  ledcSetup(1, 5000, 8); // Voided channel
  ledcAttachPin(RED, 0);
  ledcAttachPin(YELLOW, 0);
  ledcAttachPin(GREEN, 0);
}

void loop() {
  long pwm = map(analogRead(32), 0, 4095, 0, 255);
  // Display LED
  ledcWrite(0, pwm);
  for (int i = 0; i < 3; i++) {
    if (!bits[i]) continue; 
  }
  delay(100);
}
