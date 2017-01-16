/*
 * ad9851.h
 *
 * Created: 27-12-2016 23:20:55
 *  Author: Andreas
 */ 


#ifndef AD9851_H_
#define AD9851_H_

#include "asf.h"

#define CLOCK_IN 20000000
#define CLOCK_MULTIPLIER 6
#define MAX_WORD 4294967295
#define CLOCK_WORD_RATIO (MAX_WORD/(CLOCK_IN*CLOCK_MULTIPLIER))

#define DDS_D0 PIN_PA02
#define DDS_D1 PIN_PA03
#define DDS_D2 PIN_PA04
#define DDS_D3 PIN_PA05
#define DDS_D4 PIN_PA06
#define DDS_D5 PIN_PA07
#define DDS_D6 PIN_PA08
#define DDS_D7 PIN_PA09
#define DDS_W_CLK PIN_PA10
#define DDS_F_UP PIN_PA11
#define DDS_RESET PIN_PB10

void ad9851_init(void);
unsigned int calc_word(double freq);
void put_data_byte(uint8_t word);
void send_word(uint32_t word);


#endif /* AD9851_H_ */