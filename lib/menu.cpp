#include <menu.h>
#include <openGLCD.h>

Menu::Menu(MenuItem* items, int size) {
    this->_items = items;
    this->_size = size;

    Serial.println("Menu created");
    Serial.print(_size);
    Serial.println(" items:");
    for (int i = 0; i < _size; i++) {
        Serial.print("  ");
        Serial.println(_items[i].getName());
    }
    this->_selected = 0;
}

Menu::Menu() {
}

void Menu::select() {
    _items[_selected].select();
}

void Menu::up() {
    _selected--;
    if (_selected < 0) {
        _selected = _size - 1;
    }
}

void Menu::down() {
    _selected++;
    if (_selected >= _size) {
        _selected = 0;
    }
}

void Menu::left() {
    _items[_selected].left();
}

void Menu::right() {
    _items[_selected].right();
}

void Menu::draw() {
    for (int i = 0; i < _size; i++) {
        GLCD.CursorTo(0, i);
        if (i == _selected) {
            GLCD.print(">");
        } else {
            GLCD.print(" ");
        }
        GLCD.print(_items[i].getDisplayString());
    }
}

int Menu::get_size() {
    return _size;
}

MenuItem* Menu::get_items() {
    return _items;
}