#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <score_list.hpp>

ScoreList::ScoreList(sf::Font font) : text(font) {}

void ScoreList::addScore(int score, std::string name) {
  std::ifstream ifile("ressources/data.txt");
  ifile.seekg(0, std::ios::end);
  size_t size = ifile.tellg();
  std::string buffer(size, ' ');
  ifile.seekg(0);
  ifile.read(&buffer[0], size);

  std::ofstream ofile("ressources/data.txt");
}

void ScoreList::updateText() {
  std::ifstream file("ressources/data.txt");
  file.seekg(0, std::ios::end);
  size_t size = file.tellg();
  std::string buffer(size, ' ');
  file.seekg(0);
  file.read(&buffer[0], size);

  text.setString(buffer);
}
