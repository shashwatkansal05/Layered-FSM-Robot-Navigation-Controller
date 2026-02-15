#include <stdio.h>
#include <unistd.h>
#include "event.h"
#include "action.h"

/* access current mode from mode_fsm */
extern int get_mode();

/* event queue */
extern void push_event(Event e);

#define H 15
#define W 25

char map[H][W+1];

int rx=2, ry=2, dir=1; // start east

/* ---------- INIT WORLD ---------- */
void world_init()
{
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(i==0||j==0||i==H-1||j==W-1)
                map[i][j]='#';
            else
                map[i][j]=' ';
        }
        map[i][W]='\0';
    }

    // internal obstacle wall
    for(int i=3;i<12;i++)
        map[i][10]='#';
}

/* ---------- DRAW WORLD ---------- */
void draw()
{
    /* move cursor to top ONLY (no full clear → no flicker) */
    printf("\033[H");

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(i==ry && j==rx) printf("R");
            else printf("%c",map[i][j]);
        }
        printf("\n");
    }

    printf("---------------------------\n");

    int mode = get_mode();

    printf("Mode : ");
    if(mode == 0) printf("AUTO   (press a)\n");
    else if(mode == 1) printf("MANUAL (press m)\n");
    else if(mode == 2) printf("ESCAPE (auto recovery)\n");

    printf("Controls: a = auto | m = manual | Ctrl+C = exit\n");
}

/* ---------- SENSOR ---------- */
void sense()
{
    int nx=rx, ny=ry;

    if(dir==0) ny--;
    if(dir==1) nx++;
    if(dir==2) ny++;
    if(dir==3) nx--;

    if(map[ny][nx]=='#')
        push_event(EVENT_OBSTACLE);
}

/* ---------- APPLY ACTION ---------- */
void apply(Action a)
{
    if(a==ACT_TURN_RIGHT){
        dir=(dir+1)%4;
        return;
    }

    if(a==ACT_FORWARD){
        int nx=rx, ny=ry;

        if(dir==0) ny--;
        if(dir==1) nx++;
        if(dir==2) ny++;
        if(dir==3) nx--;

        if(map[ny][nx]!='#'){
            rx=nx;
            ry=ny;
        }
    }
}

/* ---------- TIMER TICK ---------- */
void tick()
{
    usleep(500000);   // slower → readable recording
    push_event(EVENT_TIMEOUT);
}
