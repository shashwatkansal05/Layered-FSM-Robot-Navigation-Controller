#include "event.h"

typedef enum { MODE_AUTO, MODE_MANUAL, MODE_ESCAPE } Mode;
Mode mode = MODE_AUTO;

int escape_timer = 0;

void mode_fsm(Event e)
{
    switch(mode)
    {
        case MODE_AUTO:
            if(e == EVENT_USER_MANUAL)
                mode = MODE_MANUAL;
            break;

        case MODE_MANUAL:
            if(e == EVENT_USER_AUTO)
                mode = MODE_AUTO;
            break;

        case MODE_ESCAPE:
            if(e == EVENT_TIMEOUT) {
                escape_timer--;
                if(escape_timer <= 0)
                    mode = MODE_AUTO;
            }
            break;
    }
}

void enter_escape()
{
    mode = MODE_ESCAPE;
    escape_timer = 10;
}

Mode get_mode() { return mode; }
