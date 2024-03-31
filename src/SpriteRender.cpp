#include "SpriteRender.h"

SpriteRender::SpriteRender(ShaderProgram *_shader) : shader(_shader), VAO(0)
{
}

void SpriteRender::DrawSprite(Texture *texture, glm::vec2 position,
                              glm::mat4 projection, glm::mat4 view,
                              glm::vec2 size, GLfloat rotate,
                              glm::vec3 color)
{
    shader->use();
    texture->bind(0);
    if (size.x == 0){
        size.x = texture->width;
    }
    if (size.y == 0) {
        size.y = texture->height;
    }
    

    glm::mat4 model(1.f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader->setUniformMat4("model", model);
    shader->setUniformMat4("projection", projection);
    shader->setUniformMat4("view", view);
    // u_color
    shader->setUniformFloat3("u_color", color.r, color.g, color.b);
    shader->setUniformInt("texture0", 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteRender::initRenderData()
{
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    GLfloat vertices[] = {
        // 位置     // 纹理
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f};
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}
