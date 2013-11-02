#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdlib.h>

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

typedef unsigned int word;

#define bit(b) (1UL << (b))

typedef uint8_t boolean;
typedef uint8_t byte;

#ifndef OSCCAL
// program memory location of the internal oscillator "calibration byte"
#define OSCCAL 8192  /* default to last byte of program memory */
#endif

#define _osccal(addr)                                \
        asm volatile (                               \
                "lpm" "\n\t"                         \
                "out 0x31,r0" /* OSCCAL register */  \
                : /* no outputs */                   \
                : "z" ((uint16_t)(addr))             \
                : "r0" /* clobbers */                \
        )
#define osccal() _osccal(OSCCAL) /* calibrate internal RC oscillator */


#endif
