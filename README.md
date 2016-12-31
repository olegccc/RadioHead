# RadioHead
http://www.airspayce.com/mikem/arduino/RadioHead/

# Description
This branch is to add working code for RF95 chip and ESP8266/RaspberryPi.

Please read pin configuration for ESP8266 and RPI in doc folder.

# Depencencies

You will need to install wiringPi and bcm2835 libraries in order to compile this code on RPI.

## Configure SPI

```bash
sudo raspi-config
(open Interfacing Options => SPI => Enable SPI => restart)
```

## Install wiringPi

```bash
git clone git://git.drogon.net/wiringPi
cd wiringPi
./build
```

## Install bcm2835

```bash
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.50.tar.gz
tar xvfz bcm2835-1.50.tar.gz
cd bcm2835-1.50
./configure
make
sudo make install
```