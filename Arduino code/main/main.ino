#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define PIN_OK 8
#define BOUNCE_DELAY_TIME 150
#define PIN_CODE_ATTEMPT 5
#define PIN_LENGHT 6

Adafruit_SSD1306 display(OLED_RESET);
byte PIN_PLUS = 10, PIN_MINUS = 9, TOKEN_POSITION = 1;
void printText(String text) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(text);
  display.display();
}
byte waitButtonClick() {
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
byte setMode() {
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
  return mode;
}
String inputPinCode() {
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
void setup() {
  Serial.begin(9600); // only for debugging!!!

  pinMode(PIN_PLUS, INPUT);
  pinMode(PIN_MINUS, INPUT);
  pinMode(PIN_OK, INPUT);
  digitalWrite(PIN_PLUS, HIGH);
  digitalWrite(PIN_MINUS, HIGH);
  digitalWrite(PIN_OK, HIGH);
  // choosing position of token
  while ((PIN_MINUS = waitButtonClick(), PIN_MINUS) == PIN_OK);
  PIN_PLUS = PIN_MINUS == 10 ? 9 : 10;
  TOKEN_POSITION = PIN_MINUS == 9 ? 1 : 0;
  delay(BOUNCE_DELAY_TIME);
  // display initialization
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, true, TOKEN_POSITION);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  byte mode = setMode();
  if (mode == PIN_PLUS) { // if synchronization mode choosed
    // code for synchronization
  }
  else { // if inputing secret mode choosed
    // inputing PIN
    bool correctPinCode = false;
    for (byte i = PIN_CODE_ATTEMPT; i > 0; i--) {
      String pinCode = inputPinCode();
      // verifying pin-code
      if (/* pinCode == correctPincode*/ false) {
        correctPinCode = true;
        break;
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
      else{
        break;
      }
    }
    if (!correctPinCode) {
      // removing all secrets
      Serial.println("All secrets removed");
    }
  }
}
void loop() {
}
