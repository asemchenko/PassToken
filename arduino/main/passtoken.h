#ifndef PASSTOKEN_H
#define PASSTOKEN_H


#include "ui.h"
#include "persistent.h"


#define DEVICE_ID 0x5450


class PassToken
{
    public:
        PassToken(UI &ui);

        bool locked();
        void unlock();

        void login();
        void sync_db();
        void change_pin();
        void reset();

        void get();
        void add(const char *title, const char *password);
        void del(size_t index);

    private:
        struct LoginEntry
        {
            char title[11];
            char password[32];
        };

    private:
        UI &ui;

        bool m_locked = true;

        PersistentScalar<int>           id             = PersistentScalar<int>(0x00);
        PersistentScalar<unsigned long> master_pin     = PersistentScalar<unsigned long>(0x02);
        PersistentScalar<int>           attempts       = PersistentScalar<int>(0x06);
        PersistentScalar<int>           entries_number = PersistentScalar<int>(0x08);
        PersistentArray<LoginEntry>     login_entries  = PersistentArray<LoginEntry>(0x10);
};


#endif // PASSTOKEN_H
