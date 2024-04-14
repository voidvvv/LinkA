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
    assetManager->loadShader("./shader/basic/simple.vert", "./shader/basic/simple.frag", "basic");

    // assetManager->loadTexture("C:/Users/voidvvv/Pictures/asset/enhancer_profile.png", "face");

    textManager->create();

    renderer = new SpriteRender(assetManager->getShader("simple"));
    basicRender = new BasicRender(assetManager->getShader("basic"));
    renderer->initRenderData();
    basicRender->initialData();
    setScreen(new MainScreen());

    std::random_device seedDevice;
    this->seed = seedDevice();
    std::cout << "Game init with seed: " << seed << std::endl;
}

InputEvent *LinkAGame::getInputEvent() { return contro; }

void LinkAGame::render()
{
    scn->render();
}

void LinkAGame::update(float &delta)
{
    contro->update(delta);
    scn->update(delta);
}

AssetManager *LinkAGame::getAssetManager()
{
    return this->assetManager;
}

void LinkAGame::renderText(std::wstring &str, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    textManager->renderText(assetManager->getShader("textSimple"), str, str.size(), x, y, scale, color);
}

void LinkAGame::setScreen(Screen *newScn)
{
    if (this->scn != nullptr)
    {
        // std::cout << scn << std::endl;
        this->scn->dispose();
    }
    this->scn = newScn;
    newScn->create();
}

SpriteRender *LinkAGame::getSpriteRender()
{
    return renderer;
}

BasicRender *LinkAGame::getBasicRender()
{
    return basicRender;
}

void LinkAGame::sendEvent(LinkA_Event &event)
{
    scn->sendEvent(event);
}

void LinkAGame::resize(GLint& w, GLint& h)
{
    this->ScreenWidth = w;
    this->ScreenHeight = h;
}

RANDOM_NUM LinkAGame::rand(RANDOM_NUM min, RANDOM_NUM max) {
    std::ranlux48 engine(this->seed);
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(engine);//随机数
}