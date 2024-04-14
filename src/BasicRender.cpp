#include "BasicRender.h"

#define Point GL_POINTS
#define Line GL_LINES
#define Filled GL_TRIANGLES

void BasicRender::setVec3(glm::vec3 v3)
{
    vertex[vIndex++] = v3[0];
    vertex[vIndex++] = v3[1];
    vertex[vIndex++] = v3[2];
    vertexCount++;
}

BasicRender::BasicRender(ShaderProgram *_shader)
    : shader(_shader), VAO(0)
{
    vertexCount = 0;
    vIndex = 0;
}

void BasicRender::initialData()
{

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 600 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    // postion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void BasicRender::drawLine(glm::vec3 start, glm::vec3 end,

                           Camera *camera, glm::vec3 color1, glm::vec3 color2)
{
    vertexCount = 0;
    vIndex = 0;
    // bind matrix
    shader->use();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    shader->setUniformMat4("projection", camera->getProjectionMatrix());
    // shader->setUniformMat4("projection", glm::mat4(1.f));

    shader->setUniformMat4("view", camera->getViewMatrix());
    // shader->setUniformMat4("view", glm::mat4(1.f));

    shader->setUniformMat4("model", glm::mat4(1.f));

    // position
    setVec3(start);
    // setVec3(glm::vec3(0.f));
    setVec3(color1);

    setVec3(end);
    // setVec3(glm::vec3(1.f));
    setVec3(color2);


    glBufferSubData(GL_ARRAY_BUFFER, 0, vIndex * sizeof(float), vertex);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glDrawArrays(GL_LINES, 0, 2);

    glUseProgram(0);
    glBindVertexArray(0);
}

void BasicRender::drawLine(glm::vec2 start, glm::vec2 end, Camera *camera, glm::vec3 color1,
                           glm::vec3 color2)
{
    drawLine(glm::vec3(start, 0.f), glm::vec3(end, 0.f), camera, color1, color2);
}
