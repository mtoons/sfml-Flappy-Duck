#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Pipe {
  sf::Sprite *pipeDown;
  sf::Sprite *pipeUp;
  float posX;
  float posY;

 public:
  bool passed;
  Pipe(float x, float y, float distance, const sf::Texture *textureUp,
       const sf::Texture *textureDown);
  sf::Sprite *getSpriteUp();
  sf::Sprite *getSpriteDown();
  void move(float x);
  bool colision(sf::Sprite const *sprite);
  void draw(sf::RenderWindow &window);
  float getX();
  ~Pipe();
};
