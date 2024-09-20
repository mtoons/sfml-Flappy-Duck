#include <pipe.hpp>

extern double dt;
Pipe::Pipe(float x, float y, float distance, const sf::Texture *textureUp,
           const sf::Texture *textureDown) {
  passed = false;
  posX = x;
  posY = y;
  pipeDown = new sf::Sprite(*textureDown);
  pipeDown->scale(sf::Vector2<float>(PIXEL_MULTIPLIER, PIXEL_MULTIPLIER));
  pipeUp = new sf::Sprite(*textureUp);
  pipeUp->scale(sf::Vector2<float>(PIXEL_MULTIPLIER, PIXEL_MULTIPLIER));
  if (IS_PIXEL) {
    int rounded_x = x / PIXEL_MULTIPLIER;
    int rounded_y = y / PIXEL_MULTIPLIER;
    int rounded_distance = distance / PIXEL_MULTIPLIER;
    pipeDown->setPosition(sf::Vector2<float>(
        rounded_x * PIXEL_MULTIPLIER,
        (rounded_y * PIXEL_MULTIPLIER) -
            (rounded_distance / 2) * PIXEL_MULTIPLIER - 600));

    rounded_x = x / PIXEL_MULTIPLIER;
    rounded_y = y / PIXEL_MULTIPLIER;
    rounded_distance = distance / PIXEL_MULTIPLIER;
    pipeUp->setPosition(
        sf::Vector2<float>(rounded_x * PIXEL_MULTIPLIER,
                           (rounded_y * PIXEL_MULTIPLIER) +
                               (rounded_distance / 2) * PIXEL_MULTIPLIER));
  } else {
    pipeDown->setPosition(sf::Vector2<float>(x, (y) - (distance / 2) - 600));

    pipeUp->setPosition(sf::Vector2<float>(x, (y) + (distance / 2)));
  }
}

sf::Sprite *Pipe::getSpriteUp() { return pipeDown; }
sf::Sprite *Pipe::getSpriteDown() { return pipeUp; }

void Pipe::move(float x) {
  posX += x;
  if (IS_PIXEL) {
    const int rounded_x = posX / PIXEL_MULTIPLIER;
    pipeDown->setPosition(
        sf::Vector2<float>(rounded_x * PIXEL_MULTIPLIER, pipeDown->getPosition().y));
    pipeUp->setPosition(
        sf::Vector2<float>(rounded_x * PIXEL_MULTIPLIER, pipeUp->getPosition().y));
  } else {

    pipeDown->setPosition(sf::Vector2<float>(posX, pipeDown->getPosition().y));
    pipeUp->setPosition(sf::Vector2<float>(posX, pipeUp->getPosition().y));
  }
}
bool Pipe::colision(sf::Sprite const *object) {
  sf::FloatRect downBoundingBox = pipeDown->getGlobalBounds();
  sf::FloatRect upBoundingBox = pipeUp->getGlobalBounds();
  sf::FloatRect objectBoundingBox = object->getGlobalBounds();
  downBoundingBox.size.x -= 2*PIXEL_MULTIPLIER;
  downBoundingBox.position.x += PIXEL_MULTIPLIER;
  upBoundingBox.size.x -= 2*PIXEL_MULTIPLIER;
  upBoundingBox.position.x += PIXEL_MULTIPLIER;
  objectBoundingBox.size.y -= 2*PIXEL_MULTIPLIER;
  objectBoundingBox.position.y += PIXEL_MULTIPLIER;
  objectBoundingBox.size.x -= 2*PIXEL_MULTIPLIER;
  objectBoundingBox.position.x += 2*PIXEL_MULTIPLIER;
  return downBoundingBox.findIntersection(objectBoundingBox) ||
         upBoundingBox.findIntersection(objectBoundingBox);
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
