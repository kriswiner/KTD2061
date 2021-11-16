/* 
 * 11/15/2021 Copyright Tlera Corporation
 *  
 *  Created by Kris Winer
 *  
 *  The KTD2058 is a 36-channel led controller (https://www.kinet-ic.com/KTD2061/).
 *  
 *  This sketch uses default SDA/SCL pins on the Ladybug (STM32L432KC) development boards, but
 *  should work on almost any dev board that supports I2C
 *
 *  Library may be used freely and without limit with attribution.
 */
#include "KTD2058.h"

#define I2C_BUS    Wire               // Define the I2C bus (Wire instance) you wish to use

I2Cdev             i2c_0(&I2C_BUS);   // Instantiate the I2Cdev object and point to the desired I2C bus

#define myLed 13

uint8_t KTD2058_chipID, KTD2058_status;

// Configure led driver
uint8_t en_mode = 2; // EnableMode: 1 = night, 2 = normal(day)
uint8_t be_en   = 1; // BrightExtend: 0 = disabled, 1 = enabled
uint8_t ce_temp = 2; //  CoolExtend: 0 = 135C, 1 = 120C, 2 = 105C, 3 = 90C

KTD2058 KTD2058(&i2c_0); // instantiate KTD2058 class

void setup() {
  Serial.begin(115200);
  Serial. blockOnOverrun(false);
  delay(4000);

  pinMode (myLed, OUTPUT);
  
  I2C_BUS.begin();                // Set master mode, default on SDA/SCL for STM32L4
  I2C_BUS.setClock(400000);       // I2C frequency at 400 kHz
  delay(1000);
  
  Serial.println("Scan for I2C devices:");
  i2c_0.I2Cscan();                // should detect IS31FL3246 at 0x30
  delay(1000);

  KTD2058_chipID = KTD2058.chipID();
  Serial.print("KTD2058 Vendor ID = 0x0"); Serial.print((KTD2058_chipID & 0xE0) >> 5, HEX); Serial.println(", should be 0x05");
  Serial.print("KTD2058 Die = 0x0"); Serial.print(KTD2058_chipID & 0x1F, HEX); Serial.println(", should be 0x05");

  KTD2058.init(en_mode, be_en, ce_temp);

  // Status of the rgb led driver
  KTD2058_status = KTD2058.monitor();  
  Serial.print("Status = 0x"); Serial.println(KTD2058_status, HEX);
  if((KTD2058_status & 0xF0) == 0x10) Serial.println("KTD2058 is a prototype IC");
  if((KTD2058_status & 0xF0) == 0x20) Serial.println("KTD2058 is an engineering sample IC");
  if((KTD2058_status & 0xF0) == 0x30) Serial.println("KTD2058 is a mass production IC");
  if(KTD2058_status & 0x08) Serial.println("At least one LED_n output is shorted to ground!");
  if(KTD2058_status & 0x04) Serial.println("There is dropout, and BrightExtend™ is enabled and active!");
  if(KTD2058_status & 0x02) Serial.println("The die is hot, and CoolExtend™ is active!");
  if(KTD2058_status & 0x01) Serial.println("VCC is between VPOR and VUVLO, or the die is in thermal shutdown!");

// Demo tests
  KTD2058.quickTest(6, 5000);
  digitalWrite(myLed, HIGH); delay (1000); digitalWrite(myLed, LOW);
  KTD2058.ghostTest(0, 500);
  digitalWrite(myLed, HIGH); delay (1000); digitalWrite(myLed, LOW);
  KTD2058.colorPalette(3, 5000);
  digitalWrite(myLed, HIGH); delay (1000); digitalWrite(myLed, LOW);
  KTD2058.breathing_demo();
  digitalWrite(myLed, HIGH); delay (1000); digitalWrite(myLed, LOW);  
  KTD2058.amazinBoot(3);
  digitalWrite(myLed, HIGH); delay (1000); digitalWrite(myLed, LOW);
  KTD2058.stackingDemo();
  digitalWrite(myLed, HIGH); delay (1000); digitalWrite(myLed, LOW);
  
  KTD2058.twelve_color_rainbow(2, 1000, 4);
  KTD2058.chasing_rainbow();
  KTD2058.twelve_color_rainbow(2, 1000, 4);
  KTD2058.rainbow_swirl(6, 125, 3);
  KTD2058.twelve_colors(6, 600, 3);
  digitalWrite(myLed, HIGH); delay (1000); digitalWrite(myLed, LOW);
 
  Serial.println("End of Setup!");

} /* end of Setup */

void loop() {
  
  digitalWrite(myLed, HIGH); delay(1000); digitalWrite(myLed, LOW); delay(1000);

} // end of main loop //
