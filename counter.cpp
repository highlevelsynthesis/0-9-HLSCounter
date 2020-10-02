#include "counter.h"



void counter(
		uint4 init_value,
		uint1 init_counter,
		uint2 push_buttons,
		uint4 &leds,
		uint8 &seven_segments_data,
		uint4 &seven_segments_enable) {

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=init_value
#pragma HLS INTERFACE ap_none port=init_counter
#pragma HLS INTERFACE ap_none port=push_buttons
#pragma HLS INTERFACE ap_none port=leds
#pragma HLS INTERFACE ap_none port=seven_segments_data
#pragma HLS INTERFACE ap_none port=seven_segments_enable



	uint1 up_count   = push_buttons[0];
	uint1 down_count = push_buttons[1];
	static int up_pressed   = 0;
	static int down_pressed = 0;

	static uint4 number = 0;

	leds = init_value;

	seven_segments_enable = 0b1110;

	if (init_counter ==1) {
		number = init_value;
	}

	if (up_count == 0b1 && up_pressed == 0) {
		number++;
		if (number == 10)
			number = 0;
		up_pressed = 1000;
	}

	if (up_count == 0b0 &&  up_pressed > 0) {
		up_pressed--;
	}

	if (down_count == 0b1 && down_pressed == 0) {
		number--;
		if (number == 15)
			number = 9;
		down_pressed = 1000;
	}

	if (down_count == 0b0 && down_pressed > 0) {
		down_pressed--;
	}

	seven_segments_data = seven_segment_code[number];


}
