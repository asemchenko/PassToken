#include "Gui.h"
Gui::Gui(){
	PIN_PLUS = 10;
	PIN_MINUS = 9;
	TOKEN_POSITION = 1;
	pinMode(PIN_PLUS, INPUT);
	pinMode(PIN_MINUS, INPUT);
	pinMode(PIN_OK, INPUT);
	digitalWrite(PIN_PLUS, HIGH);
	digitalWrite(PIN_MINUS, HIGH);
	digitalWrite(PIN_OK, HIGH);
}
byte Gui::waitButtonClick() {
  // waiting for button click and returning pin number
  while (1) {
	switch (PINB & 0x70) {
	  case 0x30:
		return 10;
	  case 0x50:
		return 9;
	  case 0x60:
		return 8;
	}
  }
}
WorkingMode Gui::requestMode() {
  // choosing token mode: inputing password or synchronization
  display.clearDisplay();
  display.setCursor(0, 13);
  display.println("Mode");
  display.setCursor(35, 0);
  display.println("Synchronization");
  display.setCursor(35, 23);
  display.println("Secret inputing");
  display.display();
  byte mode;
  while ((mode = waitButtonClick(), mode) == PIN_OK);
  delay(BOUNCE_DELAY_TIME);
  return mode==PIN_PLUS?SYNCHRONIZATION:INPUTING_SECRET;
}
String Gui::inputPinCode() {
  char inputedPin[PIN_LENGHT + 1] = {'\0'};
  memset(inputedPin + 1, '*', PIN_LENGHT - 1);
  inputedPin[0] = '0';
  char* currentDigitPtr = inputedPin;
  while (currentDigitPtr != inputedPin + PIN_LENGHT) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(22, 0);
    display.println("Input PIN-code");
    display.setTextSize(2);
    display.setCursor(22, 15);
    display.println(inputedPin);
    display.display();
    byte pressedButtonPin = waitButtonClick();
    if (pressedButtonPin == PIN_PLUS) {
      (*currentDigitPtr) == '9' ? (*currentDigitPtr) = '0' : (*currentDigitPtr)++;
    }
    else if (pressedButtonPin == PIN_MINUS) {
      (*currentDigitPtr) == '0' ? (*currentDigitPtr) = '9' : (*currentDigitPtr)--;
    }
    else { // if pressed ok
      ++currentDigitPtr;
      if (currentDigitPtr == inputedPin + PIN_LENGHT) {
        break;
      }
      (*currentDigitPtr) = '0';
    }
    delay(BOUNCE_DELAY_TIME);
  }
  return String(inputedPin);
}
void Gui::chooseTokenPosition(){
	// choosing position of token
	while ((PIN_MINUS = waitButtonClick(), PIN_MINUS) == PIN_OK);
	PIN_PLUS = PIN_MINUS == 10 ? 9 : 10;
	TOKEN_POSITION = PIN_MINUS == 9 ? 1 : 0;
	delay(BOUNCE_DELAY_TIME);
}
void Gui::initDisplay(){
	// display initialization
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C, true, TOKEN_POSITION);
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(1);
}
bool Gui::checkPinCode(String correctPinCode){
    for (byte i = PIN_CODE_ATTEMPT; i > 0; i--) {
      // verifying pin-code
      if (inputPinCode() == correctPinCode) {
        return true;
      }
      if (i != 1) { // if attempts doesn't left
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(20, 0);
        display.println("Wrong pin-code");
        display.setTextSize(2);
        display.setCursor(0, 15);
        display.println(String(i - 1) + String(" attempts"));
        display.display();
        delay(1500);
      }
    }
	return false;
}