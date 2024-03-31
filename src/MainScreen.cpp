#include "MainScreen.h"
#include <iostream>
#include "Game.h"

#include "miscellaneous.h"
#include "Shader.h"

extern Game *game;

MainScreen::MainScreen()
{
}

void MainScreen::create()
{
    float vertexArr[] = {
        // 位置     // 纹理
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f};
    camera = new OrthographicCamera(SCREEN_WIDTH, SCREEN_HEIGH);
    face = game->getAssetManager()->getTexture("face");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArr), vertexArr, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void MainScreen::render()
{
    glClearColor(0.56f, 0, 0.56f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model(1.f);
    model = glm::scale(model, glm::vec3(250, 250, 1));
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();

    ShaderProgram *shader = game->getAssetManager()->getShader("simple");

    shader->use();
    glBindVertexArray(VAO);
    face->bind(0);

    shader->setUniformInt("texture0", 0);
    shader->setUniformFloat3("u_color", 1, 1, 1);
    shader->setUniformMat4("model", model);
    shader->setUniformMat4("view", view);

    shader->setUniformMat4("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void MainScreen::update(float delta)
{
}
