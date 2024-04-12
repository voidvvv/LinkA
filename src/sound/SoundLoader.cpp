#include "sound/SoundLoader.h"

#include <libnyquist/Decoders.h>
#include <libnyquist/Encoders.h>
#include <libnyquist/Common.h>

#include <AL/alext.h>
#include <AL/alut.h>

#include <al/alc.h>
#include <vorbis/vorbisfile.h> // ogg

static bool LoadOGG(const char *name, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
{
    int endian = 0; // 0 for Little-Endian, 1 for Big-Endian
    int bitStream;
    long bytes;
    char array[32768]; // Local fixed size array
    FILE *f;

    f = fopen(name, "rb");

    if (f == NULL)
        return false;

    vorbis_info *pInfo;
    OggVorbis_File oggFile;

    // Try opening the given file
    if (ov_open(f, &oggFile, NULL, 0) != 0)
        return false;

    pInfo = ov_info(&oggFile, -1);

    if (pInfo->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;

    freq = pInfo->rate;

    do
    {
        bytes = ov_read(&oggFile, array, 32768, endian, 2, 1, &bitStream);

        if (bytes < 0)
        {
            // error
            break;
        }

        buffer.insert(buffer.end(), array, array + bytes);
    } while (bytes > 0);

    ov_clear(&oggFile);
    return true;
}

static int
safeToLower(int c)
{
    return isupper(c) ? tolower(c) : c;
}

static int
hasSuffixIgnoringCase(const char *string, const char *suffix)
{
    const char *stringPointer = string;
    const char *suffixPointer = suffix;

    if (suffix[0] == '\0')
    {
        return 1;
    }

    while (*stringPointer != '\0')
    {
        stringPointer++;
    }

    while (*suffixPointer != '\0')
    {
        suffixPointer++;
    }

    if (stringPointer - string < suffixPointer - suffix)
    {
        return 0;
    }

    while (safeToLower(*--suffixPointer) == safeToLower(*--stringPointer))
    {
        if (suffixPointer == suffix)
        {
            return 1;
        }
    }

    return 0;
}

_MUSIC_ *SoundLoader::loadMusicFromFile(const char *fileName)
{
    if (hasSuffixIgnoringCase(fileName, "mp3"))
    {
        return loadMP3(fileName);
    }
    else if (hasSuffixIgnoringCase(fileName, "ogg"))
    {
        return loadOGG(fileName);
    }
    else if (hasSuffixIgnoringCase(fileName, "wav"))
    {
        return loadWAV(fileName);
    }
    else
    {
        return loadOTHER(fileName);
    }
}

_MUSIC_ *SoundLoader::loadMP3(const char *fileName)
{
    nqr::AudioData *data = new nqr::AudioData();
    std::string sFile(fileName);
    auto memory = nqr::ReadFile(sFile);
    loader.Load(data, "mp3", memory.buffer);
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer,
                 AL_FORMAT_STEREO_FLOAT32,
                 data->samples.data(),
                 data->samples.size() * sizeof(float),
                 data->sampleRate);
    _MUSIC_ *musicPtr = new _MUSIC_();
    musicPtr->setBuffer(buffer);
    return musicPtr;
}

_MUSIC_ *SoundLoader::loadOGG(const char *fileName)
{
    std::vector<char> bufferData;
    ALuint bufferID;
    alGenBuffers(1, &bufferID);
    ALenum format;
    ALsizei freq;
    LoadOGG(fileName, bufferData, format, freq);

    // Upload sound data to buffer
    alBufferData(bufferID, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);
    _MUSIC_ *musicPtr = new _MUSIC_();
    musicPtr->setBuffer(bufferID);
    return musicPtr;
}

_MUSIC_ *SoundLoader::loadWAV(const char *fileName)
{
    // use FreeALUT to load wav
    ALuint buffer = alutCreateBufferFromFile(fileName);
    // error = alutGetError(); check error
    _MUSIC_ *musicPtr = new _MUSIC_();
    musicPtr->setBuffer(buffer);
    return musicPtr;
}

_MUSIC_ *SoundLoader::loadOTHER(const char *fileName)
{
    // todo
    return nullptr;
}
