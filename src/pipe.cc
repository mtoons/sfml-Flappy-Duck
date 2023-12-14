#include <iostream>
#include <pipe.hpp>

extern double dt;
Pipe::Pipe(float x, float y, float distance, const sf::Texture *textureUp,
           const sf::Texture *textureDown) {
  passed = false;
  posX = x;
  pipeDown = new sf::Sprite;
  pipeDown->setTexture(*textureDown);
  pipeDown->scale(10, 10);
  pipeDown->setPosition(posX, y - distance / 2 - 600);

  pipeUp = new sf::Sprite;
  pipeUp->setTexture(*textureUp);
  pipeUp->scale(10, 10);
  pipeUp->setPosition(posX, y + distance / 2);
}
sf::Sprite *Pipe::getSpriteUp() { return pipeDown; }
sf::Sprite *Pipe::getSpriteDown() { return pipeUp; }
void Pipe::move(float x) {
  posX += x;
  pipeDown->move(x, 0);
  pipeUp->move(x, 0);
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
