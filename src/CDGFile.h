//
//  CDGFile.h
//  robotKaraoke
//
//  Created by Szymczykowski, Pawel on 6/14/14.
//
//

#ifndef __robotKaraoke__CDGFile__
#define __robotKaraoke__CDGFile__

#include <iostream>
#include <fstream>
using namespace std;

#define SC_MASK     0x3F

#define CDG_WIDTH   300
#define CDG_HEIGHT  216

class CDGFile {
    
    typedef struct {
        unsigned char command;
        unsigned char instruction;
        unsigned char parityQ[2];
        unsigned char data[16];
        unsigned char parityP[4];
    } Subcode;
    
    typedef struct {
        unsigned int r;
        unsigned int g;
        unsigned int b;
    } Color;
    
    unsigned char pixelData[ CDG_WIDTH * CDG_HEIGHT ];
    unsigned char rgbaData[ 4 * CDG_WIDTH * CDG_HEIGHT ];
    long int byteCount = 0;
    fstream file;
    
    void setPixel(unsigned int x, unsigned int y, unsigned int c);
    void xorPixel(unsigned int x, unsigned int y, unsigned int c);
    int loadCLUT(unsigned char *data, short first);
    int tileBlock(unsigned char *data);
    int tileBlockXor(unsigned char *data);
    void memPreset(unsigned char *data);
    void borderPreset(unsigned char *data);
    
public:
    
    Color palette[16];

    CDGFile();
    int open(const char *filename);
    int readNext();
    long int bytesRead();    
    unsigned char *pixels();
    
};

#endif /* defined(__robotKaraoke__CDGFile__) */
