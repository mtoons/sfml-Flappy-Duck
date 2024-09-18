#pragma once
#include <SFML/Graphics.hpp>

class Player {
  public:
  float x, y;
  float velocity;
  sf::Sprite sprite;

  Player(sf::Sprite sprite);
  void update();
};
