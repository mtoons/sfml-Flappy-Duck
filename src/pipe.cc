#include <pipe.hpp>

extern double dt;
Pipe::Pipe(float x, float y, float distance, const sf::Texture *textureUp,
        const sf::Texture *textureDown) {
    passed = false;
    posX = x;
    posY = y;
    pipeDown = new sf::Sprite(*textureDown);
    pipeDown->scale(sf::Vector2<float>(10., 10.));
    pipeUp = new sf::Sprite(*textureUp);
    pipeUp->scale(sf::Vector2<float>(10., 10.));
    if (IS_PIXEL) {
        int rounded_x = x/10;
        int rounded_y = y/10;
        int rounded_distance = distance/10;
        pipeDown->setPosition(sf::Vector2<float>(rounded_x*10, (rounded_y*10) - (rounded_distance/2)*10 - 600));

        rounded_x = x/10;
        rounded_y = y/10;
        rounded_distance = distance/10;
        pipeUp->setPosition(sf::Vector2<float>(rounded_x*10, (rounded_y*10) + (rounded_distance / 2)*10));
    } else {
        pipeDown->setPosition(sf::Vector2<float>(x, (y) - (distance/2) - 600));

        pipeUp->setPosition(sf::Vector2<float>(x, (y) + (distance / 2)));
    }
}

sf::Sprite *Pipe::getSpriteUp() { return pipeDown; }
sf::Sprite *Pipe::getSpriteDown() { return pipeUp; }

void Pipe::move(float x) {
    posX += x;
    if (IS_PIXEL) {
        const int rounded_x = posX / 10;
        pipeDown->setPosition(sf::Vector2<float>(rounded_x*10, pipeDown->getPosition().y));
        pipeUp->setPosition(sf::Vector2<float>(rounded_x*10, pipeUp->getPosition().y));
    } else {

        pipeDown->setPosition(sf::Vector2<float>(posX, pipeDown->getPosition().y));
        pipeUp->setPosition(sf::Vector2<float>(posX, pipeUp->getPosition().y));
    }
}
bool Pipe::colision(sf::Sprite const *object) {
    sf::FloatRect downBoundingBox = pipeDown->getGlobalBounds();
    sf::FloatRect upBoundingBox = pipeUp->getGlobalBounds();
    sf::FloatRect objectBoundingBox = object->getGlobalBounds();
    downBoundingBox.size.x -= 20;
    downBoundingBox.position.x += 10;
    upBoundingBox.size.x -= 20;
    upBoundingBox.position.x += 10;
    objectBoundingBox.size.y -= 20;
    objectBoundingBox.position.y += 10;
    objectBoundingBox.size.x -= 20;
    objectBoundingBox.position.x += 20;
    return downBoundingBox.findIntersection(objectBoundingBox ) || upBoundingBox.findIntersection(objectBoundingBox );
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
