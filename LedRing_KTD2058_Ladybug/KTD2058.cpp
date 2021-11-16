/* 11/15/2021 Copyright Tlera Corporation
 *  
 *  Created by Kris Winer
 *  
 This is a simple library for the KTD2058 36-led driver from Kinetic Technologies
 
 Library may be used freely and without limit with attribution.
 
*/

#include "KTD2058.h"
#include "I2CDev.h"

KTD2058::KTD2058(I2Cdev* i2c_bus)
{
  _i2c_bus = i2c_bus;
}

// Core functions
  uint8_t KTD2058::chipID()
{
  uint8_t temp = _i2c_bus->readByte(KTD2058_ADDRESS, KTD2058_ID);
  return temp;
}


  uint8_t KTD2058::monitor()
{
  uint8_t temp = _i2c_bus->readByte(KTD2058_ADDRESS, KTD2058_MONITOR);
  return temp;
}


  void KTD2058::reset() // return to default registers/conditions
{
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_CONTROL, 0xC0);
}


 void KTD2058:: init(uint8_t en_mode, uint8_t be_en, uint8_t ce_temp)
{
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_CONTROL, en_mode << 6 | be_en << 5 | ce_temp << 3);  
}


  void KTD2058::globalOn(uint8_t fade)
  {
  uint8_t temp = _i2c_bus->readByte(KTD2058_ADDRESS, KTD2058_CONTROL);
  temp &= ~(0x07); // clear fade bits
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_CONTROL, temp | fade | 0x80);
  }


  void KTD2058::globalOff(uint8_t fade)
{
  uint8_t temp = _i2c_bus->readByte(KTD2058_ADDRESS, KTD2058_CONTROL);
  temp &= ~(0x07); // clear fade bits
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_CONTROL, (temp & 0x3F) | fade);
}


  void KTD2058::slowOff()
{
  uint8_t temp = _i2c_bus->readByte(KTD2058_ADDRESS, KTD2058_CONTROL);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_CONTROL, (temp & 0x3F) | 0x07);
}


 void KTD2058::setColor0(uint8_t ired0, uint8_t igrn0, uint8_t iblu0)
{
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_IRED0, ired0);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_IGRN0, igrn0);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_IBLU0, iblu0); 
}


 void KTD2058::setColor1(uint8_t ired1, uint8_t igrn1, uint8_t iblu1)
{
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_IRED1, ired1);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_IGRN1, igrn1);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_IBLU1, iblu1); 
}


void KTD2058::selectOff() 
{
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA12, 0x00);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA34, 0x00);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB12, 0x00);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB34, 0x00);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC12, 0x00);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC34, 0x00);
}

void KTD2058::selectColor0() 
{
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA12, 0x88);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA34, 0x88);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB12, 0x88);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB34, 0x88);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC12, 0x88);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC34, 0x88);
}


void KTD2058::selectColor1() 
{
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA12, 0xFF);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA34, 0xFF);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB12, 0xFF);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB34, 0xFF);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC12, 0xFF);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC34, 0xFF);
}


void KTD2058::selectAll(uint8_t isel) 
{
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA12, isel);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA34, isel);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB12, isel);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB34, isel);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC12, isel);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC34, isel);
}


  void KTD2058::selectOne(uint8_t reg, uint8_t isel, uint16_t t_delay)
  {
  _i2c_bus->writeByte(KTD2058_ADDRESS, regList[reg], isel);
  delay(t_delay);
}


  void KTD2058::selectOneClear(uint8_t reg, uint8_t isel, uint16_t t_delay)
  {
  _i2c_bus->writeByte(KTD2058_ADDRESS, regList[reg], isel);
  delay(t_delay);
  _i2c_bus->writeByte(KTD2058_ADDRESS, regList[reg], 0x00);
}
  

  void KTD2058::selectColors(uint8_t isela12, uint8_t isela34, uint8_t iselb12, uint8_t iselb34, uint8_t iselc12, uint8_t iselc34, uint16_t t_delay)
  {
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA12, isela12);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELA34, isela34);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB12, iselb12);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELB34, iselb34);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC12, iselc12);
  _i2c_bus->writeByte(KTD2058_ADDRESS, KTD2058_ISELC34, iselc34);
  delay(t_delay);
}

// Library functions

  void KTD2058::quickTest(uint8_t fade, uint16_t t_delay)
  {
   reset();
   selectColor0();
   globalOn(fade);
   delay(t_delay);
   globalOff(fade);
   delay(t_delay);
  }

  
  void KTD2058::ghostTest(uint8_t fade, uint16_t t_delay)
  {
   // Ghosting Test Library Function
   // Checks if any LEDs have more ghosting than acceptable.
   // Steps almost blue from RGB to RGB, one at a time.
   slowOff();
   setColor0(0,0,0); // color0 = black (off)
   setColor1(8 , 8, bmax); // color1 = blue (slightly pastel)
   selectOff();
   globalOn(fade);
   for (uint8_t i = 0; i < 6; i++) {
    selectOne(i, 0xF0, t_delay);
    selectOneClear(i, 0x0F, t_delay);
   }
   setColor1(8, gmax, 8); // color1 = green (slightly pastel)
   for (uint8_t i = 0; i < 6; i++) {
    selectOne(i, 0xF0, t_delay);
    selectOneClear(i, 0x0F, t_delay);
   }
   globalOff(fade);
  }

 
  void KTD2058::colorPalette(uint8_t fade, uint16_t t_delay)
  {
   // Color Palette Library Function
   // Displays color0 on A1-3, color1 on C2-4, and rest of palette on A4-C1
   // Adjust color 0 and color 1 to see different palettes
   slowOff();
   setColor0(1, 1, 1); // color0 = super dim white, adjust for other palettes
   setColor1(rmax/2, gmax/2, bmax/2); // color1 = white, adjust for other palettes
   selectColors(0x88, 0x89, 0xAB, 0xCD, 0xEF, 0xFF, 0);
   globalOn(fade);
   delay(t_delay);
   globalOff(fade);
   delay(t_delay);
  }


  void KTD2058::breathe(uint8_t cycles, uint8_t fadeOn, uint16_t timeOn, uint8_t fadeOff, uint16_t timeOff)
  {
   // Breathe Library Function
   // Uses global_on and global_off for simplest form of breathing
   // Breathes any combination of color pre-settings and pre-selections
  for(uint8_t i = 0; i < cycles; i++) 
   {
    globalOn(fadeOn);
    delay(timeOn);
    globalOff(fadeOff);
    delay(timeOff); 
  }
  }


 void KTD2058::breathing_demo()  
 {
 slowOff();
 setColor0(0,0,0); // color0 = black (off)
 setColor1(rmax, gmax, bmax); // color1 = white
 
 // breathe a palette of colors, one at a time
 uint8_t palette_list[7] = {0xCC, 0xAA, 0x99, 0xBB, 0xEE, 0xDD, 0xFF}; // rgbcymw
 for (uint8_t ii = 0; ii < 7; ii++) {
 selectAll(palette_list[ii]);
 breathe(1, 7, 1700, 3, 1300); // cycles=1, fadeOn=7, timeOn=1.7s, fadeOff=3, timeOff=1.3s
 }
   
 // breathe a double-rainbow (full rainbow viewable in every 180 degrees)
 selectColors(0xB9, 0xDC, 0xEA, 0xB9, 0xDC, 0xEA, 0); // select double-rainbow from the palette using gray code
 breathe(3, 7, 1700, 3, 1300); // cycles=3, fadeOn=7, timeOn=1.7s, fadeOff=3, timeOff=1.3s
 
 // tequila sunset two-color breathing
 slowOff();
 setColor0(rmax, gmax/4, 0); // color0 = amber
 setColor1(8, 0, 0); // color1 = dark red
 breathe_2colors(3, 7, 1700, 3, 1300); // cycles=3, fadeOn=7, timeOn=1.7s, fadeOff=3, timeOff=1.3s
 globalOff(3);
 } 


 void KTD2058::breathe_2colors(uint8_t cycles, uint8_t fadeUp, uint16_t timeUp, uint8_t fadeDn, uint16_t timeDn) 
 {
 // Breathe Two Colors Library Function
 // Breathes cycling between pre-set color0 and pre-set color1
   slowOff();
   for(uint8_t i = 0; i < cycles; i++) {
   selectColor0();
   globalOn(fadeUp);
   delay(timeUp);
   slowOff();
   selectColor1();
   globalOn(fadeDn);
   delay(timeDn);
   }
 slowOff();
 }


 void KTD2058::amazinBoot(uint8_t cycles)
{
 // mimic smart-speaker boot, cycles=11 on actual smart-speaker
 slowOff();
 delay(1700); // startup 1.7s delay (3.7s on some Dots)
 uint16_t t_delay = 110; // delay calc for 1.32s per cycle
 // fade up to a dim blue
 setColor0(0, gmax, bmax); // color0 = cyan
 setColor1(0, 0, bmax/8); // color1 = dim blue
 selectColor1();
 globalOn(7);
 delay(3000);
 // chase cyan over dim blue
 chase_1down(cycles, 3, t_delay); // fade=3, delay
 slowOff();
 // chase amber over black
 setColor0(rmax, gmax/4, 0); // color0 = amber
 setColor1(0, 0, 0); // color1 = black (off)
 chase_1down(cycles, 3, t_delay); // fade=3, delay
 globalOff(3);
 delay(1250); // delay of 1.25s
}


void KTD2058::chase_1down(uint8_t cycles, uint8_t fade, uint16_t t_delay)
{
 // Chase One Down Library Function
 // 1xRGB chases in downward direction of registers
 // Color0 is chasing foreground; color1 is background
 globalOn(fade);
   for(uint8_t i = 0; i < cycles; i++) {  
   for(uint8_t j = 6; j > 0; j--) {
    selectOne(j-1, 0x08, t_delay);
    selectOne(j-1, 0x8F, t_delay);
    selectOne(j-1, 0xFF, 0);
   }
   }
 }


 void KTD2058::stackingDemo()
{
 slowOff();
 uint8_t t_delay = 1200/2/6; // delay calc for 1.2s per cycle
 selectOff();
 setColor0(12, 12, bmax); // color0 = pastel blue
 setColor1(0,0,0); // color1 = black (off)
 stack_up(1, t_delay, 0); // fade=1, delay, color=0
 delay(1000);
 setColor1(rmax, gmax, 8); // color1 = pastel yellow
 stack_down(1, t_delay, 1); // fade=1, delay, color=1
 delay(1000);
 setColor0(rmax/2, 0, 0); // color0 = red
 stack_up(0, t_delay, 0); // fade=0, delay, color=0
 delay(1000);
 setColor1(8, gmax, 8); // color1 = pastel green
 stack_down(0, t_delay, 1); // fade=0, delay, color=1
 delay(1000);
 setColor0(0,0,0); // color0 = black (off)
 stack_up(0, t_delay, 0); // fade=0, delay, color=0
 globalOff(1);
 delay(1000);
}


 // Stacking Library Functions
  // No "cycles" because they would just write same color on top of themself
  void KTD2058::stack_up(uint8_t fade, uint16_t t_delay, uint8_t color)
{
 // Stack Up Library Function
 // Stacks in upward direction of registers
 // Choose color=0 (color0) or color=1 (color1) as stacking foreground
 globalOn(fade);
 if(color == 0) { // if color=0,...
   for(uint8_t i = 0; i < 6; i++) { 
     for(uint8_t j = 0; j < 5 - i; j++) {  
     selectOne(j, 0x8F, t_delay);
     selectOne(j, 0xF8, t_delay);
     selectOne(j, 0xFF, 0);
     }
   selectOne(5 - i, 0x8F, t_delay);
   selectOne(5 - i, 0xF8, t_delay);
     for(uint8_t j = 0; j < 5 - i; j++) {  
     selectOne(j, 0x8F, t_delay);
     selectOne(j, 0xF8, t_delay);
     selectOne(j, 0xFF, 0);
     }
   selectOne(5 - i, 0x88, t_delay);
   }
 }
 
 else if(color == 1) { // if color=1,...
   for(uint8_t i = 0; i < 6; i++) { 
     for(uint8_t j = 0; j < 5 - i; j++) {  
     selectOne(j, 0xF8, t_delay);
     selectOne(j, 0x8F, t_delay);
     selectOne(j, 0x88, 0);
     }
   selectOne(5 - i, 0xF8, t_delay);
   selectOne(5 - i, 0x8F, t_delay);
     for(uint8_t j = 0; j < 5 - i; j++) {  
     selectOne(j, 0xF8, t_delay);
     selectOne(j, 0x8F, t_delay);
     selectOne(j, 0x88, 0);
     }
   selectOne(5 - i, 0xFF, t_delay);
   }
 }
 }

 
  void KTD2058::stack_down(uint8_t fade, uint16_t t_delay, uint8_t color) 
  {
 // Stack Down Library Function
 // Stacks in downward direction of registers
 // Choose color=0 (color0) or color=1 (color1) as stacking foreground
 globalOn(fade);
 if(color == 0) { // if color=0,...
   for(uint8_t i = 0; i < 6; i++) {  
     for(uint8_t j = 6; j > i; j--) { 
     selectOne(j - 1, 0xF8, t_delay);
     selectOne(j - 1, 0x8F, t_delay);
     selectOne(j - 1, 0xFF, 0);
     }
   selectOne(i, 0xF8, t_delay);
   selectOne(i, 0x8F, t_delay);     
     for(uint8_t j = 6; j > i; j--) { 
     selectOne(j - 1, 0xF8, t_delay);
     selectOne(j - 1, 0x8F, t_delay);
     selectOne(j - 1, 0xFF, 0);
     }
   selectOne(i, 0x88, t_delay);
   }
 }
   
 else if(color == 1) { // if color=1,...
   for(uint8_t i = 0; i < 6; i++) {  
     for(uint8_t j = 6; j > i; j--) { 
     selectOne(j - 1, 0x8F, t_delay);
     selectOne(j - 1, 0xF8, t_delay);
     selectOne(j - 1, 0x88, 0);
     }
   selectOne(i, 0x8F, t_delay);
   selectOne(i, 0xF8, t_delay);
      
     for(uint8_t j = 6; j > i; j--) { 
     selectOne(j - 1, 0x8F, t_delay);
     selectOne(j - 1, 0xF8, t_delay);
     selectOne(j - 1, 0x88, 0);
     }
   selectOne(i, 0xFF, t_delay);
   }
 }
  }


 // Rainbow Demo shows various ways to make 12-colors show at once.
 // In these examples, the twelve colors form a 12-color rainbow.

 // Twelve Color Rainbow Function
 // Makes a rainbow with 12 independent colors using fade engines.
 // RGBs are on at 50% duty, so 1/2 brightness maximum.
 void KTD2058::twelve_color_rainbow(uint8_t cycles, uint16_t t_delay, uint8_t fade)
 {
 slowOff();
 setColor0(0, 0, 0); // color0 = black (off)
 selectOff();
 globalOn(fade);
 for(uint8_t i = 0; i < cycles; i++) {  
   setColor1(rmax, gmax, bmax); // color1 = white
   selectColors(0xCC, 0xEA, 0xAA, 0xB9, 0x99, 0xDC, t_delay/2);
   selectOff();
   setColor1(rmax/4, gmax/4, bmax/4); // color1 = grey
   selectColors(0x8A, 0x8C, 0x89, 0x8A, 0x8C, 0x89, t_delay/2);
   selectOff();
 }
 globalOff(3);
}

  void KTD2058::twelve_colors(uint8_t cycles, uint16_t t_delay, uint8_t fade)
  {
 // Twelve Colors Function
 // Enables display of 12 simultaneous colors.
 // Colors are set 2 RGBs at a time and held by fade engines;
 // therefore, when smoothed, they are 1/6th of full brightness.
 slowOff();
 selectOff();
 globalOn(fade);
 for(uint8_t i = 0; i < cycles; i++) {  
 setColor0(rmax, 8, 8);
 setColor1(rmax, gmax/4, 8);
 selectColors(0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, t_delay/6);
 selectOff();
 setColor0(rmax, gmax, 8);
 setColor1(rmax/4, gmax, 8);
 selectColors(0x00, 0x8F, 0x00, 0x00, 0x00, 0x00, t_delay/6);
 selectOff();
 setColor0(8, gmax, 8);
 setColor1(8, gmax, bmax/4);
 selectColors(0x00, 0x00, 0x8F, 0x00, 0x00, 0x00, t_delay/6);
 selectOff();
 setColor0(8, gmax, bmax);
 setColor1(8, gmax/4, bmax);
 selectColors(0x00, 0x00, 0x00, 0x8F, 0x00, 0x00, t_delay/6);
 selectOff();
 setColor0(8, 8, bmax);
 setColor1(rmax/4, 8, bmax);
 selectColors(0x00, 0x00, 0x00, 0x00, 0x8F, 0x00, t_delay/6);
 selectOff();
 setColor0(rmax, 8, bmax);
 setColor1(rmax, 8, bmax/4);
 selectColors(0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, t_delay/6);
 selectOff();
 }
  }


  void KTD2058::chasing_rainbow()
{
 // Chasing Rainbow Function
 // Execute the twelve_colors function, and then ramp the fade rate to reveal chasing.
 for(uint8_t fade = 7; fade > 0; fade--) { 
 twelve_colors(1, 1000, fade);
 }
 for(uint8_t fade = 0; fade < 8; fade++) { 
 twelve_colors(1, 1000, fade);
 }
 globalOff(3);
}


 void KTD2058::rainbow_swirl(uint8_t cycles, uint16_t t_delay, uint8_t fade)
{
 // Rainbow Swirl Function
 // Rotates Red, Green, and Blue, but fade-engine blends to show 12 rainbow colors.
 slowOff();
 setColor0(0, 0, 0); // color0 = black (off)
 setColor1(rmax/2, gmax/2, bmax/2); // color1 = white
 globalOn(fade);
 for(uint8_t i = 0; i < cycles; i++) { 
 selectColors(0xCC, 0xCC, 0xAA, 0xAA, 0x99, 0x99, t_delay);
 selectColors(0x9C, 0xCC, 0xCA, 0xAA, 0xA9, 0x99, t_delay);
 selectColors(0x99, 0xCC, 0xCC, 0xAA, 0xAA, 0x99, t_delay);
 selectColors(0x99, 0x9C, 0xCC, 0xCA, 0xAA, 0xA9, t_delay);
 selectColors(0x99, 0x99, 0xCC, 0xCC, 0xAA, 0xAA, t_delay);
 selectColors(0xA9, 0x99, 0x9C, 0xCC, 0xCA, 0xAA, t_delay);
 selectColors(0xAA, 0x99, 0x99, 0xCC, 0xCC, 0xAA, t_delay);
 selectColors(0xAA, 0xA9, 0x99, 0x9C, 0xCC, 0xCA, t_delay);
 selectColors(0xAA, 0xAA, 0x99, 0x99, 0xCC, 0xCC, t_delay);
 selectColors(0xCA, 0xAA, 0xA9, 0x99, 0x9C, 0xCC, t_delay);
 selectColors(0xCC, 0xAA, 0xAA, 0x99, 0x99, 0xCC, t_delay);
 selectColors(0xCC, 0xCA, 0xAA, 0xA9, 0x99, 0x9C, t_delay);
 }
 globalOff(3);
}
 
