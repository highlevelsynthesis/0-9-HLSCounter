#ifndef __COUNTER_H__
#define __COUNTER_H__

#include <ap_int.h>


typedef ap_uint<8> uint8;
typedef ap_uint<5> uint5;
typedef ap_uint<4> uint4;
typedef ap_uint<2> uint2;
typedef ap_uint<1> uint1;

const uint8 seven_segment_code[10] = {
		0b11000000,
		0b11111001,
		0b10100100,
		0b10110000,
		0b10011001,
		0b10010010,
		0b10000010,
		0b11111000,
		0b10000000,
		0b10010000
};

#endif //__COUNTER_H__
