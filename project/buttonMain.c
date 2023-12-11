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
      clearScreen(COLOR_WHITE);
      break;
    case 0:
      clearScreen(COLOR_BLACK);
      break;
      }
    P1OUT &= ~LED_GREEN;
    SC = 0;
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
  }
}

void timehandle(){
if(sec == 25){
    if (period == 0){
      if(OFFSET!=0){
	period = 1950;
      }
    }
    else if(period > 2050){
    period = 1900;
    State = 1;
    SC = 1;
    
    }
    else if (period < 1900){
     period = 2050;
     State = 0;
     SC = 1;
     }else{
    period += OFFSET;
    }
    buzzer_set_period(period);
    sec =0;
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

