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
    byteCount += file.gcount();
    
    switch (subcode.instruction & SC_MASK) {

        case 1: // Memory Preset (set background color)
            memPreset(subcode.data);
            break;
		case 2: // Border Preset
            cout << "TODO: Border Preset" << endl;
            break;
        case 6: // Tile Block (Normal)
            tileBlock(subcode.data);
            break;
        case 20: // Scroll Preset
            cout << "TODO: Scroll Preset" << endl;
            break;
        case 24: // Scroll Copy
            cout << "TODO: Scroll Copy" << endl;
            break;
        case 28: // Define Transparent Color
            cout << "TODO: Define Transparent Color" << endl;
            break;
        case 30: // Load Color Table (entries 0-7)
            loadCLUT(subcode.data, 0);
            break;
        case 31: // Load Color Table (entries 8-15)
            loadCLUT(subcode.data, 8);
            break;
        case 38:
            tileBlockXor(subcode.data);
            break;
        default:
            cout << "Unhandled instruction: " << (int)subcode.instruction << endl;
            break;
    }
}

long int CDGFile::bytesRead() {
    return byteCount;
}

void CDGFile::setPixel(unsigned int x, unsigned int y, unsigned int c) {
    pixelData[ (y * CDG_WIDTH) + x ] = c;
}

void CDGFile::xorPixel(unsigned int x, unsigned int y, unsigned int c) {
    pixelData[ (y * CDG_WIDTH) + x ] ^= c;
}

unsigned char * CDGFile::pixels() {
    int j = 0;
    for (int i=0;i<CDG_WIDTH*CDG_HEIGHT;i++) {
        rgbaData[j++] = palette[ pixelData[i] ].r;
        rgbaData[j++] = palette[ pixelData[i] ].g;
        rgbaData[j++] = palette[ pixelData[i] ].b;
        rgbaData[j++] = 255;
    }
    return rgbaData;
}

int CDGFile::open(const char *filename) {
    file.open(filename, fstream::in | fstream::binary);
    if (file.fail()) {
        cout << "ERROR: Cannot open the file..." << endl;
        exit(0);
    }
}

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

void CDGFile::borderPreset(unsigned char *data) {
    //    The border area is the area contained with a
    //    rectangle defined by (0,0,300,216) minus the interior pixels which are contained
    //    within a rectangle defined by (6,12,294,204).

}

void CDGFile::memPreset(unsigned char *data) {
    int color = data[0] & SC_MASK;
    short repeat = data[1] & SC_MASK;
	if (repeat == 0) {
		for (int x=0;x<CDG_WIDTH;x++)
			for (int y=0;y<CDG_HEIGHT;y++)
				setPixel( x, y, color );
	}
}

int CDGFile::tileBlock(unsigned char *data) {
	short color0 = data[0] & 0x0F;
	short color1 = data[1] & 0x0F;
	short row = data[2] & 0x1F;
	short col = data[3] & 0x3F;
	int x_pos = (col * 6);
	int y_pos = (row * 12);
    
	for (int y=0; y<12; y++) {
		setPixel(x_pos    , y_pos + y, data[y + 4] & 0x20 ? color1 : color0);
		setPixel(x_pos + 1, y_pos + y, data[y + 4] & 0x10 ? color1 : color0);
		setPixel(x_pos + 2, y_pos + y, data[y + 4] & 0x08 ? color1 : color0);
		setPixel(x_pos + 3, y_pos + y, data[y + 4] & 0x04 ? color1 : color0);
		setPixel(x_pos + 4, y_pos + y, data[y + 4] & 0x02 ? color1 : color0);
		setPixel(x_pos + 5, y_pos + y, data[y + 4] & 0x01 ? color1 : color0);
	}
}

int CDGFile::tileBlockXor(unsigned char *data) {
	short color0 = data[0] & 0x0F;
	short color1 = data[1] & 0x0F;
	short row = data[2] & 0x1F;
	short col = data[3] & 0x3F;
	int x_pos = (col * 6);
	int y_pos = (row * 12);
    
	for (int y=0; y<12; y++) {
		xorPixel(x_pos    , y_pos + y, data[y + 4] & 0x20 ? color1 : color0);
		xorPixel(x_pos + 1, y_pos + y, data[y + 4] & 0x10 ? color1 : color0);
		xorPixel(x_pos + 2, y_pos + y, data[y + 4] & 0x08 ? color1 : color0);
		xorPixel(x_pos + 3, y_pos + y, data[y + 4] & 0x04 ? color1 : color0);
		xorPixel(x_pos + 4, y_pos + y, data[y + 4] & 0x02 ? color1 : color0);
		xorPixel(x_pos + 5, y_pos + y, data[y + 4] & 0x01 ? color1 : color0);
	}
}