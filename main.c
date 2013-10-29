#include <util/delay.h>
#include "tools.h"
#include "vwire.h"
#include "EasyTransferVW.h"

#define NODE_ID 0x01

struct SEND_DATA_STRUCTURE {
  byte device_id;
  unsigned int packet_id;
  byte command;
  unsigned int data;
} mydata;

volatile unsigned int count = 1;

void init(void) {
  cli();

}

void setup(void) {
  SET(DDRB, PB2);
  srandom(1024);
  ET_begin(details(mydata));
  vw_setup(2000);
}

void loop(void) {
  mydata.device_id = NODE_ID;
  mydata.packet_id = random() % 65354;
  mydata.command = 0x14;
  mydata.data = count;
  
  sbi(PORTB, PB2);
  ET_sendData();
  cbi(PORTB, PB2);
  _delay_ms(1000);
  count += 1;
}

int main(void) {
  
  //OSCCAL = 0x59;

  init();
  
  setup();
  
  sei();
  
  for(;;) {
    loop();
  } 

  return 0;
}
