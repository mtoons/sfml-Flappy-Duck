#pragma once
#include <SFML/Graphics.hpp>

namespace player {
struct Player {
  float velocity;
  sf::Sprite sprite;
};
[[nodiscard]] float playerUpdate(sf::Sprite &player, float velocity);
} // namespace player
