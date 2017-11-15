# ScoreKeepr
A digital, wireless scorekeeper for games like cornhole & table tennis.

![Picture of ScoreKeepr](https://lh3.googleusercontent.com/v-XfOl9yOUwXBhUw_9KL1M1RmGstFs-cc0sc7AzLUCWk5MtLbUBRHvb4mKNmOPK3LZ2nKdJ-m3XZNx1xIlY1d2fsh0-OWNqoPEBlZOwYlDAB7oLBSPhQHNLfKpXnME5yqIEK_pdSLnUG1raSMxbq8ieFafR5spcrzRlGRid4No2GPBQ1lgfbRMEiUszWdZQ-FHBmCuA5NvjknOOYWugCwe-xoZAmURTPv94WJ5gTtfikftMXnjaCPY_iOruHjWMrLOemqN1kLg65kfcA_JyVgk3-Sqyu2QgHjRsreqrudIL2RbhYZZXrLja9f7Y9GRfdWAyVCl4aPl4ejbPDfOqVGram5gd-3SYmTwTHixeHsJ1c2hrf3Q3XNL-hUqBw_PQOdxI7_3Or4zLjRAAtWDpJpKCzSY56Yc55xFr-cvhgNjg21ibghr-AO6FOvbWv7nIQ_g8NmQb5mJ0oGXWGGf1DEtISskDmGwd8uL8wWXGZxsyb-5_SZSNECF2myt_shnB81X51SZLucSdFNhZOnxFXfqd_ByiXA8-avztKmEUaoNpBRSU-sCW0UIWqIiWWQXvxRF2_9lAY2BjMVmLpJkTRGi9EslXvTdD2V3tEvUpxKwZTzBNwN-A0T0qUE1qn60qwI7ZIKHrdw8-sxDz-KK89aCu4A0N3n2p7XJpc=w1778-h910-no)
![Front Board Picture](https://github.com/jgennari/ScoreKeepr/blob/master/board/front.png?raw=true)

## Overview
ScoreKeepr is a digital, wireless score keeping device for two player games where the players may be stationed apart from each other. For games like [cornhole](https://en.wikipedia.org/wiki/Cornhole) or [table tennis](https://en.wikipedia.org/wiki/Table_tennis). This was my first fully integrated hardware project, including PCB design, CAD modeling for the case, 3D printing, assembly and coding.

## Required
You can buy all the parts individually or use the Digi-Key cart I've created [here](http://www.digikey.com/short/q38b45).

* PCB [(link)](https://oshpark.com/shared_projects/CAZ9tcIK)
* Trinket Pro 5V [(link)](https://www.adafruit.com/product/2000)
* RFM69 Radio Module [(link)](https://www.adafruit.com/product/3070)
* LED 7-Segment Backpack [(link)](https://www.adafruit.com/product/1268)
* 5V Regulator [(link)](https://www.pololu.com/product/2119)
* Various switches
* Basic soldering skills
* 3D Printer

## Assembly
The assembly is simple. The Trinket Pro & radio module are mated to the PCB using standard .1" headers for ease of debugging. I used .1" header to connect the switches and regulator, so soldering should be very simple.

## Programming
The Trinket Pro 5V has a USB bootloader, so programming is pretty straight forward. Just load the INO file into the Arduino IDE and upload to the device. You will need the following before you can compile and upload:

* Install the following libraries in your Arduino environment:

   Bounce2 [(link)](https://github.com/thomasfredericks/Bounce2)  
   Adafruit_GFX [(link)](https://github.com/adafruit/Adafruit-GFX-Library)  
   Adafruit_LEDBackpack [(link)](https://github.com/adafruit/Adafruit_LED_Backpack)  
   RadioHead [(link)](http://www.airspayce.com/mikem/arduino/RadioHead/)  
   PinChangeInterrupt [(link)](https://github.com/NicoHood/PinChangeInterrupt)  
   LowPower [(link)](https://github.com/rocketscream/Low-Power)  
   EEPROMex [(link)](https://github.com/thijse/Arduino-EEPROMEx)  
* Install the Trinket Pro boards in the Arduino IDE [(link)](https://learn.adafruit.com/introducing-pro-trinket/setting-up-arduino-ide)

## Future Improvements
I learned a lot during this project, and with all project there would be future improvements I would incorporate:

* Reduction in size - Due to the use of the LED backpack and Trinket, a lot of space is wasted between all the surfaces.
* Reduction in cost - Using modules and backpacks helped reduce the complexity in design, however you pay for that service. In future revisions there would be a single PCB utilizing discrete components.
* Mounting - The 3D printed case was the most simple case I could design to hold all the parts securely. There was very little thought to how it would be actually utilized. A redesign should include a mounting solution.
* Bootloader - The current implementation keeps the USB bootloader on the Trinket. However there is about a 3 second delay on boot while it checks for the presence of a USB device. This should be eliminated by burning the code directly to the MCU.

## Lessons Learned

* I designed the PCB using Fritzing and enjoyed the experience. For a subsequent project I tried Eagle and found it better suited for serious work. 
* I learned how to utilize parametric design in Fusion 360 and it really sped up the design of the case. It took about 5 iterations before I got a fit I was happy with. Without parametric design it would've been 5 redesigns from scratch.


