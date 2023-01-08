#ifndef MENU_ITEM_H
#define MENU_ITEM_H
#include <Arduino.h>

class MenuItem {
private:
    String _name;
    void (*_select_callback)(void);

public:
    MenuItem(String name, void (*select_callback)(void));
    String getName();
    void select();

    virtual int getValue();
    virtual String getDisplayString();
    virtual void left();
    virtual void right();
    virtual boolean has_value();
};

class MenuVariable : public MenuItem {
private:
    int _value;
    int _min;
    int _max;
    int _step;
public:
    MenuVariable(String name, int default_value, int min, int max, int step);
    int getValue();
    String getDisplayString();
    void left();
    void right();
    boolean has_value();
};

#endif