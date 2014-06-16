//
//  CDGFile.cpp
//  robotKaraoke
//
//  Created by Szymczykowski, Pawel on 6/14/14.
//
//

#include "CDGFile.h"


CDGFile::CDGFile() {
}

int CDGFile::readNext() {
    
    Subcode subcode;
    
    file.read((char*)&subcode, sizeof(Subcode));
    if (file.fail()) {
        cout << "ERROR: Cannot read the file..." << endl;
    }
    
    switch (subcode.instruction & SC_MASK) {

        case 38:
        case 6: // Tile Block (Normal)
            tileBlock(subcode.data);
            break;
        case 30: // Load Color Table (entries 0-7)
            loadCLUT(subcode.data, 0);
            break;
        case 31: // Load Color Table (entries 8-15)
            loadCLUT(subcode.data, 8);
            break;
        default:
            //cout << "Unhandled instruction: " << (int)subcode.instruction << endl;
            break;
    }
}

unsigned char * CDGFile::pixels() {
    return pixelData;
}

int CDGFile::open(const char *filename) {
    file.open(filename, fstream::in | fstream::binary);
    if (file.fail()) {
        cout << "ERROR: Cannot open the file..." << endl;
        exit(0);
    }
}

// RED = 240 0 25
// ORANGE = 255 168 61

int CDGFile::loadCLUT(unsigned char *data, short first) {
    int j=0;
	for (int i=0;i<8;i++) {
        int c = first + i;
		palette[ c ].r = ((data[j]  & SC_MASK) >> 2) * 15;
		palette[ c ].g = (((data[j] & 0x03) << 2) | ((data[j + 1] & SC_MASK) >> 4)) * 15;
		palette[ c ].b = (data[j + 1] & 0x0F) * 15;
		j+=2;
        cout << c << ": " << palette[ c ].r << " " << palette[ c ].g << " " << palette[ c ].b << endl;
	}
}

void CDGFile::setPixel(unsigned int x, unsigned int y, unsigned int c) {
    unsigned int pixelOffset = ( y * 4 * CDG_WIDTH ) + ( x * 4 );
    pixelData[ pixelOffset     ] = palette[ c ].r;
    pixelData[ pixelOffset + 1 ] = palette[ c ].g;
    pixelData[ pixelOffset + 2 ] = palette[ c ].b;
    pixelData[ pixelOffset + 3 ] = 255;
}

int CDGFile::tileBlock(unsigned char *data) {
	short color0 = data[0] & 0x0F;
	short color1 = data[1] & 0x0F;
	short row = data[2] & 0x1F;
	short col = data[3] & 0x3F;
    
	int x_pos = (col * 6) + 10;
	int y_pos = (row * 12) + 12;
	
	for (int y=0; y<12; y++) {
		setPixel(x_pos    , y_pos + y, data[y + 4] & 0x20 ? color1 : color0);
		setPixel(x_pos + 1, y_pos + y, data[y + 4] & 0x10 ? color1 : color0);
		setPixel(x_pos + 2, y_pos + y, data[y + 4] & 0x08 ? color1 : color0);
		setPixel(x_pos + 3, y_pos + y, data[y + 4] & 0x04 ? color1 : color0);
		setPixel(x_pos + 4, y_pos + y, data[y + 4] & 0x02 ? color1 : color0);
		setPixel(x_pos + 5, y_pos + y, data[y + 4] & 0x01 ? color1 : color0);
	}
}