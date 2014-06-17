//
//  KaraokePlayer.cpp
//  robotKaraoke
//
//  Created by Szymczykowski, Pawel on 6/16/14.
//
//

#include "KaraokePlayer.h"

KaraokePlayer::KaraokePlayer() {
    
}

void KaraokePlayer::open(const char *baseFilename) {
    char *filename = (char *) malloc( strlen(baseFilename) + 5 );
    
    // Load the MP3
    sprintf(filename, "%s.%s", baseFilename, "mp3");
    mp3File.loadSound(filename);
    
    // Load the CDG
    sprintf(filename, "%s.%s", baseFilename, "cdg");
    cdgFile.open(filename);
    
    free(filename);
}

void KaraokePlayer::play() {
    mp3File.play();
}

void KaraokePlayer::pause() {
    
}

// The CD+G format takes advantage of the unused channels R thru W.  These unused
// six bits are used to store graphics information. Note that this is an extremely
// thin stream of information.  6 bits per byte * 16 bytes per packet * 4
// packets per sector * 75 sectors per second = 28800 bits per second, or 3.6 K per
// second.  By comparison, a typical 160 x 120 QuickTime movie uses 90K per second.

void KaraokePlayer::update() {
    
    // 24 bytes * 4 packets * 75 sectors = 7200 bytes per second
    long int bytesForPosition = mp3File.getPositionMS() * 7.2;
    while ( cdgFile.bytesRead() <= bytesForPosition )
        cdgFile.readNext();
}

unsigned char * KaraokePlayer::pixels() {
    return cdgFile.pixels();
}


