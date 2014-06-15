 /*
  * cdg.h - CD+G player declarations
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

#ifndef __CDG_H__
#define __CDG_H__

#include "gpgraphic.h"
#include "defines.h"

#define SC_MASK 	0x3F
#define SC_CDG_COMMAND 	0x09

#define GP_RGB24(r,g,b) (((((r>>3))&0x1f)<<11)|((((g>>3))&0x1f)<<6)|((((b>>3))&0x1f)<<1))
#define CDG_Pixel(x,y) CDG_screenBuffer[(240 * (x)) + (240 - (y))]

typedef struct 
{
	unsigned char command;
	unsigned char instruction;
	unsigned char parityQ[2];
	unsigned char data[16];
	unsigned char parityP[4];
} SUBCODE;

extern unsigned char CDG_screenBuffer[76800];

void CDG_Handler(SUBCODE * subCode);
void CDG_MemPreset(unsigned char * data);
void CDG_BorderPreset(unsigned char * data);
void CDG_TileBlock(unsigned char * data);
void GpSetPaletteEntry (u8 i, u8 r, u8 g, u8 b);
void CDG_LoadCLUT(unsigned char * data, short first);
void CDG_TileBlockXOR(unsigned char * data);

#endif /*__CDG_H__*/
