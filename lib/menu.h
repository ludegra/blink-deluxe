#ifndef MENU_H
#define MENU_H

#include <menu_item.h>

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