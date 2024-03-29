#include <loop.h>
#include <menu.h>
#include <openGLCD.h>

// PINS:
// 2 - up
// 3 - down
// 12 - left
// 13 - right
// A7 - select

// Pin declarations
#define UP_PIN 2
#define DOWN_PIN 3
#define LEFT_PIN 12
#define RIGHT_PIN 13
#define SELECT_PIN A7

// Button states
bool up_pressed = false;
bool down_pressed = false;
bool left_pressed = false;
bool right_pressed = false;
bool select_pressed = false;

// Button timestamps (for holding down button)
unsigned long up_timestamp = 0;
unsigned long down_timestamp = 0;
unsigned long left_timestamp = 0;
unsigned long right_timestamp = 0;
unsigned long select_timestamp = 0;

// Button hold time constants (in ms)
const unsigned long hold_delays[] = {500, 500, 250, 250, 250, 250, 125, 125, 125, 125, 75};

// Button hold times (indices for hold_delays)
int up_hold_time = 0;
int down_hold_time = 0;
int left_hold_time = 0;
int right_hold_time = 0;

const int thresholdValue = 1020;
const unsigned long analogDelay = 500;

int analogReadDigital(int analogPin)
{
  int analogValue = analogRead(analogPin);
  if (analogValue < thresholdValue)
  {
    return LOW;
  }
  else
  {
    return HIGH;
  }
}

bool check_button_down(int pin, bool *state, bool allow_hold, unsigned long *timestamp = 0, int *delay_index = 0)
{
  if (digitalRead(pin) == HIGH)
  {
    // Check if button is not already pressed
    if (!*state)
    {
      *state = true;
      *timestamp = millis();
      *delay_index = 0;
      return true;
    }
    // If it is pressed, check if button is being held down
    else if (allow_hold && millis() >= *timestamp + hold_delays[*delay_index])
    {
      *timestamp = millis();
      int hold_time_max = sizeof(hold_delays) / sizeof(hold_delays[0]);
      *delay_index = constrain(*delay_index + 1, 0, hold_time_max - 1);
      return true;
    }
  }
  else
  {
    // If button is not pressed, set state to false
    *state = false;
  }
  return false;
}

bool check_button_down_analog(int pin, bool *state, unsigned long *timestamp)
{
  if (analogReadDigital(pin) == HIGH)
  {
    // Check if button is not already pressed
    if (!*state)
    {
      *state = true;
      *timestamp = millis();
      return true;
    }
  }
  else if (millis() >= *timestamp + analogDelay)
  {
    // If button is not pressed, set state to false
    *state = false;
  }
  return false;
}

void Loop::update(Menu *menu)
{

  // Check buttons
  if (check_button_down(DOWN_PIN, &down_pressed, true, &down_timestamp, &down_hold_time))
  {
    Serial.println("Down pressed");
    menu->down();
  }
  // For some reason D2 (UP_PIN) reads HIGH for a split second when D3 (DOWN_PIN) is pressed
  if (check_button_down(UP_PIN, &up_pressed, true, &up_timestamp, &up_hold_time) && !down_pressed)
  {
    Serial.println("Up pressed");
    menu->up();
  }
  if (check_button_down(LEFT_PIN, &left_pressed, true, &left_timestamp, &left_hold_time))
  {
    Serial.println("Left pressed");
    menu->left();
  }
  if (check_button_down(RIGHT_PIN, &right_pressed, true, &right_timestamp, &right_hold_time))
  {
    Serial.println("Right pressed");
    menu->right();
  }
  if (check_button_down_analog(SELECT_PIN, &select_pressed, &select_timestamp))
  {
    Serial.println("Select pressed");
    delay(100);
    menu->select();
  }
}

void Loop::draw(Menu *menu)
{
  GLCD.ClearScreen();
  menu->draw();
}