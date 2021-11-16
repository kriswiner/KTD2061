# KTD2061
Demo sketch for KTD2058/KTD2061 36-channel rgb led driver family

Straightforward translation of many of the demos for the KTD2061 Evaluation Kit (KTD2061EUAC-EV1) from the original Python to
Arduino-IDE-compatible C++. The KTD2061 family requires 3V3 and GND, I2C (SDA/SCL) connections to the MCU to allow control of the led driver.

Rather than the Evaluation Kit, which is expensive, I designed and assembled my own [breakout board](https://oshpark.com/shared_projects/IfVZ6NAp) using the KTD2058 (I2C address 0x60) variant of the device family. The family comes in several variants each identical but for different I2C addresses so two or more can be easily ganged for controlling multiple batches of 12 rgb leds. 

![image](https://user-images.githubusercontent.com/6698410/141882034-2c540819-88d3-48e8-84b5-86b890a51f68.jpg)

The data sheet lists several requirements for the leds that can be driven with the KTD2061 drivers and recommends several particular rgb led part numbers. I used the Lumex [LX0303](https://www.lumex.com/datasheet/SML-LX0303RGBC+1TR) rgb leds, which have been discontinued but persist with a different [part number](https://www.mouser.com/ProductDetail/Lumex/SML-LX0303RGBC-1TR?qs=%2Fha2pyFaduiB1xzLMZf49k2WyUwxAIaczuP6ZrGk3iiDCIZtmBvRdw%3D%3D). These small rgb leds work well with the KTD2058 driver and are very pretty.

I am using a STM32L432 ([Ladybug](https://www.tindie.com/products/tleracorp/ladybug-stm32l432-development-board/)) development board but just about any Arduino-compatible MCU with an I2C port will work with this sketch.

Download the EAGLE CAD design files from OSH Park shared space [here](https://oshpark.com/shared_projects/IfVZ6NAp).

2021 Copyright Tlera Corporation All Rights Reserved.

Hardware design and Arduino sketch may be used without restriction as long as properly attributed.
