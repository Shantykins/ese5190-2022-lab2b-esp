

Toggle the Qt Py's Neopixel LED when the BOOT button is pressed, using only direct register reads to access the boot button status. You may use the SDK to initialize the board and the pins, and the WS2812 example code to toggle the Neopixel. 

The code to toggle the Qt Py's Neopixel LED when the BOOT button is pressed by using only direct register reads to access the boot button status has been attached in this folder.

![blink_on_boot](https://user-images.githubusercontent.com/114099174/200090063-4bb468eb-cbae-46fa-bdc5-82a3193f4ce8.gif)

Boot pin number is 21. To access the register for the boot pin, an offset of `0x0A8` is added to the the `IO_BANK0_BASE`. 

By reading the register on boot press, we identify that it takes a hex value of 0x00000000 on each boot press.

The Neopixel LED blinks on every occurence of 0x00000000 on the boot pin register.
