#include <menu_item.h>
#include <menu.h>
#include <loop.h>

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
    Serial.println("Menu variable left function");

    if (_value <= _min) {
        return;
    }

    _value -= _step;
}

void MenuVariable::right() {
    Serial.println("Menu variable right function");

    if (_value >= _max) {
        return;
    }

    _value += _step;
}

boolean MenuVariable::has_value() {
    return true;
}

// ReturnButton

ReturnButton::ReturnButton(String name, bool *exit_variable) : MenuItem(name, NULL) {
    this->_exit_variable = exit_variable;
}

String ReturnButton::getType() {
    return "ReturnButton";
}

String ReturnButton::getDisplayString() {
    return getName();
}

void ReturnButton::select() {
    *_exit_variable = true;
}

// Runner

Runner::Runner(String name, MenuVariable* on_time, MenuVariable* off_time) : MenuItem(name, NULL) {
    this->_on_time = on_time;
    this->_off_time = off_time;
}

String Runner::getType() {
    return "Runner";
}

String Runner::getDisplayString() {
    return "Run";
}

boolean Runner::has_value() {
    return false;
}

void Runner::select() {
    bool should_exit = false;
    bool light_on = false;
    unsigned long last_change = 0;

    MenuItem* items[] = { _on_time, _off_time, new ReturnButton("Return", &should_exit) };
    Menu menu(items, 3);

    while (!should_exit) {
        if (light_on && millis() - last_change >= _on_time->getValue()) {
            light_on = false;
            last_change = millis();
            digitalWrite(A5, LOW);
        } else if (!light_on && millis() - last_change >= _off_time->getValue()) {
            light_on = true;
            last_change = millis();
            digitalWrite(A5, HIGH);
        }


        Loop::update(&menu);
        Loop::draw(&menu);
    }


}