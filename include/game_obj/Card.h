#ifndef __CARD_H__
#define __CARD_H__
#include "GameObject.h"
#include "Texture.h"
#include "GameEvent.h"

class Card : public GameObject
{
public:
  int compare_id;
  Texture *img;
  glm::vec3 PickedColor;
  glm::vec3 NormalColor;
  glm::vec2 postion_delta;
  glm::vec3 record_position;

  virtual void onEvent(LinkA_Event &__event);
  virtual void create();
  virtual void render(Camera *);
  virtual void update(float delta);
};

#endif // __CARD_H__