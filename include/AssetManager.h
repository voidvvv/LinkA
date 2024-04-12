#ifndef __ASSETMANAGER_H__
#define __ASSETMANAGER_H__

#include <map>
#include <iostream>

#include "sound/SoundLoader.h"
#include "Shader.h"
#include "Texture.h"

class AssetManager
{
private:
    std::map<std::string, Texture *> textureMap;
    std::map<std::string, ShaderProgram *> shaderMap;
    std::map<std::string, _MUSIC_ *> musicMap;
    SoundLoader musicLoader;
public:
    Texture *loadTexture(const char *path, std::string name);
    ShaderProgram *loadShader(const char *vertPath, const char *fragPath, std::string name);
    _MUSIC_ *loadMusic(const char *filePath, std::string name);
    Texture *getTexture(std::string name);
    ShaderProgram *getShader(std::string name);
    _MUSIC_ *getMusic(std::string name);
};

#endif // __ASSETMANAGER_H__