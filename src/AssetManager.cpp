#include "AssetManager.h"

Texture *AssetManager::loadTexture(const char *path, std::string name)
{
    if (textureMap[name] != NULL) {
        delete textureMap[name];
    }
    textureMap[name] = new Texture(path);
    return textureMap[name];
}

ShaderProgram *AssetManager::loadShader(const char *vertPath, const char *fragPath, std::string name)
{
    std::cout<<"load shader!"<<std::endl;
    shaderMap[name] = new ShaderProgram(vertPath, fragPath);
    return shaderMap[name];
}

_MUSIC_ *AssetManager::loadMusic(const char *filePath, std::string name)
{
    _MUSIC_ * music = musicLoader.loadMusicFromFile(filePath);
    if (music!=nullptr){
        musicMap[name] = music;
    }
    return music;
}

Texture *AssetManager::getTexture(std::string name)
{
    return textureMap[name];
}

ShaderProgram *AssetManager::getShader(std::string name)
{
    return shaderMap[name];
}

_MUSIC_ *AssetManager::getMusic(std::string name)
{
    return musicMap[name];
}
