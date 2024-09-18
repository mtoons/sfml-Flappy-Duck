#include <layer.hpp>

Layer::Layer(sf::Texture &texture) : sprite(sf::Sprite(texture)), alternate(sf::Sprite(texture)) {
    sprite.setScale(sf::Vector2<float>(10., 10.));
    alternate.setScale(sf::Vector2<float>(10., 10.));
}
void Layer::move(const float speed, const float window_width) {
    float width = window_width;
    x += speed/10;
    float alternate_x = x - window_width;
    const int rounded_x = x/10;
    const int rounded_alternate_x = alternate_x/10;
    sprite.setPosition(sf::Vector2<float>(-(rounded_x*10), 0));
    alternate.setPosition(sf::Vector2<float>(-(rounded_alternate_x*10), 0));
    if (x > width) { x = 0; }
}
