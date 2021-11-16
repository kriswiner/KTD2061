/* 11/15/2021 Copyright Tlera Corporation
 *  
 *  Created by Kris Winer
 *  
 This is a simple library for the KTD2058 36-led driver from Kinetic Technologies
 
 Library may be used freely and without limit with attribution.
 
*/
  
#ifndef KTD2058_h
#define KTD2058_h

#include "Arduino.h"
#include "I2CDev.h"
#include <Wire.h>

/* KTD2058 registers */
#define KTD2058_ID         0x00
#define KTD2058_MONITOR    0x01
#define KTD2058_CONTROL    0x02
#define KTD2058_IRED0      0x03
#define KTD2058_IGRN0      0x04
#define KTD2058_IBLU0      0x05
#define KTD2058_IRED1      0x06
#define KTD2058_IGRN1      0x07
#define KTD2058_IBLU1      0x08
#define KTD2058_ISELA12    0x09
#define KTD2058_ISELA34    0x0A
#define KTD2058_ISELB12    0x0B
#define KTD2058_ISELB34    0x0C
#define KTD2058_ISELC12    0x0D
#define KTD2058_ISELC34    0x0E

#define KTD2058_ADDRESS    0x69  

typedef enum {
  FADE_32                = 0x00, // in milliseconds
  FADE_63                = 0x01,
  FADE_125               = 0x02,
  FADE_250               = 0x03,
  FADE_500               = 0x04,
  FADE_1000              = 0x05,
  FADE_2000              = 0x06,
  FADE_4000              = 0x07  
} FADE_LIST;


class KTD2058
{
  public: 
  KTD2058(I2Cdev* i2c_bus);
  uint8_t chipID();
  uint8_t monitor();
  void reset();
  void init(uint8_t en_mode, uint8_t be_en, uint8_t ce_temp);
  
  // Core Functions
  void globalOff(uint8_t fade);
  void globalOn(uint8_t fade);
  void slowOff();
  void setColor0(uint8_t ired0, uint8_t igrn0, uint8_t iblu0);
  void setColor1(uint8_t ired1, uint8_t igrn1, uint8_t iblu1);
  void selectOff();
  void selectColor0();
  void selectColor1();
  void selectAll(uint8_t isel);
  void selectOne(uint8_t reg, uint8_t isel, uint16_t t_delay);
  void selectOneClear(uint8_t reg, uint8_t isel, uint16_t t_delay);
  void selectColors(uint8_t isela12, uint8_t isela34, uint8_t iselb12, uint8_t iselb34, uint8_t iselc12, uint8_t iselc34, uint16_t t_delay);

  // Library Functions and Demos
  void quickTest(uint8_t fade, uint16_t t_delay);   
  void ghostTest(uint8_t fade, uint16_t t_delay);
  void colorPalette(uint8_t fade, uint16_t t_delay);
  void breathe(uint8_t cycles, uint8_t fadeOn, uint16_t timeOn, uint8_t fadeOff, uint16_t timeOff);
  void breathe_2colors(uint8_t cycles, uint8_t fadeUp, uint16_t timeUp, uint8_t fadeDn, uint16_t timeDn);   
  void breathing_demo(); 
  void amazinBoot(uint8_t cycles);  
  void chase_1down(uint8_t cycles, uint8_t fade, uint16_t t_delay);
  void stackingDemo();
  void stack_up(uint8_t fade, uint16_t t_delay, uint8_t color);
  void stack_down(uint8_t fade, uint16_t t_delay, uint8_t color); 
  void twelve_color_rainbow(uint8_t cycles, uint16_t t_delay, uint8_t fade);
  void twelve_colors(uint8_t cycles, uint16_t t_delay, uint8_t fade); 
  void chasing_rainbow();
  void rainbow_swirl(uint8_t cycles, uint16_t t_delay, uint8_t fade);  
  
  private:
  I2Cdev* _i2c_bus;
  uint8_t rmax = 80;
  uint8_t gmax = 128;
  uint8_t bmax = 108;
  uint8_t regList[6] = {KTD2058_ISELA12, KTD2058_ISELA34, KTD2058_ISELB12, KTD2058_ISELB34, KTD2058_ISELC12, KTD2058_ISELC34};
 };

#endif
