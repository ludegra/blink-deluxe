#include <menu_item.h>

// MenuItem
MenuItem::MenuItem(String name, void (*select_callback)(void)) {
    this->_name = name;
    this->_select_callback = select_callback;
}

String MenuItem::getType() {
    return "MenuItem";
}

String MenuItem::getName() {
    return _name;
}

int MenuItem::getValue() {
    return 0;
}

String MenuItem::getDisplayString() {
    return _name;
}

void MenuItem::select() {
    _select_callback();
}

void MenuItem::left() {
}

void MenuItem::right() {
}

boolean MenuItem::has_value() {
    return false;
}

// MenuVariable
MenuVariable::MenuVariable(String name, int default_value, int min, int max, int step) : MenuItem(name, NULL) {
    this->_value = default_value;
    this->_min = min;
    this->_max = max;
    this->_step = step;
}

String MenuVariable::getType() {
    return "MenuVariable";
}

int MenuVariable::getValue() {
    return _value;
}

String MenuVariable::getDisplayString() {
    return getName() + ": " + _value;
}

void MenuVariable::left() {
    if (_value <= _min) {
        return;
    }

    _value -= _step;
}

void MenuVariable::right() {
    if (_value >= _max) {
        return;
    }

    _value += _step;
}

boolean MenuVariable::has_value() {
    return true;
}