#ifndef __COUNTER_TB_H__
#define __COUNTER_TB_H__


#include "counter.h"

void counter(
		uint4 init_value,
		uint1 init_counter,
		uint2 push_buttons,
		uint4 &leds,
		uint8 &seven_segments_data,
		uint4 &seven_segments_enable);
#endif // __COUNTER_TB_H__
