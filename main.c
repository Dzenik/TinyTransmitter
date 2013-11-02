#include <util/delay.h>
#include "tools.h"
#include "vwire.h"
#include "EasyTransferVW.h"

#define NODE_ID 0x01
#define PWR_PIN PB2

struct SEND_DATA_STRUCTURE {
  byte device_id;
  unsigned int packet_id;
  byte command;
  unsigned int data;
} mydata;

volatile unsigned int count = 1;

int __attribute__ ((__OS_main__)) main(void) {
  
  osccal();

  cli();

  SET(DDRB, PWR_PIN);
  srandom(1024);
  ET_begin(details(mydata));
  vw_setup(4000);
  
  sei();
  
  for(;;) {
    mydata.device_id = NODE_ID;
    mydata.packet_id = random() % 65354;
    mydata.command = 0x14;
    mydata.data = count;
  
    sbi(PORTB, PWR_PIN);
    ET_sendData();
    cbi(PORTB, PWR_PIN);
    _delay_ms(500);
    count += 1;
  } 

  return 0;
}
