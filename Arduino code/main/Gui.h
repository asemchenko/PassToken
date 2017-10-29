#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;
enum WorkingMode {INPUTING_SECRET,SYNCHRONIZATION};
#define PIN_OK 8
#define BOUNCE_DELAY_TIME 150
#define PIN_CODE_ATTEMPT 5
#define PIN_LENGHT 6
class Gui{
	byte PIN_PLUS;
	byte PIN_MINUS;
	byte TOKEN_POSITION;
	public:
		Gui();
		byte waitButtonClick();
		WorkingMode requestMode();
		String inputPinCode();
		void chooseTokenPosition();
		void initDisplay();
		bool checkPinCode(String);
};