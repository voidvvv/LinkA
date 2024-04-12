#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include <ctype.h>
#include <vector>
#include <map>

#include <AL/alut.h>

#define _MUSIC_ LinkA_Music

class LinkA_Music
{
private:
    ALuint buffer;
    ALuint currentSource;

public:
    virtual ALuint getBuffer();
    virtual ALuint getCurrentSource();
    virtual void setBuffer(ALuint);
    virtual void setCurrentSource(ALuint);
    virtual dispose();
};

// 管理音频的工具类
class SoundPlayer
{
public:
    ALuint bgmSource; // always should have a bgm source
    virtual void create();
    virtual void play(_MUSIC_ *music);
    virtual void playBgm(_MUSIC_ *music);
    virtual void update();

private:
    std::vector<ALuint> sourceList;
    std::map<ALuint, _MUSIC_ *> runningSource;
    virtual void bindMusic(_MUSIC_ *);
};

#endif // __SOUNDMANAGER_H__