// TODO: Port this shit to zig build

#include <main.hpp>
double dt;

int main() {
  srand(time(0));

  // window setup
  unsigned int const screenWidth(sf::VideoMode::getDesktopMode().width),
      screenHeight(sf::VideoMode::getDesktopMode().height);
  sf::RenderWindow window(sf::VideoMode(1600, 900), "flappy duck");
  window.setActive(true);
  window.setVerticalSyncEnabled(true);
  float windowWidth(window.getSize().x);
  float windowHeight(window.getSize().y);

  sf::Texture backgroundTexture;
  backgroundTexture.loadFromFile("ressources/background.png");
  sf::Sprite background;
  background.setTexture(backgroundTexture);
  background.setScale(10, 10);

  // load the font
  sf::Font font;
  font.loadFromFile("ressources/Roboto.ttf");

  // setup score variable and text
  int score = 0;
  sf::Text scoreText;
  scoreText.setFont(font);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setCharacterSize(50);
  scoreText.setPosition(0, 0);
  scoreText.setString(std::to_string(score));

  // setup game over variable and text
  bool gameOver = false;
  sf::Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setFillColor(sf::Color::White);
  gameOverText.setCharacterSize(50);
  gameOverText.setString("Game over");
  gameOverText.setOrigin(100, 50);
  gameOverText.setPosition(windowWidth / 2, windowHeight / 2);

  // create the player
  sf::Texture duckTexture;
  duckTexture.loadFromFile("ressources/duck.png");
  player::Player player;
  player.sprite.setTexture(duckTexture);
  player.sprite.setScale(10, 10);
  player.sprite.setPosition(windowWidth / 4., windowHeight / 2.);
  player.velocity = 0;

  // setup the pipes
  sf::Texture *pipeUpTexture = new sf::Texture;
  pipeUpTexture->loadFromFile("ressources/pipe_up.png");
  sf::Texture *pipeDownTexture = new sf::Texture;
  pipeDownTexture->loadFromFile("ressources/pipe_down.png");
  std::vector<Pipe *> pipes = {};
  float pipeSpeed = 500;

  sf::Clock deltaClock;
  sf::Event event;
  bool space = false;
  float count = 10;
  while (window.isOpen()) {
    window.clear(sf::Color::Black);
    window.draw(background);

    { // take events
      space = false;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        } else if (event.type == sf::Event::KeyPressed) {
          switch (event.key.scancode) {
          case sf::Keyboard::Scan::Escape:
            window.close();
            break;

          case sf::Keyboard::Scan::Space:
            space = true;
            break;

          default:
            break;
          }
        }
      }
    }

    if (!gameOver) {
      player.velocity = ((10 * space) + (player.velocity * !space));

      player.velocity = player::playerUpdate(player.sprite, player.velocity);

      pipeSpeed += 0.5 * dt;
      for (Pipe *&element : pipes) {
        element->move(-pipeSpeed * dt);
        if (element->colision(player.sprite.getPosition().x,
                              player.sprite.getPosition().y)) {
          gameOver = true;
        }
        if ((!element->passed) && (element->getX() <= windowWidth / 4)) {
          element->passed = true;
          score++;
          scoreText.setString(std::to_string(score));
        }
      }
      count += 10 * dt;
      if (count >= 10) {
        count = 0;
        pipes.push_back(
            new Pipe(windowWidth, windowHeight / 4. - 250 + rand() % 500,
                     650 - 25 + rand() % 50, pipeUpTexture, pipeDownTexture));
      }
      if (pipes[0]->getSpriteUp()->getPosition().x <= -200) {
        delete pipes[0];
        pipes.erase(pipes.begin());
      }
    } else {
      if (space) {
        for (Pipe *&element : pipes) {
          delete element;
        }
        pipes.erase(pipes.begin(), pipes.end());
        score = 0;
        scoreText.setString(std::to_string(score));
        count = 10;
        player.velocity = 0;
        pipeSpeed = 500;
        player.sprite.setPosition(windowWidth / 4., windowHeight / 2.);

        gameOver = false;
      }
    }

    for (Pipe *&element : pipes) {
      element->draw(window);
    }
    window.draw(player.sprite);
    window.draw(scoreText);
    if (gameOver) {
      window.draw(gameOverText);
    }
    window.display();

    dt = deltaClock.restart().asSeconds();
  }
  delete pipeUpTexture;
  delete pipeDownTexture;
  for (Pipe *&element : pipes) {
    delete element;
  }
}
