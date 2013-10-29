#ifndef VWIRE_h
#define VWIRE_h

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#undef abs
#undef double
#undef round

#define true 0x1
#define false 0x0

#define SET(x,y) (x|=(1<<y))
#define CLR(x,y) (x&=(~(1<<y)))
#define CHK(x,y) (x & (1<<y))
#define TOG(x,y) (x^=(1<<y))

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

#define membersof(x) (sizeof(x)/sizeof(x[0]))

#define VM_PIN 1

// Maximum number of bytes in a message, counting the byte count and FCS
#define VW_MAX_MESSAGE_LEN 30

// The maximum payload length
#define VW_MAX_PAYLOAD VW_MAX_MESSAGE_LEN-3

// Outgoing message bits grouped as 6-bit words
// 36 alternating 1/0 bits, followed by 12 bits of start symbol
// Followed immediately by the 4-6 bit encoded byte count, 
// message buffer and 2 byte FCS
// Each byte from the byte count on is translated into 2x6-bit words
// Caution, each symbol is transmitted LSBit first, 
// but each byte is transmitted high nybble first
#define VW_HEADER_LEN 8


// Initialise the VirtualWire software, to operate at speed bits per second
// Call this one in your setup() after any vw_set_* calls
// Must call vw_rx_start() before you will get any messages
uint8_t vw_setup(unsigned int speed);

// Return true if the transmitter is active
uint8_t vx_tx_active();

// Block until the transmitter is idle
void vw_wait_tx();

// Send a message with the given length. Returns almost immediately,
// and message will be sent at the right timing by interrupts
// Returns true if the message was accepted for transmissions
// Returns false if the message is too long (>VW_MAX_MESSAGE_LEN - 3)
uint8_t vw_send(unsigned char* buf, unsigned char len);

#endif
