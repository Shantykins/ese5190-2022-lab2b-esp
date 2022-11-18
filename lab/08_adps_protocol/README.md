TODO:

Use the capabilities of your sequencer to implement the ADPS9960 protocol and control the sensor.
Explanation

    The logic behind the sequencer implemnented in part 3 and 4 is extended to read the APDS9969 via the i2c bus using PIO.
    We need to first get the raw values from the APDS9969 Registers for proximity and colour values i.e. RGBC.
    Referring the APDS9969 datasheet the way we access the values (Read or Write) is by first sending a command byte to the slave at adreess 0x39, followed by the register from which we want to read or write followed by the data.

Screenshot 2022-11-18 152748

    In order to initialise the sensor, the power, proixmity and colour enabling bits need to be set at register 0x80.
    In the main while we first check if the values of the proximity and colour registers have changed. This is done by accessing the status register at 0x93. The bits corresponding to the status register for Proximity and Colour are bit no. 1 and bit no. 0 respectively.

Screenshot 2022-11-18 153948

    If the status of these bits changes we read the Colour data (0x94 to 0x9B) and Proximity(0x9C) values and display the output in the console.

Screenshot 2022-11-18 154803 image 7. The final Output we achieve is as follows: WhatsApp Image 2022-11-18 at 3 18 57 PM
