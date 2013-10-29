#ifndef EasyTransferVirtualWire_h
#define EasyTransferVirtualWire_h

//make it a little prettier on the front end. 
#define details(name) (byte*)&name,sizeof(name)

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

void ET_begin(uint8_t *, uint8_t);
void ET_sendData();

#endif
