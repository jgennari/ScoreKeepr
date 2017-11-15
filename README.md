# ScoreKeepr
A digital, wireless scorekeeper for games like cornhole & table tennis.

<img src="https://lh3.googleusercontent.com/v-XfOl9yOUwXBhUw_9KL1M1RmGstFs-cc0sc7AzLUCWk5MtLbUBRHvb4mKNmOPK3LZ2nKdJ-m3XZNx1xIlY1d2fsh0-OWNqoPEBlZOwYlDAB7oLBSPhQHNLfKpXnME5yqIEK_pdSLnUG1raSMxbq8ieFafR5spcrzRlGRid4No2GPBQ1lgfbRMEiUszWdZQ-FHBmCuA5NvjknOOYWugCwe-xoZAmURTPv94WJ5gTtfikftMXnjaCPY_iOruHjWMrLOemqN1kLg65kfcA_JyVgk3-Sqyu2QgHjRsreqrudIL2RbhYZZXrLja9f7Y9GRfdWAyVCl4aPl4ejbPDfOqVGram5gd-3SYmTwTHixeHsJ1c2hrf3Q3XNL-hUqBw_PQOdxI7_3Or4zLjRAAtWDpJpKCzSY56Yc55xFr-cvhgNjg21ibghr-AO6FOvbWv7nIQ_g8NmQb5mJ0oGXWGGf1DEtISskDmGwd8uL8wWXGZxsyb-5_SZSNECF2myt_shnB81X51SZLucSdFNhZOnxFXfqd_ByiXA8-avztKmEUaoNpBRSU-sCW0UIWqIiWWQXvxRF2_9lAY2BjMVmLpJkTRGi9EslXvTdD2V3tEvUpxKwZTzBNwN-A0T0qUE1qn60qwI7ZIKHrdw8-sxDz-KK89aCu4A0N3n2p7XJpc=w1778-h910-no" alt="IMAGE ALT TEXT HERE" width="45%"/>
<img src="https://github.com/jgennari/ScoreKeepr/blob/master/board/front.png?raw=true" alt="IMAGE ALT TEXT HERE" width="45%"/>

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
![Inside](https://lh3.googleusercontent.com/EB8lr5_Ue-uhq_NUh4rdfYeRYP7nRB3DBMlZgg_3J5hOfSd1uYdCLQTaeXuNpGC8c9cLIu12nuFSjJkAKhCtU4IvUhB__q3_GUOcpaGGLYo6QbFg7tiwQ45jAksJ-Zd9QVCvl8LS1yXSg4I8O9uJK5HNaD9XBWxRjzXbLjncL52W1ikoEYEDLeEDJWmSYlDcvYjA_hdV3JfOwlji0GLr6CqBMI-H9ZgLcEBMRmrk7r29uR5TKh9C5N2jQqN-UMvFyr6E9sVFt5IGL5bmLd3BoqqCEI8VKAIqtmASSbmaUN2nc58vEXNlERWaFy0fHQO74svl8ZI3PX0SEWtVopb_x6lfeCmAjz_euDoYd0-rWo1uDHaJ6__9-mzs-VV_HwsPqahMUAYGUZAHnBwFdqe3ETE1RTF8E4CeEx2C92uKiha-67SM6pX1D7aOaVZznwVqOyxauL0tRA0LPCLbLV23ZiiW4hlSw1Pl463OUSqbDb0_3s4Wnt3OkX9mm9082GtHOdwN0nlH3qvXS7jh2AqF3_WUU86387mw0M2zp5p6VsKGBsRUY4qkFxGrR08rf1s_KeKtNL6jD79NAmeot9Wv4sJKO8C_U4czSp4aXc_v_Y8tVEaYmF7fUkO6_ZbCfBK-2KSczKPP9wupfp7u7AelitiusxMgmPZPJ39r=w1507-h910-no)

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

## Operation
The operation is simple. There is a power switch in the middle and two rocker switch for player 1 and player 2. Clicking the rocker switches up and down will increase and decrease the score for each player respectively. Pressing and holding the P2 down button will reset the score. Pressing and holding the P1 down button will cycle through different brightness levels. 

<a href="http://www.youtube.com/watch?feature=player_embedded&v=zjyllZozEEc" target="_blank"><img src="http://img.youtube.com/vi/zjyllZozEEc/0.jpg" 
alt="Operation Video" width="240" height="180" border="10" /></a>

## Future Improvements
I learned a lot during this project, and with all project there would be future improvements I would incorporate:

* Reduction in size - Due to the use of the LED backpack and Trinket, a lot of space is wasted between all the surfaces.
* Reduction in cost - Using modules and backpacks helped reduce the complexity in design, however you pay for that service. In future revisions there would be a single PCB utilizing discrete components.
* Mounting - The 3D printed case was the most simple case I could design to hold all the parts securely. There was very little thought to how it would be actually utilized. A redesign should include a mounting solution.
* Bootloader - The current implementation keeps the USB bootloader on the Trinket. However there is about a 3 second delay on boot while it checks for the presence of a USB device. This should be eliminated by burning the code directly to the MCU.
* Channels - Currently any unit listening on the 915mhz frequency with the correct encryption key can participate in the game. Ideally there would be different channels available for different games. 
* Radio - The radio works okay with a wire antenna up to about 50 feet. Any longer and you'd need a different antenna. Also, after I completed the project I found the ESP-Now which utilizes 2.4ghz wifi signal with no router. It would be way cheaper to use a ESP8266 module in this mode.

## Lessons Learned

* I designed the PCB using Fritzing and enjoyed the experience. For a subsequent project I tried Eagle and found it better suited for serious work. 
* I learned how to utilize parametric design in Fusion 360 and it really sped up the design of the case. It took about 5 iterations before I got a fit I was happy with. Without parametric design it would've been 5 redesigns from scratch.
* I misread the specs for the LED 7-segment display and overestimated the power requirements by a large magnitude. I could've used a way smaller regulator, although I do like those three-hole solutions from Pololu.

![Power Testing](https://lh3.googleusercontent.com/AjVLxFHPbsxVVe9WUHqJFsg0Itv99qrcK_7O76fUHGWLvgi-HI0GddeOpkAMe5iwYY-z4soHm4KBF3Rcq_0zcbrp8ysE8UfHm-ivrrlQ7wi-r1DnGCSx6geaM3CF6ygm5Rodh8baM0mogPsS2LttfZIRIvq5LN-UqdWuLgVkqncepPw9SeAwiJ7zAuxhTA1QBnvJm7EAYNrHVbwj5P9cMpNLIxkqsgWk3iP3mLkgXhY3zmTk71eJHTcyhBavuJ8WdZ8oLOBCAgDhZpjDjV2Q3tsKXeTarGumBBO3i65IfKvxsfk457tggdO4OD4tgd5cG6VlY_HR0eL3ahxwbU4yZ3KfsyOZe9Pqo-LZfuVJr4E-FYIsG4I3-frRK_bYW1-XULifTdUp0992RzNoa-_PwHwSOOVFKPyoDxxEUOwiULYdSABSBDb2YgjtWRLIf006e0pBbHLN0mLLx5NpIyKVAPw60FoQCPuwVPMWJ_zXFpd6qpBAYIEc18WNaeqvS9pfy_IbhKHgNGDsMw8FlH3lmc0SJuxIlfOJXkkaTfKN1FyxTsl4vpdWmIftJQALDYr7TfK-oDlHyRLsb63CtthsnFEqAfKqAppmXKEA3mbawZMkrcgmae0jjf8f6ExT2OQSI0VNPIBJNKhkBaW7G9eHiSS24kC_uBMTwRk3=w639-h910-no)