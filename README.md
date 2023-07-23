# WatchPi
A Raspberry Pi RP2040-based watch with a color display and some smarts.

![image](https://github.com/abhignay/WatchPi/assets/74813604/331e2707-f14a-45b1-afe8-912f4422b5eb)

## Software
Written in C with the [Raspberry Pi RP2040 C/C++ SDK](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html) 

## Hardware
- The microcontroller is an RP2040, the display module is a GC9A01 that's on a Waveshare RP2040 + 1.28" LCD [module.](https://www.waveshare.com/rp2040-lcd-1.28.htm)
+ WatchPi uses a 400mAh mini LiPo [battery.](https://robu.in/product/400mah-pcm-protected-micro-li-po-battery-2/)
+ For the specced battery to actually fit in the case you will have to destructively remove the battery JST connector on the Waveshare module and directly solder the battery to the PCB
* Mini through-hole Tactile Push-Button switches are used for the buttons.
- The watch case can be 3D printed in any filament you want, STL files are given in the Mechanical folder. I have found [these](https://www.amazon.in/Silicone-Compatible-ColorFit-Caliber-Smartwatch/dp/B0B3KVBHX1/ref=sr_1_2_sspa?crid=253FRRXGHHQEX&keywords=22mm+black+watch+strap&qid=1680966373&s=jewelry&sprefix=22mm+black+watch+str%2Cjewelry%2C322&sr=1-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1) 22mm watch straps to work pretty well, but any 22mm watch strap will fit.
- To secure the backplate of the watch with the case, 2 5-6mm long M2 screws can be used however, some BlueTac or weak adhesives are less good-looking but viable options for holding the backplate in place.

## A couple of other things
This watch currently doesn't do anything else than show time, date, and ambient temperature so you can refer to it as a "dumb watch". I wanted to try out making a wearable device, and this was a good learning experience for me. That said this watch might be a hassle to use if you're used to other open-source smartwatches or just smartwatches in general. The battery currently last's for around 10 hours (with an always-on display) and can be charged with the onboard USB Type C port (the Waveshare module has a battery charge manager on board, and the LiPo has some on-cell protection too but I'd suggest that you always monitor the watch while it is charging and disconnect it from the charger if the watch gets too hot). You will need to edit the RTC's date and time in Software if the watch is not synchronized with the current time.

WatchPi has two watch faces and one that shows the raw data from the onboard IMU. Since it has an IMU a raise-to-wake feature can be added.

If you have any questions or suggestions feel free to open up an issue.

## License
Code in this repository is licensed under the terms of the MIT license.
