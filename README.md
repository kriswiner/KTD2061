# KTD2061
Demo sketch for KTD2058/KTD2061 36-channel rgb led driver family

Straightforward translation of many of the demos for the KTD2061 Evaluation Kit (KTD2061EUAC-EV1) from the original Python to
Arduino-IDE-compatible C++.

Rather than the Evaluation Kit, which is rather expensive, I designed and assembled my own [breakout board](https://oshpark.com/shared_projects/IfVZ6NAp) using the KTD2058 (I2C address 0x60) variant of the device family. The family comes in several variants each identical but for different I2C addresses so two or more can be easily ganged for controlling multiples batches of 36 rgb leds. 

The data sheet lists several requirements for the leds that can be driven with the KTD2061 drivers and recommends several particular part numbers. I used the Lumex [LX0303](https://www.lumex.com/datasheet/SML-LX0303RGBC+1TR) rgb leds, which have been discontued but persist with a different [part number](https://www.mouser.com/ProductDetail/Lumex/SML-LX0303RGBC-1TR?qs=%2Fha2pyFaduiB1xzLMZf49k2WyUwxAIaczuP6ZrGk3iiDCIZtmBvRdw%3D%3D). These small rgb leds wotk well with the KTD2058 driver.
