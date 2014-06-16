 /*
  * cdg.c - CD+G player handler functions
  * Copyright (c)2003 Pawel Szymczykowski <pawel@makenai.net>
  *
  *
  * This is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2 of the License, or
  * (at your option) any later version.
  *
  * It is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with Foobar; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  */

#include "cdg.h"

void CDG_Handler(SUBCODE * subCode)
{
	switch (subCode->instruction & SC_MASK)
	{
		case 1: // Memory Preset
			CDG_MemPreset(subCode->data);
		break;

		case 2: // Border Preset
			CDG_BorderPreset(subCode->data);
		break;

		case 6: // Tile Block (Normal)
			CDG_TileBlock(subCode->data);
		break;

		case 20: // Scroll Preset
	
			// I have no idea how this is supposed to work.. I
			// need to find a CD+G subcode dump that utilizes
			// this feature.
		
		break;

		case 24: // Scroll Copy

			// Ditto on the above Scroll Preset comment
		
		break;

		case 28: // Define Transparent Color

			// Presumably, this is not very useful unless we do
			// video overlays in a future version.
		
		break;

		case 30: // Load Color Table (entries 0-7)
			CDG_LoadCLUT(subCode->data, 0);
		break;

		case 31: // Load Color Table (entries 8-15)
			CDG_LoadCLUT(subCode->data, 8);
		break;

		case 38: // Tile Block (XOR)
			CDG_TileBlockXOR(subCode->data);
		break;
	}
}

void CDG_TileBlock(unsigned char * data)
{
	short color0 = data[0] & 0x0F;
	short color1 = data[1] & 0x0F;
	short row = data[2] & 0x1F;
	short col = data[3] & 0x3F;

	int x_pos = (col * 6) + 10;
	int y_pos = (row * 12) + 12;
	
	for (int y=0; y<12; y++)
	{
		CDG_Pixel(x_pos    , y_pos + y) = data[y + 4] & 0x20 ? color1 : color0;
		CDG_Pixel(x_pos + 1, y_pos + y) = data[y + 4] & 0x10 ? color1 : color0;
		CDG_Pixel(x_pos + 2, y_pos + y) = data[y + 4] & 0x08 ? color1 : color0;
		CDG_Pixel(x_pos + 3, y_pos + y) = data[y + 4] & 0x04 ? color1 : color0;
		CDG_Pixel(x_pos + 4, y_pos + y) = data[y + 4] & 0x02 ? color1 : color0;
		CDG_Pixel(x_pos + 5, y_pos + y) = data[y + 4] & 0x01 ? color1 : color0;
	}
}

void CDG_TileBlockXOR(unsigned char * data)
{
	short color0 = data[0] & 0x0F;
	short color1 = data[1] & 0x0F;
	short row = data[2] & 0x1F;
	short col = data[3] & 0x3F;

	int x_pos = (col * 6) + 10;
	int y_pos = (row * 12) + 12;

	for (int y=0; y<12; y++)
	{
		CDG_Pixel(x_pos    , y_pos + y) ^= data[y + 4] & 0x20 ? color1 : color0;
		CDG_Pixel(x_pos + 1, y_pos + y) ^= data[y + 4] & 0x10 ? color1 : color0;
		CDG_Pixel(x_pos + 2, y_pos + y) ^= data[y + 4] & 0x08 ? color1 : color0;
		CDG_Pixel(x_pos + 3, y_pos + y) ^= data[y + 4] & 0x04 ? color1 : color0;
		CDG_Pixel(x_pos + 4, y_pos + y) ^= data[y + 4] & 0x02 ? color1 : color0;
		CDG_Pixel(x_pos + 5, y_pos + y) ^= data[y + 4] & 0x01 ? color1 : color0;
	}
}

void CDG_MemPreset(unsigned char * data)
{
	int color = data[0] & SC_MASK;
	short repeat = data[1] & SC_MASK;

	if (repeat == 0)
	{
		for (int j=2400;j<74400;j+=240) 
			for (int y=12;y<228;y++)
				CDG_screenBuffer[j + y] = color;
	}
}

void CDG_BorderPreset(unsigned char * data)
{
	short color = data[0] & SC_MASK;

	for (int i=0;i<2400;i++)
		CDG_screenBuffer[i] = color;
	
	for (int j=2400;j<74400;j+=240)
	{
		for (int y=228;y<240;y++)
			CDG_screenBuffer[j + y] = color;

		for (int y=0;y<12;y++)
			CDG_screenBuffer[j + y] = color;
	}
	
	for (int i=74400;i<76800;i++)
		CDG_screenBuffer[i] = color;
}
