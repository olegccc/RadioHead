AM_CFLAGS = --pedantic -Wall -std=c99 -O2
AM_CPPFLAGS = -I../lib/RadioHead -DRASPBERRY_PI
lib_LIBRARIES = libradiohead.a
libradiohead_a_SOURCES = RH_RF95.cpp RHGenericDriver.cpp RHSPIDriver.cpp RHutil/RasPi.cpp RHHardwareSPI.cpp RHGenericSPI.cpp
#libradiohead_a_LIBADD = -lbcm2835