#include "LinkAGame.h"
#include "MainScreen.h"



void LinkAGame::create()
{
    contro = new InputEvent();
    assetManager = new AssetManager();
    textManager = new CharacterManager();
    
    // init asset
    assetManager->loadShader("./shader/simple/simple.vert", "./shader/simple/simple.frag", "simple");
    assetManager->loadShader("./shader/text_simple/text.vert", "./shader/text_simple/text.frag", "textSimple");


    assetManager->loadTexture("C:/Users/voidvvv/Pictures/asset/enhancer_profile.png", "face");

    // load font and glyph
    std::wstring texts = L"abcABC我爱C++++中，真开心哈哈哈";
    textManager->create(texts);

    renderer = new SpriteRender(assetManager->getShader("simple"));
    renderer->initRenderData();
    setScreen(new MainScreen());
}

InputEvent *LinkAGame::getInputEvent() { return contro; }

void LinkAGame::render()
{
    scn->render();
    std::wstring c = L"abcABC我爱C++++中，真开心哈哈哈";

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

void LinkAGame::setScreen(Screen* newScn)
{
    if (this->scn != nullptr){
        std::cout << scn << std::endl;
        this->scn->dispose();
    }
    this->scn = newScn;
    newScn->create();
}

SpriteRender* LinkAGame::getSpriteRender()
{
    return renderer;
}

void LinkAGame::sendEvent(LinkA_Event& event)
{
    scn->sendEvent(event);
}
