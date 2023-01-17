# ESP 32 UltraWideBand (UWB) Indoor position sensing
This project uses Makerfabs [ESP32 UWB (Ultra Wideband) Microcontroller](https://www.makerfabs.com/esp32-uwb-ultra-wideband.html) to perform indoor position sensing.  We calculate the X, Y, and Z for a 3d position sense.

This project uses the [decawave (now acquired by Qorvo) DW1000](https://www.qorvo.com/products/p/DW1000) ultra wide band chip



## What is Ultra-WideBand (UWB)?

### It's like GPS positioning that works indoors

A radio frequency that is [high frequency (often 6GHz to 9GHz)](https://en.wikipedia.org/wiki/Radio_spectrum) and low energy.  Other radio frequencies like FM Radio operate at ~100 MHz so it's infrequent and has a large radio wavelength measured in meters.  [Ultra Wideband](https://en.wikipedia.org/wiki/Ultra-wideband) is fast often operating at 6GHz with a wider band and small wavelenght measured in centemeters.  

This allows locating through triangulation (similar to GPS) but available indoors.





## What range does my testing achive?
### Only 8 meters maximum distance
- **8 meters is a Deal Breaker** 8 meters (20 feet) was the maximum distance I could achieve within my house. Even in clear-line-of-sight (ie no walls or obstructions between the microcontroller) I could not get above 8 meters. 
- **80% False Advertising** Makerfabs advertised 45 meters (85 feet), this must be "theoretical" 45 meters in a outer space with no objects or radio waves around.  
- **Tried Multiple ways to increase distance**
  - **Range Modes** Tried multiple range MODES but none of them exceeded 8 meters.  Other [UWB Distance Tests on Github](https://github.com/jremington/UWB-Indoor-Localization_Arduino)  found MODE_LONGDATA_RANGE_LOWPOWER "range up to 33 m. All other options lead to 5-10 m at best." 
    - **33 meters REALLY??** I was unable to reproduce these results
    - [ ] **TODO: Double the TX (Transmitter) power** as seen on this [git repo](https://github.com/jremington/UWB-Indoor-Localization_Arduino/blob/main/DW1000_library_highpower/src/DW1000.cpp) "last update 5/30/22 line 650 doubled TX_POWER to 0x28"
  - **Clear line of sight** I tried tests with objects and walls in the way.  Compared to clear/straight open air tests the results did not vary much.  This indicated UWB is decent at moving through walls.
- **New Product ESP32 UWB Pro** [ high power UWB launched by makerfabs.com](https://www.makerfabs.cc/product/esp32-uwb-high-power-version-120m.html) with an advertised 200 meter distance/range.
    - **Makerfab's realized their problem** This was released about a year after I purchased the original chip. 
    -  **Still 80% overestimating/ false advertising? = 40 meters (120 feet)**  If the new chip is about the same 80% hopium advertisement as their original UWB chip... it will achive 40 meters (120 feet) of the 200 meters they advertise.   
        -  The regular ESP32 UWB I tested is advertised at 45 meters but my testing indicates 8 meters maximum distance. Approximatly 20%
     -  **Is it worth $300 to test the new chip's distance?** (5 chips needed @ $55 each for X*2,Y,Z, Tag anchors for 3d position)
