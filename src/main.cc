// TODO: Port this shit to zig build

#include <main.hpp>
double dt;

int main() {
  srand(time(0));

  // window setup
  unsigned int const screenWidth(sf::VideoMode::getDesktopMode().size.x),
      screenHeight(sf::VideoMode::getDesktopMode().size.y);
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1600, 900)),
                          "flappy duck");
  static_cast<void>(window.setActive(true));
  window.setVerticalSyncEnabled(true);
  float windowWidth(window.getSize().x);
  float windowHeight(window.getSize().y);

  sf::Texture backgroundTexture;
  static_cast<void>(
      backgroundTexture.loadFromFile("ressources/background.png"));
  sf::Sprite background(backgroundTexture);
  // background.setTexture(backgroundTexture);
  background.setScale(sf::Vector2<float>(10, 10));

  // load the font
  sf::Font font = sf::Font("ressources/Roboto.ttf");

  // setup score variable and text
  int score = 0;
  sf::Text scoreText(font);
  // scoreText.setFont(font);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setCharacterSize(50);
  scoreText.setPosition(sf::Vector2<float>(0, 0));
  scoreText.setString(std::to_string(score));

  // setup game over variable and text
  bool gameOver = false;
  sf::Text gameOverText(font);
  // gameOverText.setFont(font);
  gameOverText.setFillColor(sf::Color::White);
  gameOverText.setCharacterSize(50);
  gameOverText.setString("Game over");
  gameOverText.setOrigin(sf::Vector2<float>(100, 50));
  gameOverText.setPosition(
      sf::Vector2<float>(windowWidth / 2, windowHeight / 2));

  // create the player
  sf::Texture duckTexture;
  static_cast<void>(duckTexture.loadFromFile("ressources/duck.png"));
  Player player_instance((sf::Sprite(duckTexture)));
  // player.sprite.setTexture(duckTexture);
  player_instance.sprite.setScale(sf::Vector2<float>(10, 10));
  player_instance.sprite.setPosition(
      sf::Vector2<float>(windowWidth / 4., windowHeight / 2.));
  player_instance.x = windowWidth / 4.;
  player_instance.y = windowHeight / 2.;
  player_instance.update();
  player_instance.velocity = 0;

  // setup the pipes
  sf::Texture *pipeUpTexture = new sf::Texture;
  static_cast<void>(pipeUpTexture->loadFromFile("ressources/pipe_up.png"));
  sf::Texture *pipeDownTexture = new sf::Texture;
  static_cast<void>(pipeDownTexture->loadFromFile("ressources/pipe_down.png"));
  std::vector<Pipe *> pipes = {};
  float pipeSpeed = 500;

  sf::Clock deltaClock;
  // sf::Event event;
  bool space = false;
  float count = 10;
  while (window.isOpen()) {
    window.clear(sf::Color::Black);
    window.draw(background);

    {  // take events
      space = false;
      while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          window.close();
        } 
        else if (event->is<sf::Event::KeyPressed>()) {
          switch (event->getIf<sf::Event::KeyPressed>()->code) {
            case sf::Keyboard::Key::Escape:
              window.close();
              break;

            case sf::Keyboard::Key::Space:
              space = true;
              break;

            default:
              break;
          }
        }
      }
    }

    if (!gameOver) {
      if (space) {player_instance.velocity = 10;}
      // player_instance.velocity = space ? 10 : player_instance.velocity;
      // ((10 * space) + (player_instance.velocity * !space));

      player_instance.update();

      pipeSpeed += 0.5 * dt;
      for (Pipe *&pipe : pipes) {
        pipe->move(-pipeSpeed * dt);
        if (pipe->colision(player_instance.sprite.getPosition().x,
                              player_instance.sprite.getPosition().y)) {
          gameOver = true;
        }
        if ((!pipe->passed) && (pipe->getX() <= player_instance.x)) {
          pipe->passed = true;
          score++;
          scoreText.setString(std::to_string(score));
        }
      }
      count += 10 * dt;
      if (count >= 10) {
        count = 0;
        const int rounded_x = windowWidth/10;
        const int rounded_y =  (windowHeight / 4. - 250 + rand() % 500)/10;
        const int rounded_dist = (650 - 25 + rand() % 50)/10;

        pipes.push_back(
            new Pipe(rounded_x*10, rounded_y*10,
                     rounded_dist*10, pipeUpTexture, pipeDownTexture));
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
        player_instance.velocity = 0;
        pipeSpeed = 500;
        player_instance.sprite.setPosition(
            sf::Vector2<float>(windowWidth / 4., windowHeight / 2.));
        player_instance.x = windowWidth / 4.;
        player_instance.y = windowHeight / 2.;

        gameOver = false;
      }
    }

    for (Pipe *&element : pipes) {
      element->draw(window);
    }
    window.draw(player_instance.sprite);
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
