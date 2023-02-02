#ifndef LOOP_H
#define LOOP_H

#include <Arduino.h>
#include <menu.h>

class Loop
{
public:
    static void update(Menu *menu);
    static void draw(Menu *menu);
};

#endif