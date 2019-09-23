### I2C Addresses when using two I2C displays
```
You can change the address of a backpack very easily. Look on the back to find the two or three A0, A1 or A2 solder jumpers. Each one of these is used to hardcode in the address. If a jumper is shorted with solder, that sets the address. A0 sets the lowest bit with a value of 1, A1 sets the middle bit with a value of 2 and A2 sets the high bit with a value of 4. The final address is 0x70 + A2 + A1 + A0. So for example if A2 is shorted and A0 is shorted, the address is 0x70 + 4 + 1 = 0x75. If only A1 is shorted, the address is 0x70 + 2 = 0x72
```
See https://learn.adafruit.com/adafruit-led-backpack/changing-i2c-address for more details



