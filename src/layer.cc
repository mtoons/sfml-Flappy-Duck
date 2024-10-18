#include <layer.hpp>

Layer::Layer(sf::Texture &texture)
    : sprite(sf::Sprite(texture)), alternate(sf::Sprite(texture)) {
    sprite.setScale(sf::Vector2<float>(PIXEL_MULTIPLIER, PIXEL_MULTIPLIER));
    alternate.setScale(sf::Vector2<float>(PIXEL_MULTIPLIER, PIXEL_MULTIPLIER));
}
void Layer::move(const float speed, const float window_width) {
    float width = window_width;
    x += speed / 10;
    float alternate_x = x - window_width;
    if (IS_PIXEL) {
        const int rounded_x = x / PIXEL_MULTIPLIER;
        const int rounded_alternate_x = alternate_x / PIXEL_MULTIPLIER;
        sprite.setPosition(
            sf::Vector2<float>(-(rounded_x * PIXEL_MULTIPLIER), 0));
        alternate.setPosition(
            sf::Vector2<float>(-(rounded_alternate_x * PIXEL_MULTIPLIER), 0));
    } else {
        sprite.setPosition(sf::Vector2<float>(-(x), 0));
        alternate.setPosition(sf::Vector2<float>(-(alternate_x), 0));
    }
    if (x > width) {
        x = 0;
    }
}
