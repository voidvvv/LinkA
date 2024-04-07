#include "game_obj/Card.h"
#include "ObjUtil.h"
#include <iostream>

extern _LinkAGameEvents *events;

void Card::onEvent(LinkA_Event &event)
{
    if (this->status == GAME_STATUS::INVALID)
        return; // if invalid , do nothing
    if (event.type == LinkA_EventType::MOUSE_PRESS)
    {
        if (contain(this, event))
        {
            // send message
            events->sendMessaage(_CARD_SELECTED, this, NULL, &(this->cardInfo));
        }
    }
    else if (event.type == LinkA_EventType::MOUSE_RELEASE)
    {
    }
    else if (event.type == LinkA_EventType::MOUSE_MOVE)
    {
    }
}

void Card::create()
{
    std::stringstream ss;
    ss << "card" << compare_id;
    this->PickedColor.x = this->PickedColor.y = this->PickedColor.z = 0.5;
    this->NormalColor.x = this->NormalColor.y = this->NormalColor.z = 1.f;
    // init img
    img = game->getAssetManager()->getTexture(ss.str());
    size = glm::vec2(50, 50);
    updateInfo();
    events->registListerner(_CARD_SUCCESS_MATCH,this);
}

void Card::updateInfo()
{
    this->cardInfo.compare_id = this->compare_id;
    this->cardInfo.index = this->index;
    this->cardInfo.cPtr = this;
}
void Card::render(Camera *cam)
{
    if (this->status == GAME_STATUS::INVALID)
        return; // if invalid , do nothing

    glm::vec3 color = NormalColor;
    if (this->status == Game_obj_status::PICKED)
    {
        color = PickedColor;
    }
    glm::mat4 projection = cam->getProjectionMatrix();
    glm::mat4 view = cam->getViewMatrix();
    game->getSpriteRender()->DrawSprite(img, position, projection, view, size, 0.f, color);
}

void Card::update(float delta)
{
    if (this->status == GAME_STATUS::INVALID)
        return; // if invalid , do nothing
}

std::vector<Connection<Card> *> Card::getAllValidConnection()
{
    validConnections.clear();
    for (int x = 0; x < connections.size(); x++)
    {
        if (connections[x]->getFromNode()->nodeStatus == LinkANodeValid::NODE_VALID && connections[x]->getToNode()->nodeStatus == LinkANodeValid::NODE_INVALID)
            validConnections.push_back(connections[x]);
    }
    return validConnections;
}
// std::vector<Connection<Card> *> getAllTargetValidConnection(Card *target)
std::vector<Connection<Card> *> Card::getAllTargetValidConnection(Card *target)
{
    validConnections.clear();
    for (int x = 0; x < connections.size(); x++)
    {
        if ((connections[x]->getToNode() == target) || (connections[x]->getToNode()->nodeStatus == LinkANodeValid::NODE_INVALID))
            validConnections.push_back(connections[x]);
    }
    return validConnections;
}

void CardInfo::onEvent(LinkA_Event &__event){};
void CardInfo::create(){};
void CardInfo::updateInfo(){};
void CardInfo::render(Camera *){};
void CardInfo::update(float delta){};

// recipient
bool Card::handleMessage(_LinkAMessage &msg){
    if (msg.messageType == _CARD_SUCCESS_MATCH) {
        std::cout << "invalid" << std::endl;
        this->status = Game_obj_status::INVALID;
        this->nodeStatus = LinkANodeValid::NODE_INVALID;
    }
};

// card graph

std::vector<Connection<Card> *> LinkCardAGraph::getConnections(Card *fromNode)
{
    typename std::vector<Card*>::iterator it =
        std::find(this->nodeVector.begin(), this->nodeVector.end(), fromNode);
    if (it == this->nodeVector.end()){
        return emptyConnections;
    }
    return (*it)->getAllValidConnection();
}
//   std::vector<Connection<Card> *> getConnections(Card *fromNode, Card *matchNode);
std::vector<Connection<Card> *> LinkCardAGraph::getConnections(Card *fromNode, Card *matchNode)
{
    typename std::vector<Card*>::iterator it =
        std::find(this->nodeVector.begin(), this->nodeVector.end(), fromNode);
    if (it == this->nodeVector.end()){
        return emptyConnections;
    }
    return (*it)->getAllTargetValidConnection(matchNode);
}

int LinkCardAGraph::getIndex(Card *node)
{
    return node->index;
};
int LinkCardAGraph::size()
{
    return this->nodeVector.size();
};

void LinkCardAGraph::create(){
    this->nodeVector.clear();
};

// connection 
Card *LinkACardConnection::getFromNode()
{
    return this->fromNode;
}

Card *LinkACardConnection::getToNode()
{
    return this->toNode;
}

float LinkACardConnection::getCost()
{
    return 1;
}