#ifndef BLINK_DELUXE
#define BLINK_DELUXE
#include <Arduino.h>

class MenuItem {
private:
    String _name;
    void (*_select_callback)(void);

public:
    MenuItem(String name, void (*select_callback)(void));
    String getName();
    void select();
    void left();
    void right();
};

class Menu {
private:
    MenuItem* _items;
    int _size;
    int _selected;
    
public:
    Menu(MenuItem* items, int size);
    Menu();
    void select();
    void up();
    void down();
    void left();
    void right();
    void draw();
    int get_size();
    MenuItem* get_items();
};

#endif