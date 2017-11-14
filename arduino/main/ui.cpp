#include "ui.h"


UI::UI()
{
    pinMode( 8, INPUT);
    pinMode( 9, INPUT);
    pinMode(10, INPUT);

    digitalWrite( 8, HIGH);
    digitalWrite( 9, HIGH);
    digitalWrite(10, HIGH);
}


void UI::init_display()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C, true, (bool)right_oriented);
    display.clearDisplay();
    display.setTextColor(WHITE);
}


void UI::show_message(const char *title, const char *detailed = nullptr, int duration = 2000)
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println(title);

    if (detailed != nullptr)
    {
        display.setTextSize(1);
        display.setCursor(0, 16);
        display.println(detailed);
    }

    display.display();

    delay(duration);
}


size_t UI::show_menu(const char **entries, size_t number, size_t selected)
{
    while (true)
    {
        display.clearDisplay();

        display.setTextSize(1);

        // Print previous entry
        size_t prev = (number + selected - 1) % number;
        display.setCursor(0, 0);
        display.print(entries[prev]);

        // Print previous entry
        size_t next = (selected + 1) % number;
        display.setTextSize(1);
        display.setCursor(0, 24);
        display.print(entries[next]);

        // Print current entry;
        display.setTextSize(2);
        display.setCursor(0, 8);
        display.print(entries[selected]);

        display.display();

        switch (wait_click())
        {
            case Button::Up:
                selected = prev;
                break;

            case Button::Down:
                selected = next;
                break;

            case Button::Ok:
                display.clearDisplay();
                return selected;
        }
    }
}


unsigned long UI::prompt_number(const char *prompt)
{
    char input[] = "0*****";
    char curr_digit = 0;
    unsigned long long number = 0;

    while (curr_digit < 6)
    {
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.println(prompt);

        display.setTextSize(2);
        display.setCursor(0, 12);
        display.println(input);

        display.display();

        switch (wait_click())
        {
            case Button::Up:
                input[curr_digit] = '0' + (input[curr_digit] - '0' + 1) % 10;
                break;

            case Button::Down:
                input[curr_digit] = '0' + (10 + input[curr_digit] - '0' - 1) % 10;
                break;

            case Button::Ok:
                number = number * 10 + input[curr_digit] - '0';
                input[curr_digit] = '*';
                curr_digit += 1;
                input[curr_digit] = '0';
                break;
        }
    }

    return number;
}


UI::Button UI::wait_click()
{
    delay(250);

    while (true) {
        if (Serial.available())
        {
            byte buffer[64];
            Serial.readBytes(buffer, 64);
            Serial.println("ERROR: Request Rejected");
        }

        switch (PINB & 0x70)
        {
            case 0x30:
                return right_oriented ? Button::Up : Button::Down;
            case 0x50:
                return right_oriented ? Button::Down : Button::Up;
            case 0x60:
                return Button::Ok;

            default:
                delay(10);
                break;
        }
    }
}


void UI::turn_over()
{
    right_oriented = right_oriented ? 0 : 1;
    init_display();
}
