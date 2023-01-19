#include <openGLCD.h>
#include <blink-deluxe.h>

// PINS:
// 2 - up
// 3 - down
// 12 - left
// 13 - right
// A5 - select (kinda funky rn)

// Pin declarations
#define UP_PIN 2
#define DOWN_PIN 3
#define LEFT_PIN 12
#define RIGHT_PIN 13
#define SELECT_PIN A7

// Button states
boolean up_pressed = false;
boolean down_pressed = false;
boolean left_pressed = false;
boolean right_pressed = false;
boolean select_pressed = false;

// Button timestamps (for holding down button)
unsigned long up_timestamp = 0;
unsigned long down_timestamp = 0;
unsigned long left_timestamp = 0;
unsigned long right_timestamp = 0;

// Button hold time constants (in ms)
const unsigned long hold_delays[] = {500, 500, 250, 250, 250, 250, 125};

// Button hold times (indices for hold_delays)
int up_hold_time = 0;
int down_hold_time = 0;
int left_hold_time = 0;
int right_hold_time = 0;

Menu main_menu;

MenuItem* main_menu_items[] = {
  new MenuVariable("On time", 100, 0, 100000, 1),
  new MenuVariable("Off time", 100, 0, 100000, 1)
};

void setup()
{
  // Setting pins
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  pinMode(SELECT_PIN, INPUT);

  // // This program uses the rx/tx pins as digital pins
  // // DON'T USE SERAIL MONITOR IF YOU ABSOLUTELY DON'T HAVE TO
  // Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  // Serial.println("Initializing...");

  // Serial.println("Initializing GLCD...");
  // Initialize the GLCD
  GLCD.Init();

  // Select the font for the default text area
  GLCD.SelectFont(System5x7);

  // Serial.println("Initializing menu...");

  main_menu = Menu(main_menu_items, sizeof(main_menu_items) / sizeof(main_menu_items[0]));

  //  GLCD.print(F("hello, world!")); // keep string in flash on AVR boards with IDE 1.x
  //  GLCD.Puts(F("hello, world!")); // Puts() supports F() with any version of IDE

  // print() below uses RAM on AVR boards but works
  // on any version of IDE with any processor
  // note: Same is true for Puts()
}

boolean check_button_down(int pin, boolean *state, boolean allow_hold, unsigned long *timestamp = 0, int *delay_index = 0)
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

void update(Menu *menu)
{

  // Check buttons
  if (check_button_down(DOWN_PIN, &down_pressed, true, &down_timestamp, &down_hold_time))
  {
    menu->down();
  }
  // For some reason D2 (UP_PIN) reads HIGH for a split second when D3 (DOWN_PIN) is pressed
  if (check_button_down(UP_PIN, &up_pressed, true, &up_timestamp, &up_hold_time) && !down_pressed)
  {
    menu->up();
  }
  if (check_button_down(LEFT_PIN, &left_pressed, true, &left_timestamp, &left_hold_time))
  {
    menu->left();
  }
  if (check_button_down(RIGHT_PIN, &right_pressed, true, &right_timestamp, &right_hold_time))
  {
    menu->right();
  }
  // FIXME: Select button makes the program go bananas
  // if (check_button_down(SELECT_PIN, &select_pressed, false)) {
  //   menu->select();
  // }
}

void draw(Menu *menu)
{
  GLCD.ClearScreen();
  menu->draw();
}

void loop()
{
  // Serial.println("Updating...");
  update(&main_menu);

  // Serial.println("Drawing...");
  draw(&main_menu);

  delay(20);
}