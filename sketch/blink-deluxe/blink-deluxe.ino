#include <openGLCD.h>
#include <blink-deluxe.h>

// PINS:
// 2 - up
// 3 - down
// 12 - left
// 13 - right
// A6 - select (kinda funky rn)

// Pin declarations
#define UP_PIN 2
#define DOWN_PIN 3
#define LEFT_PIN 12
#define RIGHT_PIN 13
#define SELECT_PIN A6
#define LED_PIN A5

Menu main_menu;

MenuVariable *on_time = new MenuVariable("On time", 100, 0, 100000, 1);
MenuVariable *off_time = new MenuVariable("Off time", 100, 0, 100000, 1);
Runner *runner = new Runner("Run", on_time, off_time);

MenuItem* main_menu_items[] = {
  on_time,
  off_time,
  runner
};

void setup()
{
  // Setting pins
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  pinMode(SELECT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // // This program uses the rx/tx pins as digital pins
  // // DON'T USE SERAIL MONITOR IF YOU ABSOLUTELY DON'T HAVE TO
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  // Serial.println("Initializing...");

  // Serial.println("Initializing GLCD...");
  // Initialize the GLCD
  GLCD.Init();

  // Select the font for the default text area
  GLCD.SelectFont(System5x7);

  // Serial.println("Initializing menu...");

  main_menu = Menu(main_menu_items, sizeof(main_menu_items) / sizeof(main_menu_items[0]));

  // GLCD.println("Hello, world!");

  //  GLCD.print(F("hello, world!")); // keep string in flash on AVR boards with IDE 1.x
  //  GLCD.Puts(F("hello, world!")); // Puts() supports F() with any version of IDE

  // print() below uses RAM on AVR boards but works
  // on any version of IDE with any processor
  // note: Same is true for Puts()
}

void test_pins()
{
  // Serial.println("Testing pins...");
  if (digitalRead(UP_PIN) == HIGH)
  {
    Serial.println("Up pressed");
  }
  if (digitalRead(DOWN_PIN) == HIGH)
  {
    Serial.println("Down pressed");
  }
  if (digitalRead(LEFT_PIN) == HIGH)
  {
    Serial.println("Left pressed");
  }
  if (digitalRead(RIGHT_PIN) == HIGH)
  {
    Serial.println("Right pressed");
  }
  if (analogReadDigital(SELECT_PIN) == HIGH)
  {
    Serial.println("Select pressed");
  }
}

void loop()
{
  // Serial.println("Updating...");
  Loop::update(&main_menu);

  // Serial.println("Drawing...");
  Loop::draw(&main_menu);

  // test_pins();
  delay(20);
}
