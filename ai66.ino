#include "channel.h"

//edit this
#define SERIAL_RATE 4800
#define SERIAL_CONFIG SERIAL_8N1
#define SERIAL_TIMEOUT_MS 300
#define CHANNEL_COUNT 2

//edit this
//for each channel
#define ID1 7
#define ID2 8
#define INTERVAL_MS 500
#define CS1 3
#define CS2 5
#define SCLK 2
#define MISO 4


Channel channels[CHANNEL_COUNT];
PUART puart;

void setup()
{
  Serial.begin(SERIAL_RATE, SERIAL_CONFIG);
  Serial.setTimeout(SERIAL_TIMEOUT_MS);
  puart_init(&puart);
  
  //edit this
  //for each channel
  channel_init(&channels[0], ID1, INTERVAL_MS, CS1, SCLK, MISO);
  channel_init(&channels[1], ID2, INTERVAL_MS, CS2, SCLK, MISO);
}


void loop()
{
	for (int i = 0; i < CHANNEL_COUNT; i++) {
	  channel_control(&channels[i]);
	  puart_server(&puart, channels, CHANNEL_COUNT );
	}
}
