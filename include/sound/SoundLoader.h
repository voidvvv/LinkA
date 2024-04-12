#ifndef __SOUNDLOADER_H__
#define __SOUNDLOADER_H__

#include "sound/SoundManager.h"
#include <libnyquist/Decoders.h>

class SoundLoader
{
    nqr::NyquistIO loader; // for mp3 or others 
    
public:
    _MUSIC_ *loadMusicFromFile(const char *fileName);
    _MUSIC_ *loadMP3(const char *fileName);
    _MUSIC_ *loadOGG(const char *fileName);
    _MUSIC_ *loadWAV(const char *fileName);
    _MUSIC_ *loadOTHER(const char *fileName);
};

#endif // __SOUNDLOADER_H__