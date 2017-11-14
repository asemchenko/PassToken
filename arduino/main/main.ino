#include "passtoken.h"


Adafruit_SSD1306 display;
UI ui;
PassToken token(ui);

void setup() {
    Serial.begin(9600);

    ui.init_display();
    ui.show_message("PassToken", "Password Manager", 1000);
}


const char *menu[] = {
    "Login",
    "Sync DB",
    "Full Reset",
    "Change PIN",
    "Turn UI",
};


void loop() {
    static size_t selected = 0;

    selected = ui.show_menu(menu, 5, selected);
    
    switch (selected)
    {
        case 0:
            token.login();
            break;

        case 1:
            token.sync_db();
            break;

        case 2:
            token.reset();
            ui.show_message("Ok", "Token was reseted");
            break;

        case 3:
            token.change_pin();
            break;

        case 4:
            ui.turn_over();
            break;
    }
}
