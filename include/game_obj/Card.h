#ifndef __CARD_H__
#define __CARD_H__
#include "GameObject.h"
#include "Texture.h"
#include "GameEvent.h"
#include "LinkAFinder.h"

class Card;
class CardInfo : public GameObject
{
public:
  int index;
  int compare_id;
  int x;
  int y;
  Card *cPtr;

  virtual void onEvent(LinkA_Event &__event);
  virtual void create();
  virtual void updateInfo();
  virtual void render(Camera *);
  virtual void update(float delta);
};

class LinkCardANode
{
public:
  int x;
  int y;
  int index;
  LinkANodeType nodeType;
  LinkANodeValid nodeStatus = LinkANodeValid::NODE_VALID;
  std::shared_ptr<GameObject> obj;
  virtual std::vector<Connection<Card> *> getAllValidConnection() = 0;
};

class LinkACardConnection : public Connection<Card>
{
public:
  float cost;
  Card *fromNode;
  Card *toNode;

  float getCost();
  Card *getFromNode();
  Card *getToNode();
};

class Card : public GameObject, public LinkCardANode, public _Recipient
{
public:
  CardInfo cardInfo;
  int compare_id;

  Texture *img;
  glm::vec3 PickedColor;
  glm::vec3 NormalColor;
  glm::vec2 postion_delta;
  glm::vec3 record_position;

  std::vector<Connection<Card> *> connections;
  std::vector<Connection<Card> *> validConnections;
  virtual void onEvent(LinkA_Event &__event);
  virtual void create();
  virtual void updateInfo();
  virtual void render(Camera *);
  virtual void update(float delta);
  virtual std::vector<Connection<Card> *> getAllValidConnection();
  virtual std::vector<Connection<Card> *> getAllTargetValidConnection(Card *target);

  virtual bool handleMessage(_LinkAMessage &msg);
};

class LinkCardAGraph : public Graph<Card>
{
private:
  const std::vector<Connection<Card> *> emptyConnections;

public:
  std::vector<Card *> nodeVector;
  void create();
  std::vector<Connection<Card> *> getConnections(Card *fromNode);
  std::vector<Connection<Card> *> getConnections(Card *fromNode, Card *matchNode);

  int getIndex(Card *node);
  int size();
};

#endif // __CARD_H__