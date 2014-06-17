//
//  KaraokePlayer.h
//  robotKaraoke
//
//  Created by Szymczykowski, Pawel on 6/16/14.
//
//

#ifndef __robotKaraoke__KaraokePlayer__
#define __robotKaraoke__KaraokePlayer__

#include <iostream>
#include "ofMain.h"
#include "CDGFile.h"

class KaraokePlayer {
    
    CDGFile cdgFile;
    ofSoundPlayer mp3File;
    
public:

    KaraokePlayer();
    void open(const char *filename);
    void play();
    void pause();
    void update();
    unsigned char *pixels();
    
};



#endif /* defined(__robotKaraoke__KaraokePlayer__) */
