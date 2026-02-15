#include "event.h"
#include "action.h"

/* external functions from mode_fsm */
extern int get_mode();
extern void enter_escape();

static int fail_count = 0;
#define THRESHOLD 3

Action motion_fsm(Event e)
{
    int mode = get_mode();

    /* ESCAPE mode: keep turning */
    if(mode == 2)   // MODE_ESCAPE
        return ACT_TURN_RIGHT;

    /* MANUAL mode: ignore automatic events */
    if(mode == 1)   // MODE_MANUAL
        return ACT_NONE;

    /* AUTO mode behaviour */

    if(e == EVENT_OBSTACLE)
    {
        fail_count++;

        if(fail_count > THRESHOLD) {
            enter_escape();
            fail_count = 0;
        }

        return ACT_TURN_RIGHT;
    }

    if(e == EVENT_TIMEOUT)
        return ACT_FORWARD;

    return ACT_NONE;
}
