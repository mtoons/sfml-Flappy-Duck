#include <player.hpp>

[[nodiscard]] float player::playerUpdate(sf::Sprite &player, float velocity) {
  player.move(0, -velocity);
  return velocity - 0.5; // gravity
}
