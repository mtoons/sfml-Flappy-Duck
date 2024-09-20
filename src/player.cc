#include <player.hpp>

Player::Player(sf::Sprite given_sprite) : sprite(given_sprite) {}

void Player::update() {
  y -= velocity;
  velocity -= 0.5;  // gravity
  if (IS_PIXEL) {
      const int rounded_x = x / PIXEL_MULTIPLIER;
      const int rounded_y = y / PIXEL_MULTIPLIER;
      sprite.setPosition(sf::Vector2<float>(rounded_x*PIXEL_MULTIPLIER, rounded_y*PIXEL_MULTIPLIER));
  } else {
      sprite.setPosition(sf::Vector2<float>(x, y));
  }
}
