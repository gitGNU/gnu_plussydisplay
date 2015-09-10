/*
	Plussy Display
	Copyright (C) 2015  Christian Carlowitz <chca@cmesh.de>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "common.h"

/*
Default Matrix LED Order:
          19 18
          16 17

  15 14   13 12   11 10
  04 05   06 07   08 09
  
          03 02
          00 01
*/

static uint8_t ledOrder[] = {0,3,6,5,4,15,14,13,16,19,18,17,12,11,10,9,8,7,2,1};
static int cnt = 0;
static uint8_t state = 0;

#define INC 4 // controls speed of animation (default: quarter sine cycle in 2.55/4 secs)

void anim_green(uint8_t* data, uint16_t len)
{
	uint16_t nLeds = len/3;
	
	switch(state)
	{
	case 0:
		for(int i = 0; i < nLeds; i++)
		{
			uint8_t v = 0;
			int tmp = cnt-i*50; // start cycle for each next LED after 50 counts
			if(tmp > 0xff) // cycle is 255 counts long
				v = 0xff;
			else if(tmp > 0)
				v = tmp;
			data[3*ledOrder[i]+0] = 0x00;
			data[3*ledOrder[i]+1] = sin4(v); // sinusodial modulation
			data[3*ledOrder[i]+2] = 0x00;
		}
		if(cnt > (nLeds*50+0xff)) // last LED has full brightness
		{
			state++;
			cnt = 0;
		}
		break;
	default:
		for(int i = 0; i < nLeds; i++)
		{
			data[3*i+0] = 0x00;
			if(state%2)
				data[3*i+1] = sin4(0xff-(uint8_t)cnt); // decrease brightness
			else
				data[3*i+1] = sin4((uint8_t)cnt); // increase brightness
			data[3*i+2] = 0x00;
		}
		if((cnt+INC) > 255) // end of increase/decrease cycle
		{
			state++;
			cnt = 0;
		}
		if(state == 6) // reset after a few cycles
		{
			state = 0;
			cnt = 0;
		}
		break;
	}
	
	cnt+=INC;
}
