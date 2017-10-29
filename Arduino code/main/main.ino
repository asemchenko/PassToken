#include "Gui.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
Gui gui;
void setup() {
  Serial.begin(9600); // only for debugging!!!
  gui.chooseTokenPosition();
  gui.initDisplay();
  if (gui.requestMode() == SYNCHRONIZATION) { // if synchronization mode choosed
    // code for synchronization
  }
  else { // if inputing secret mode choosed
    if (gui.checkPinCode("000000")) {
      // if user input correct pin-code
      Serial.println("Authorization succesed");
    }
    else {
      // if user can't input correct password
      // removing all secrets
      Serial.println("All secrets removed");
    }
  }
}
void loop() {
}
