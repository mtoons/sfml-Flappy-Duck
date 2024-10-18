#include <SFML/Graphics.hpp>
#include <fstream>

class ScoreList {
public:
  ScoreList(sf::Font font);
  void updateText();
  void addScore(int score, std::string name);

  sf::Text text;
};
