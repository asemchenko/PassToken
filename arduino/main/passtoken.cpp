#include <Keyboard.h>
#include <EEPROM.h>

#include "passtoken.h"


PassToken::PassToken(UI &ui) : ui(ui)
{
    if (id != DEVICE_ID)
    {
        reset();
    }
}


void PassToken::login()
{
    if (locked())
        unlock();

    if (login_entries.size() == 0)
    {
        ui.show_message("Oops!", "Password DB is empty");
        return;
    }

    char **titles = new char*[login_entries.size() + 1];
    for (int i = 0; i < login_entries.size(); ++i)
    {
        auto entry = (LoginEntry)login_entries[i];
        titles[i] = new char[11];
        strcpy(titles[i], entry.title);
    }
    titles[login_entries.size()] = "<- cancel";

    int s = ui.show_menu(titles, login_entries.size() + 1);

    for (int i = 0; i < login_entries.size(); ++i)
    {
        delete titles[i];
    }
    delete titles;

    if (s == login_entries.size())
    {
        return;
    }

    auto entry = (LoginEntry)login_entries[s];
    Keyboard.begin();
    Keyboard.print(entry.password);
    Keyboard.end();
}


void PassToken::sync_db()
{
    if (locked())
        unlock();

    ui.show_message("Syncing DB", "Press OK\nto disconnect");

    while (digitalRead(8) == HIGH)
    {
        if (Serial.available() == 0)
        {
            delay(50);
            continue;
        }

        char request[64];

        int n = Serial.readBytesUntil('\n', request, 64);
        request[n] = '\0';

        if (strncmp("GET", request, 3) == 0)
        {
            get();
        }
        else if (strncmp("ADD", request, 3) == 0)
        {
            if (login_entries.size() >= 10)
            {
                Serial.println("ERROR: DB Is Full");
                continue;
            }

            char * title = request + 4;
            char * separator = strchr(title, ':');
            
            if (separator == nullptr)
            {
                Serial.println("ERROR: Bad Request");
                continue;                
            }
            
            char * password = separator + 1;
            
            *separator = '\0';

            add(title, password);
        }
        else if (strncmp("DEL", request, 3) == 0)
        {
            String str_index(request + 4);
            auto index = str_index.toInt();

            del(index);
        }
        else if (strncmp("DIS", request, 3) == 0)
        {
            break;
        }
        else
        {
            Serial.println("ERROR: Bad Request");
        }
    }
}


bool PassToken::locked()
{
    return m_locked;
}


void PassToken::unlock()
{
    while (attempts > 0)
    {
        auto entered_pin = ui.prompt_number("Master PIN:");
        attempts = attempts - 1;

        if (entered_pin == master_pin)
        {
            m_locked = false;
            attempts = 5;
            break;
        }
    }

    if (m_locked)
    {
        reset();
        m_locked = false;
        ui.show_message("Warning!", "All data was erased.");
    }
}


void PassToken::reset()
{
    for (int i = 0; i < EEPROM.length(); ++i)
    {
        EEPROM.update(i, 255);
    }

    id             = DEVICE_ID;
    master_pin     = 0;
    attempts       = 5;
    login_entries.erase();
}


void PassToken::change_pin()
{
    if (locked())
        unlock();

    auto new_pin1 = ui.prompt_number("New PIN:");
    auto new_pin2 = ui.prompt_number("New PIN:");

    if (new_pin1 == new_pin2)
    {
        master_pin = new_pin1;
        ui.show_message("Success!", "PIN was updated");
    }
    else
    {
        ui.show_message("Oops!", "PIN's dont match");
    }
}


void PassToken::get()
{
    Serial.println("OK");
    Serial.println(login_entries.size());

    for (int i = 0; i < login_entries.size(); ++i)
    {
        LoginEntry entry = login_entries[i];

        Serial.print(entry.title);
        Serial.print(":");
        Serial.println(entry.password);
    }

    Serial.println("DONE");
}


void PassToken::add(const char *title, const char *password)
{
    if (strlen(title) > 10 || strlen(password) > 31)
    {
        Serial.println("ERROR: String Is Too Long");
        return;
    }

    LoginEntry entry;
    strcpy(entry.title, title);
    strcpy(entry.password, password);

    login_entries.append(entry);

    Serial.println("OK");
}


void PassToken::del(size_t index)
{
    if (index < 0 || index >= login_entries.size())
    {
        Serial.println("ERROR: Index Out Of Range");
    }
    else
    {
        login_entries.remove(index);
        Serial.println("OK");
    }
}
