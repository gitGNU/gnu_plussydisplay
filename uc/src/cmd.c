/*
	Plussy Display
	Copyright (C) 2016  Christian Carlowitz <chca@cmesh.de>

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

#include "cmd.h"

#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "usb.h"
#include "animations/common.h"
#include "boot.h"
#include "util.h"

#define usartDataLen (256+1)
static char usartData[usartDataLen];
static char usartData2[usartDataLen];

static int debugCnt = 0;


void cmd_setup(void)
{
	//
}

void cmd_proc(struct plussy_params* p)
{
	void (*comm_write)(char*) = 0;
	int (*comm_get_read)(char*,uint16_t) = 0;


	if(usb_rx_ready())
	{
		comm_write = &usb_write;
		comm_get_read = &usb_get_read;
	}
	else if(usart_rx_ready())
	{
		comm_write = &usart_write;
		comm_get_read = &usart_get_read;
	}

	if(usart_rx_ready() || usb_rx_ready())
	{
		int len = comm_get_read(usartData, usartDataLen);

		if(len < 1)
		{
			comm_write("?");
		}
		else
		{
			int sel = 0;
			switch(usartData[0])
			{
			case 'e': // [e]cho test
				sprintf(usartData, "E%d", debugCnt++);
				comm_write(usartData);
				break;
			case 'b': // [b]rightness scale setting
				sscanf(usartData+1, "%02x", &sel);
				p->brightnessScale = (uint8_t)sel;
				comm_write("B");
				break;
			case 'c': // [c]omputation time
				sprintf(usartData, "C%d", p->compTime);
				comm_write(usartData);
				break;
			case 's': // [s]top animations
				p->animSel = -1;
				memset(p->rgbData, 0, p->rgbDataLen);
				comm_write("S");
				break;
			case 'a': // [a]nimation selection
				sscanf(usartData+1, "%02x", &sel);
				if(sel <= p->animSelMax)
					p->animSel = sel;
				sprintf(usartData, "A%c", p->animSel==sel ? '1':'0');
				comm_write(usartData);
				break;
			case 'l': // [l]ist query
				sscanf(usartData+1, "%02x", &sel);
				sprintf(usartData, "L%s", sel > p->animSelMax ? "" : animTable[sel].name);
				comm_write(usartData);
				break;
			case 'm': // [m]anual led set
				p->animSel = -1;
				sscanf(usartData+1, "%02x", &sel);
				if(sel < (p->rgbDataLen/3))
				{
					int r,g,b;
					sscanf(usartData+3, "%02x%02x%02x", &r, &g, &b);
					p->rgbDataManual[3*sel] = r;
					p->rgbDataManual[3*sel+1] = g;
					p->rgbDataManual[3*sel+2] = b;
				}
				usartData[0] = 'M';
				for(int i = 0; i < p->rgbDataLen; i++)
					sprintf(usartData+1+i*2, "%02x", p->rgbDataManual[i]);
				comm_write(usartData);
				break;
			case 'r': // [r]ead complete led matrix
				usartData[0] = 'R';
				for(int i = 0; i < p->rgbDataLen; i++)
					sprintf(usartData+1+i*2, "%02x", p->rgbDataManual[i]);
				comm_write(usartData);
				break;
			case 'w': // [w]rite complete led matrix
				p->animSel = -1;
				if(len != (1+2*p->rgbDataLen)) // 1 char command, 6 chars per LED
				{
					comm_write("?");
				}
				else
				{
					for(int i = 0; i < (p->rgbDataLen/3); i++)
					{
						int r,g,b;
						sscanf(usartData+3, "%02x%02x%02x", &r, &g, &b);
						p->rgbDataManual[3*sel] = r;
						p->rgbDataManual[3*sel+1] = g;
						p->rgbDataManual[3*sel+2] = b;
					}
					comm_write("W");
				}
				break;
			case '~': // bootloader command
				ascii_decode((uint8_t*)usartData+1, len-1);
				boot_cmd((uint8_t*)usartData+1, (uint8_t*)usartData2, (len-1)/2);
				ascii_encode((uint8_t*)usartData2, len-1);
				usartData2[len-1] = '\0';
				comm_write(usartData2);
				break;
			default:
				comm_write("?");
			}
		}
	}
}
