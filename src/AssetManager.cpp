#include "AssetManager.h"

Texture *AssetManager::loadTexture(const char *path, std::string name)
{
    textureMap[name] = new Texture(path);
    return textureMap[name];
}

ShaderProgram *AssetManager::loadShader(const char *vertPath, const char *fragPath, std::string name)
{
    std::cout<<"load shader!"<<std::endl;
    shaderMap[name] = new ShaderProgram(vertPath, fragPath);
    return shaderMap[name];
}

Texture *AssetManager::getTexture(std::string name)
{
    return textureMap[name];
}

ShaderProgram *AssetManager::getShader(std::string name)
{
    return shaderMap[name];
}
