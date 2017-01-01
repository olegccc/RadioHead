// RasPi.cpp
//
// Routines for implementing RadioHead on Raspberry Pi
// using BCM2835 library for GPIO
//
// Contributed by Mike Poublon and used with permission


#include <RadioHead.h>

#if (RH_PLATFORM == RH_PLATFORM_RASPI)

#include <sys/time.h>
#include <time.h>
#include "RasPi.h"
#include <wiringPi.h>

void attachInterrupt(uint8_t pin, void (*interruptHandler)(void), int mode) {

    int piMode = INT_EDGE_RISING;
    switch (mode) {
        case RISING:
            piMode = INT_EDGE_RISING;
            break;
        case FALLING:
            piMode = INT_EDGE_FALLING;
            break;
        case CHANGE:
            piMode = INT_EDGE_BOTH;
            break;
        case LOW:
            piMode = INT_EDGE_SETUP;
            break;
    }

    wiringPiISR(pin, piMode, interruptHandler);
}

//Initialize the values for sanity
timeval RHStartTime;

void SPIClass::begin() {
    //Set SPI Defaults
    uint16_t divider = BCM2835_SPI_CLOCK_DIVIDER_256;
    uint8_t bitorder = BCM2835_SPI_BIT_ORDER_MSBFIRST;
    uint8_t datamode = BCM2835_SPI_MODE0;

    begin(divider, bitorder, datamode);
}

void SPIClass::begin(uint16_t divider, uint8_t bitOrder, uint8_t dataMode) {

    bcm2835_init();
    bcm2835_spi_begin();

    bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);

//    setClockDivider(divider);
//    setBitOrder(bitOrder);
//    setDataMode(dataMode);
//
//    //Set CS pins polarity to low
//    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);
//
//    bcm2835_spi_begin();

    //Initialize a timestamp for millis calculation
    gettimeofday(&RHStartTime, NULL);
}

void SPIClass::end() {
    //End the SPI
    bcm2835_spi_end();
}

void SPIClass::setBitOrder(uint8_t bitOrder) {
    //Set the SPI bit Order
    bcm2835_spi_setBitOrder(bitOrder);
}

void SPIClass::setDataMode(uint8_t mode) {
    //Set SPI data mode
    bcm2835_spi_setDataMode(mode);
}

void SPIClass::setClockDivider(uint16_t rate) {
    //Set SPI clock divider
    bcm2835_spi_setClockDivider(rate);
}

byte SPIClass::transfer(byte _data) {
    //Set which CS pin to use for next transfers
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    //Transfer 1 byte
    byte data;
    data = bcm2835_spi_transfer((uint8_t) _data);
    return data;
}

void delay(unsigned long ms) {
    //Implement Delay function
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = (ms * 1000);
    nanosleep(&ts, &ts);
}

long random(long min, long max) {
    long diff = max - min;
    long ret = diff * rand() + min;
    return ret;
}

void SerialSimulator::begin(int baud) {
    //No implementation neccesary - Serial emulation on Linux = standard console
    //
    //Initialize a timestamp for millis calculation - we do this here as well in case SPI
    //isn't used for some reason
    gettimeofday(&RHStartTime, NULL);
}

size_t SerialSimulator::println(const char *s) {
    print(s);
    printf("\n");
}

size_t SerialSimulator::print(const char *s) {
    printf(s);
}

size_t SerialSimulator::print(unsigned int n, int base) {
    if (base == DEC)
        printf("%d", n);
    else if (base == HEX)
        printf("%02x", n);
    else if (base == OCT)
        printf("%o", n);
    // TODO: BIN
}

size_t SerialSimulator::print(char ch) {
    printf("%c", ch);
}

size_t SerialSimulator::println(char ch) {
    printf("%c\n", ch);
}

size_t SerialSimulator::print(unsigned char ch, int base) {
    return print((unsigned int) ch, base);
}

size_t SerialSimulator::println(unsigned char ch, int base) {
    print((unsigned int) ch, base);
    printf("\n");
}

#endif
