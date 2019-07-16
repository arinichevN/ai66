#ifndef CHANNEL_H
#define CHANNEL_H

#include "common.h"
#include "ton.h"
#include "puart.h"

struct Channel{
	int id;
	int cs;
	int sclk;
	int miso;
	FTS output;
	Ton tmr;
	int state;
    int selected;
    
};

extern void channel_init(Channel *item, int id, int interval_ms, int cs, int sck, int so);

extern int channel_control(Channel *item);

#endif 
