/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#in
clude "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
void
f1(){
  for (int i = 0; i<30; i++){
    drawPixel(i, i, COLOR_PINK);
    drawPixel(i, 30-i , COLOR_PINK);
  }
}
void
f2(){
  for (int i = 0; i<30; i++)
    drawPixel(i,30-i , COLOR_PINK);
}

int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  // drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  // fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  f1();
  // f2();
  
}
