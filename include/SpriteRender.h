#ifndef __SPRITERENDER_H__
#define __SPRITERENDER_H__
#include "Shader.h"
#include "Texture.h"

class LinkAGame;
class SpriteRender
{
private:
    ShaderProgram *shader;
    GLuint VAO;
    friend class LinkAGame;
    void initRenderData();

public:
    SpriteRender(ShaderProgram *_shader);
    void DrawSprite(Texture* texture, glm::vec2 position,
                    glm::mat4 projection, glm::mat4 view,
                    glm::vec2 size = glm::vec2(0,0), GLfloat rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));
};

#endif // __SPRITERENDER_H__