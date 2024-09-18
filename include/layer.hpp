#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
class Layer {
public:
    Layer(sf::Texture &texture);
    void move(const float speed, const float width);

    sf::Sprite sprite;
    sf::Sprite alternate;

    float x = 0;
};
