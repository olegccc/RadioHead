# RaspberryPi

## Pinout

RF95 pins        | RaspberryPi pins | WiringPI pins
---------------- | ---------------- | -------------
DIO0 (Interrupt) | 15 GPIO3         | 3
3.3V             | 1  3.3V          |         
GND              | 9  GND           |         
MISO             | 21 MISO          | 13
MOSI             | 19 MOSI          | 12
SCK              | 23 SCLK          | 14          
NSS              | 24 CE0           | 10          
RESET            | 13 GPIO2         | 2          

## Initialize RF95 object instance

```cpp
#define RFM95_CS 10
#define RFM95_RST 2
#define RFM95_INT 3
#define RF95_FREQ 434.0
RH_RF95 rf95(RFM95_CS, RFM95_INT);
wiringPiSetup();
pinMode(RFM95_RST, OUTPUT);
digitalWrite(RFM95_RST, HIGH);
digitalWrite(RFM95_RST, LOW);
delay(10);
digitalWrite(RFM95_RST, HIGH);
delay(10);
rf95.init();
rf95.setFrequency(RF95_FREQ);
```