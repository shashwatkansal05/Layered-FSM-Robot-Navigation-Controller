#include "event.h"

#define QSIZE 20

static Event q[QSIZE];
static int head = 0, tail = 0;

void push_event(Event e)
{
    int next = (head + 1) % QSIZE;
    if(next != tail) {
        q[head] = e;
        head = next;
    }
}

Event pop_event()
{
    if(tail == head)
        return EVENT_NONE;

    Event e = q[tail];
    tail = (tail + 1) % QSIZE;
    return e;
}
