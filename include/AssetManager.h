#ifndef __ASSETMANAGER_H__
#define __ASSETMANAGER_H__

#include <map>
#include <iostream>

#include "Shader.h"
#include "Texture.h"

class AssetManager
{
private:
    std::map<std::string, Texture *> textureMap;
    std::map<std::string, ShaderProgram *> shaderMap;

public:
    Texture *loadTexture(const char *path, std::string name);
    ShaderProgram *loadShader(const char *vertPath, const char *fragPath, std::string name);
    Texture *getTexture(std::string name);
    ShaderProgram *getShader(std::string name);
};

#endif // __ASSETMANAGER_H__