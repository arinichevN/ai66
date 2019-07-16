#include "channel.h"

void channel_init(Channel *item, int id, int interval_ms, int cs, int sclk, int miso){
	item->selected = 0;
	item->id = id;
	item->cs = cs;
	item->sclk = sclk;
	item->miso = miso;
	ton_setInterval(&item->tmr, interval_ms);
	item->state = INIT;
}

int deviceRead(double *result, int sclk, int cs, int miso) {
    uint16_t v=0;
    digitalWrite(cs, LOW);
    delay(1);
    {
        for (int i = 15; i >= 0; i--) {
            digitalWrite(sclk, LOW);
            delay(1);
            if (digitalRead(miso)) {
                v |= (1 << i);
            }
            digitalWrite(sclk, HIGH);
            delay(1);
        }
    }
    digitalWrite(cs, HIGH);
    if (v & 0x4) {
        return 0;
    }
    v >>= 3;
    *result = v * 0.25;
    return 1;
}

int channel_control(Channel *item){
	switch(item->state){
		case RUN:
			if(ton(&item->tmr)){
				ton_reset(&item->tmr);
				double v = 0.0;
				item->output.state = deviceRead(&v, item->sclk, item->cs, item->miso);
				if(item->output.state){
					item->output.value = v;
				}
				item->output.tm = millis();
			}
			break;
		case OFF:
			break;
		case INIT:
			ton_reset(&item->tmr);
			item->output.state = 0;
			item->output.tm = millis();
			pinMode(item->cs, OUTPUT);
			pinMode(item->sclk, OUTPUT); 
			pinMode(item->miso, INPUT);
		    digitalWrite(item->cs, HIGH);
			item->state = RUN;
			break;
		default:
			break;
	}
	return item->state;
}
