#ifndef UI_H
#define UI_H


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "persistent.h"


extern Adafruit_SSD1306 display;


/**
 * @brief      User interface with display and three buttons (up, down & ok).
 */
class UI
{
public:
    UI();
    
    void init_display();
    
    size_t show_menu(const char **entries, size_t number, size_t selected = 0);

    unsigned long  prompt_number(const char *prompt);

    void show_message(const char *title, const char *detailed = nullptr, int duration = 2000);

    void turn_over();

private:
    enum class Button { Ok, Up, Down };
    PersistentScalar<int> right_oriented = PersistentScalar<int>(0x0a);

    Button wait_click();
};

#endif // UI_H
