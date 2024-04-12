#include "sound/SoundManager.h"


static void playSource(ALuint source)
{
    if (source == 0)
    {
        return;
    }
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state == AL_INITIAL || state == AL_STOPPED || state == AL_PAUSED)
    {
        alSourcePlay(source);
    }
}

static void forcePlaySource(ALuint source)
{
    if (source == 0)
    {
        return;
    }
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state == AL_INITIAL || state == AL_STOPPED || state == AL_PAUSED)
    {
        alSourcePlay(source);
    }
    else if (state == AL_PLAYING)
    {
        alSourceStop(source);
        alSourcePlay(source);
    }
}

static void stopSource(ALuint source)
{
    if (source == 0)
    {
        return;
    }
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state == AL_PLAYING)
    {
        alSourceStop(source);
    }
}

void SoundPlayer::create()
{
    alutInit(NULL, NULL);
    ALuint *source = new ALuint[21];
    alGenSources(21, source);
    for (int x = 0; x < 20; x++)
    {
        sourceList.push_back(source[x]);
    }
    bgmSource = source[20];
    alSourcei(bgmSource, AL_LOOPING, AL_TRUE);
}
void SoundPlayer::play(_MUSIC_ *music)
{
    if (music->getCurrentSource() > 0)
    {
        playSource(music->getCurrentSource());
    }
    else if (sourceList.size() > 0)
    {
        bindMusic(music);
        playSource(music->getCurrentSource());
    }
    else
    {
        // do nothing, may be add to a queue
    }
}

void SoundPlayer::playBgm(_MUSIC_ *music)
{
    if (music->getCurrentSource() != bgmSource)
    {
        stopSource(music->getCurrentSource());
        sourceList.push_back(music->getCurrentSource());

        music->setCurrentSource(bgmSource);
        stopSource(bgmSource);

        alSourcei(bgmSource, AL_BUFFER, music->getBuffer());
    }
    forcePlaySource(bgmSource);
}

void SoundPlayer::update()
{
    // foreach running source,
    auto it = runningSource.begin();
    while (it != runningSource.end())
    {
        ALuint source = (*it).first;
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        ALint loopState;
        alGetSourcei(source, AL_LOOPING, &loopState);
        if (loopState == AL_FALSE && (state == AL_STOPPED))
        {
            _MUSIC_ *music = (*it).second;
            music->setCurrentSource(0);

            it = runningSource.erase(it);
            alSourcei(source, AL_BUFFER, 0);
            sourceList.push_back(source);
        }
        else
        {
            it++;
        }
    }
}

void SoundPlayer::bindMusic(_MUSIC_ *music)
{
    if (sourceList.size() == 0)
        return ;
    ALuint source = sourceList.back();
    sourceList.pop_back();
    runningSource[source] = music;
    alSourcei(source, AL_BUFFER, music->getBuffer());
    music->setCurrentSource(source);
}

ALuint LinkA_Music::getBuffer()
{
    return this->buffer;
}

ALuint LinkA_Music::getCurrentSource()
{
    return this->currentSource;
}

void LinkA_Music::setBuffer(ALuint buffer) {
    this->buffer = buffer;
}
void LinkA_Music::setCurrentSource(ALuint currentSource)
{
    this->currentSource = currentSource;
}

LinkA_Music::dispose()
{
    stopSource(this->currentSource);
    alDeleteBuffers(1,&this->buffer);
}
