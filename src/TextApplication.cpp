#include "TextApplication.h"
#include <typeinfo>
#include <locale>
#include <codecvt> // codecvt_utf8
#include "LinkALog.h"

void CharacterManager::loadCharater(GLint &ch, FT_Face &face)
{
    if (CharacterCache.find(ch) != CharacterCache.end())
    {
        return;
    }
    // Load character glyph
    // FT_Load_Glyph
    // FT_Get_Char_Index(face, text[i])
    if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return;
    }
    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer);
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // std::cout << "ch: " << ch << " bind to id: " << texture << std::endl;
    // Now store character for later use
    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x};
    // CharacterCache.insert(std::pair<FT_ULong, Character>(ch, character));
    CharacterCache[ch] = character;
}

CharacterManager::CharacterManager()
{
}

// void CharacterManager::create(std::string &text)
// {
//     FT_Library ft;
//     camera = new OrthographicCamera(800, 600);
//     // All functions return a value different than 0 whenever an error occurred
//     if (FT_Init_FreeType(&ft))
//         std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//     FT_Face face;
//     if (FT_New_Face(ft, "C:/Windows/Fonts/BRLNSDB.TTF", 0, &face))
//         std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

//     // Set size to load glyphs as
//     FT_Set_Pixel_Sizes(face, 0, 48);
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

//     for (int x = 0; x < text.size(); x++)
//     {
//         char c = text[x];

//         // FT_ULong
//         loadCharater(c, face);
//     }

//     FT_Done_Face(face);
//     FT_Done_FreeType(ft);
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }

void CharacterManager::create(const char *file)
{

    camera = new OrthographicCamera(800, 600);
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    if (FT_New_Face(ft, file, 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 45);
    // FT_Select_Charmap(face, ft_encoding_unicode);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (int x = 0; x < 128; x++)
    {

        loadCharater(x, face);
    }

    // FT_Done_Face(face);
    // FT_Done_FreeType(ft);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CharacterManager::create()
{
    // "C:/Windows/Fonts/SIMLI.TTF"
    create("C:/Windows/Fonts/msyh.ttc");
}

void CharacterManager::renderText(ShaderProgram *program, std::wstring &text, int size, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    // Activate corresponding render state
    program->use();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUniform3f(glGetUniformLocation(program->ID, "u_color"), color.x, color.y, color.z);
    program->setUniformMat4("projection", camera->projection);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (int i = 0; i < size; i++)
    {
        GLint s = static_cast<int>(text[i]);
        if (CharacterCache.find(s) == CharacterCache.end())
        {
            loadCharater(s, face);
        }
        Character ch = CharacterCache[s];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            {xpos, ypos + h, 0.0, 0.0},
            {xpos, ypos, 0.0, 1.0},
            {xpos + w, ypos, 1.0, 1.0},

            {xpos, ypos + h, 0.0, 0.0},
            {xpos + w, ypos, 1.0, 1.0},
            {xpos + w, ypos + h, 1.0, 0.0}};
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        // text++;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glUseProgram(0);
}
