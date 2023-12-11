#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "wdt.h"
#include "lcdutils.h"
#include "lcddraw.h"
int sec = 0;
int oldperiod = 0;
int period = 19010;
int OFFSET = 0;
int State = 0;
int SC = 0;
int SCC = 0;
int SM = 0;
int invx = 1;
int invy = 1;
int xspeed = 0;
int yspeed = 0;
u_char xcords = 0;
u_char ycords = 0;
u_char xold = 0;
u_char yold = 0;
void main(void) 
{  
  configureClocks();
  enableWDTInterrupts();
  switch_init();
  led_init();
  lcd_init();
  buzzer_init();
  buzzer_set_period(period);

  or_sr(0x8);  // GIE on

  while(1){
    P1OUT |= LED_GREEN;
    switch(State){
    case 1:
      if(SCC)
      clearScreen(COLOR_WHITE);
      fillRectangle(xold, yold, 50, 50, COLOR_WHITE);
      fillRectangle(xcords, ycords, 50, 50, COLOR_GREEN);
      xold = xcords;
      yold = ycords;
      break;
    case 0:
      if(SCC)
      clearScreen(COLOR_BLACK);
      fillRectangle(xold, yold, 50, 50, COLOR_BLACK);
      fillRectangle(xcords, ycords, 50, 50, COLOR_GREEN);
      xold = xcords;
      yold = ycords;
      break;
      }
    P1OUT &= ~LED_GREEN;
    SC = 0;
    SM = 0;
    SCC = 0;
    or_sr(0x10); //CPU off
    
 } 
} 

//void setoff(int a){
  //OFFSET=a;
  //}
void setper(int a){
  if(period = 0){}else{
  oldperiod = period;
  period=a;
  buzzer_set_period(period);
  
  }
}

void timehandle(){
  if((sec % 25) == 0){
    if (OFFSET != 0){
    if (period == 0){
	period = 1950;
    }
    else if(period > 2050){
    period = 1900;
    if(State != 1){
    State = 1;
    SC = 1;
    SCC =1;
    }
    
    }
    else if (period < 1900){
     period = 2050;
     if(State == 1){
     State = 0;
     SC = 1;
     SCC =1;
     }
     }else{
    period += OFFSET;
    }
    buzzer_set_period(period);
    }
  }
 if(sec == 50){
   if(xcords >= (SHORT_EDGE_PIXELS-50))
     invx = -1;
   if (xcords <= 5 || xcords >= 250)
     invx = 1;
   if(ycords >= (LONG_EDGE_PIXELS-50)){
     invy = -1;
   }
   if(ycords <= 5 || ycords >= 250)
     invy = 1;
   ycords += (invy * yspeed);
   xcords += (invx * xspeed);
   if(!(xcords == xold && ycords == yold)){
   SC = 1;
   SM = 1;
   }
   sec = 0;
 }
  sec += 1;
}
/*
void
__interrupt_vec(WDT_VECTOR) WDT(){
  timehandle();
  if(SC){
    P1O
    }*/

