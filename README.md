##WHAT THE FILES DO

-Provides native C functions for rp2040, rp2350, pico and pico-2 microcontrollers (Using the pico-sdk)

##IMPROVEMENTS TO BE MADE

I plan to include all functions for all the registers and a more complete solution in the near future.

#INSTRUCTIONS FOR USE

Copy the AS5600.h and AS5600.c files into the same directory in which your source file/ main function is and add "#include "AS5600.c" in the file in which you are writing your program or where you are bringing everything together.

##CONNECTING THE AS5600 TO YOUR MICROCONTROLLER:

The default Hardware I2C port GP4 and GP5 on the pico-2 didn't work with the AS5600 for me but I found that pins GP8 and GP9 work.

for example code that implements the readAAS5600() and a few other functions check out the examples.c file.

When writing to the registers cross check with the data sheet to ensure you are sending out the correct data.

I haven't included any of the burn functions since its a permanent procedure and you can only burn the values upto 3 times for certain values and only 1 time for others. If you wanted to store the starting position ZPOS, stop position MPOS or the anglular range MANG you can simply write the desired value to the registers using the corresponding write functions, which will then be stored in the chip until the power is cut off or there is a power reset.

#DOCUMENTATION OF FUNCTIONS:- 

readAS5600_Angle();    ->  reads the raw angle value from the angle register and                                converts it to a value in range from 0 to 360 and returns                            the absolute angle as a float

readAS5600_Status();  -> reads the status register and prints "Magnet too weak" if                            the magnet is far away, returning 0, "Magnet too strong" if                          the magnet is too close to the sensor returning 0. The                               function returns the value in the status register as an                              integer if the distancing is perfect.

readAS5600_AGC();  -> returns the AGC gain value as an integer. for optimal                                positioning the gain should be in the middle of its range so                         for 5v operation, the range is 0 to 255 counts, and for 3v3                          operation the range is reduced to 0 to 128 counts.

readAS5600_Magnitude();  -> returns the magnitude of the internal cordic as an                                   integer.

writeA5600_HYST(int lsb) ; -> takes in the HYST bits in the CONF register in lsb                                   format as an integer and writes/changes only those                                   bits of the CONF register.

writeAS5600_ZPOS(uint8_t zpos[2]); -> takes the ZPOS register values in hexadecimal                                        since there is a H and L registers for ZPOS                                          the H and L parts are taken separately as                                            zpos[0] = H and zpos[1] = L

writeAS5600_MPOS(uint8_t mpos[2]); -> input is the exact same structure as for                                             writing to ZPOS.

writeAS5600_PM(int mode); -> takes the power mode as an integer input.

readAS5600_ZMCO(); -> checks and returns the data if any stored in the ZMCO register
                      adn prints if the chip has already been burned/programmed.
