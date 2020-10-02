/************************************************
Copyright (c) 2020, Mohammad Hosseinabady
All rights reserved.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. // Copyright (c) 2020, Mohammad Hosseinabady.
************************************************/
#include "counter-tb.h"

void counter(
		uint5 push_buttons,
		uint8 &seven_segments_data,
		uint4 &seven_segments_enable);




int main() {

	int status = 0;
	uint2 push_buttons;
	uint8 seven_segments_data_hw;
	uint4 seven_segments_enable_hw;
	uint4 leds_hw;
	uint1 init_counter;
	uint4 init_value;


	uint4 leds_sw;
	uint8 seven_segments_data_sw;
	uint4 seven_segments_enable_sw;
	unsigned int software_counter=0;

	unsigned int button_pressed = 0;
	push_buttons = 0b10;

	for (int i = 0; (i < 10) && (status == 0) ; i++) {
		init_value = (uint4) i;

		for (int j = 0; (j < 2000) && (status == 0); j++) {
			if (j == 0) {
				init_counter = 1;
				software_counter = init_value;
			} else {
				init_counter = 0;
			}
			bool r = rand() % 2;
			if (button_pressed == 0) {
				button_pressed = 1000;
				if (r) {
					push_buttons = 0b01;
					if (software_counter == 9)
						software_counter = 0;
					else
						software_counter++;
				} else {
					push_buttons = 0b10;
					if (software_counter == 0)
						software_counter = 9;
					else
						software_counter--;
				}
			} else {
				button_pressed--;
				push_buttons = 0b00;
			}
			software_counter=software_counter%10;
			counter(init_value, init_counter, push_buttons, leds_hw, seven_segments_data_hw, seven_segments_enable_hw);

			seven_segments_data_sw   = seven_segment_code[software_counter];
			seven_segments_enable_sw = 0b1110;
			leds_sw                  =  init_value;

			if (    (seven_segments_data_hw != seven_segments_data_sw)
				 || (seven_segments_enable_hw != seven_segments_enable_sw)
				 || (leds_hw != leds_sw)
				)
			{
				status = 1;
				std::cout << " Error at "
						  << " software_counter = "
						  << software_counter
						  << " seven_segments_data_hw = " << seven_segments_data_hw.to_string()
						  << " seven_segments_data_sw = " << seven_segments_data_sw.to_string()
						  << " seven_segments_enable_hw = " << seven_segments_enable_hw.to_string()
						  << " seven_segments_enable_sw = " << seven_segments_enable_sw.to_string()
						  << " leds_hw = " << leds_hw.to_string()
						  << " leds_sw = " << leds_sw.to_string()
						  << std::endl;

			}
		}
	}



	if (status == 0) {
		std::cout << "Test Passed!" << std::endl;
	} else {
		std::cout << "Test Failed!" << std::endl;
	}



	return status;
}
