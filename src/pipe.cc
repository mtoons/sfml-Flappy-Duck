#include <pipe.hpp>

extern double dt;
Pipe::Pipe(float x, float y, float distance, const sf::Texture *textureUp,
           const sf::Texture *textureDown) {
  passed = false;
  posX = x;
  posY = y;
  pipeDown = new sf::Sprite(*textureDown);
  pipeDown->scale(sf::Vector2<float>(10., 10.));
  int rounded_x = x/10;
  int rounded_y = y/10;
  int rounded_distance = distance/10;
  pipeDown->setPosition(sf::Vector2<float>(rounded_x*10, (rounded_y*10) - (rounded_distance/2)*10 - 600));

  pipeUp = new sf::Sprite(*textureUp);
  pipeUp->scale(sf::Vector2<float>(10., 10.));
  rounded_x = x/10;
  rounded_y = y/10;
  rounded_distance = distance/10;
  pipeUp->setPosition(sf::Vector2<float>(rounded_x*10, (rounded_y*10) + (rounded_distance / 2)*10));
}

sf::Sprite *Pipe::getSpriteUp() { return pipeDown; }
sf::Sprite *Pipe::getSpriteDown() { return pipeUp; }

void Pipe::move(float x) {
  posX += x;
  const int rounded_x = posX / 10;
  pipeDown->setPosition(sf::Vector2<float>(rounded_x*10, pipeDown->getPosition().y));
  pipeUp->setPosition(sf::Vector2<float>(rounded_x*10, pipeUp->getPosition().y));
}
bool Pipe::colision(float x, float y) {
  bool infX = x >= posX - 75;
  bool supX = x <= posX + 90;
  bool infY = y <= pipeDown->getPosition().y + 1000 - 20;
  bool supY = y >= pipeUp->getPosition().y - 80;
  bool inX = infX && supX;
  bool inY = infY || supY;
  // std::cout << inX << inY << "  y:" << y << '\n';
  return inY && inX;
}

void Pipe::draw(sf::RenderWindow &window) {
  window.draw(*pipeDown);
  window.draw(*pipeUp);
}

float Pipe::getX() { return posX; }

Pipe::~Pipe() {
  delete pipeDown;
  delete pipeUp;
}
