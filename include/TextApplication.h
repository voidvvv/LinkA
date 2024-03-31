#ifndef __TEXTAPPLICATION_H__
#define __TEXTAPPLICATION_H__
#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Game.h"
#include "Shader.h"
#include "OrthographicCamera.h"

struct Character
{
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    FT_Pos Advance;     // Horizontal offset to advance to next glyph
};

class CharacterManager
{
private:
    FT_Library ft;
    FT_Face face;
    GLuint VAO, VBO;
    friend class Game;
    OrthographicCamera *camera;
    void loadCharater(GLint &ch, FT_Face &face);

public:
    CharacterManager();
    std::map<GLint, Character> CharacterCache;
    // void create(std::string &text);
    void create(const char *file);
    void create();
    // void renderText(ShaderProgram *program, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    void renderText(ShaderProgram *program, std::wstring &text, int size, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};

#endif // __TEXTAPPLICATION_H__