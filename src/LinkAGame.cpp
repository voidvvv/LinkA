#include "LinkAGame.h"
#include "MainScreen.h"

LinkAGame::LinkAGame()
{
}

void LinkAGame::create()
{
    contro = new InputEvent();
    scn = new MainScreen();
    assetManager = new AssetManager();
    textManager = new CharacterManager();
    // init asset
    assetManager->loadShader("./shader/simple/simple.vert", "./shader/simple/simple.frag", "simple");
    std::cout << " =============== " << std::endl;
    assetManager->loadShader("./shader/text_simple/text.vert", "./shader/text_simple/text.frag", "textSimple");

    assetManager->loadTexture("C:/Users/voidvvv/Pictures/asset/enhancer_profile.png", "face");
    std::wstring c = L"abcABC我爱C+，真开心饕餮哈哈哈";
    
    textManager->create(c);

    scn->create();
}

InputEvent *LinkAGame::getInputEvent() { return contro; }

void LinkAGame::render()
{
    scn->render();
    std::wstring c = L"abcABC我爱C++++，真开心哈哈哈";

    // std::string s = "ABCDEFG我爱你";
    // renderText(,50,50,1,glm::vec3(1,1,1));
    renderText(c,100,100,1,glm::vec3(1.0,0.5,0.5));
}


void LinkAGame::update(float &delta)
{
    scn->update(delta);
}

AssetManager *LinkAGame::getAssetManager()
{
    return this->assetManager;
}

void LinkAGame::renderText(std::wstring& str, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    textManager->renderText(assetManager->getShader("textSimple"), str,str.size(), x, y, scale, color);
}
