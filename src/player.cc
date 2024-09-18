#include <player.hpp>

Player::Player(sf::Sprite given_sprite) : sprite(given_sprite) {}

void Player::update() {
  y -= velocity;
  velocity -= 0.5;  // gravity
  const int rounded_x = x / 10;
  const int rounded_y = y / 10;
  sprite.setPosition(sf::Vector2<float>(rounded_x*10, rounded_y*10));
}
