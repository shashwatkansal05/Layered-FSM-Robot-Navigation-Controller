#include <stdio.h>
#include <conio.h>
#include "event.h"
#include "action.h"

/* world */
void world_init();
void draw();
void sense();
void apply(Action a);
void tick();

/* fsm */
void mode_fsm(Event e);
Action motion_fsm(Event e);

/* queue */
void push_event(Event e);
Event pop_event();

int main()
{
    world_init();

    printf("Controls:\n");
    printf("m -> manual mode\n");
    printf("a -> auto mode\n");
    printf("o -> force obstacle\n");
    printf("Ctrl+C to exit\n");

    while(1)
    {
        /* environment */
        sense();
        tick();

        /* user control */
        if(kbhit())
        {
            char c = getch();

            if(c=='m') push_event(EVENT_USER_MANUAL);
            else if(c=='a') push_event(EVENT_USER_AUTO);
            else if(c=='o') push_event(EVENT_OBSTACLE);
        }

        /* process all events */
        Event e;
        while((e = pop_event()) != EVENT_NONE)
        {
            mode_fsm(e);
            Action a = motion_fsm(e);
            apply(a);
        }

        draw();
    }
}
