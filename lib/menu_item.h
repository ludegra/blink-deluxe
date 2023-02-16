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

    virtual void select();
    virtual String getType();
    virtual int getValue();
    virtual String getDisplayString();
    virtual void left();
    virtual void right();
    virtual boolean has_value();
};

class MenuVariable : public MenuItem {
private:
    long _value;
    long _min;
    long _max;
    long _step;
    String _suffix;
public:
    MenuVariable(String name, String suffix, long default_value, long min, long max, long step);

    String getType();
    int getValue();
    String getDisplayString();
    void left();
    void right();
    boolean has_value();
};

class ReturnButton : public MenuItem {
private:
    bool *_exit_variable;
public:
    ReturnButton(String name, bool *exit_variable);

    void select();
    String getType();
    String getDisplayString();
};

class Runner : public MenuItem {
private:
    MenuVariable* _on_time;
    MenuVariable* _off_time;

public:
    Runner(String name, MenuVariable* on_time, MenuVariable* off_time);

    void select();
    String getType();
    String getDisplayString();
    boolean has_value();
};

#endif