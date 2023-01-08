#include <openGLCD.h>
#include <blink-deluxe.h>

Menu main_menu;
MenuItem items[] = {MenuItem("Example 1", NULL), MenuItem("Example 2", NULL), MenuItem("Example 3", NULL)};

void setup()
{
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  Serial.println("Initializing...");

  Serial.println("Initializing GLCD...");
  // Initialize the GLCD
  GLCD.Init();

  // Select the font for the default text area
  GLCD.SelectFont(System5x7);

  Serial.println("Initializing menu...");


  main_menu = Menu(items, 3);

  //  GLCD.print(F("hello, world!")); // keep string in flash on AVR boards with IDE 1.x
  //  GLCD.Puts(F("hello, world!")); // Puts() supports F() with any version of IDE

  // print() below uses RAM on AVR boards but works
  // on any version of IDE with any processor
  // note: Same is true for Puts()
}

void loop()
{
  Serial.println("Drawing menu...");
  GLCD.ClearScreen();
  main_menu.draw();
  main_menu.down();

  delay(1000);
}
