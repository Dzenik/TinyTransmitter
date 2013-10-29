#include "EasyTransferVW.h"
#include "vwire.h"

volatile uint8_t * address;  //address of struct
volatile uint8_t size;       //size of struct

void ET_begin(uint8_t * ptr, uint8_t length) {
  address = ptr;
  size = length;
}

//Sends out struct in binary, with header, length info and checksum
void ET_sendData(){

	//temp storage place
	uint8_t temp_buffer[size+4];

	uint8_t CS = size;
	temp_buffer[0] = 0x06;
	temp_buffer[1] = 0x85;
	temp_buffer[2] = size;
	
	for(int i = 0; i<size; i++){
		CS^=*(address+i);
		temp_buffer[i+3] = (*(address+i));
	}
	temp_buffer[size+3] = CS;
	
	vw_send((uint8_t *)temp_buffer, size+4);
    vw_wait_tx(); // Wait until the whole message is gone

}
