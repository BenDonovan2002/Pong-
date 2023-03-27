#include <SFML/Graphics.hpp>

const int windowWidth = 1600;
const int windowHeight = 1200;
const float paddleWidth = 20.0f;
const float paddleHeight = 100.0f;
const float ballSize = 10.0f;

const float paddleSpeed = 10.0f;  // Updated from 5.0f to 10.0f
const float BALL_VELOCITY = 6.0f;  // Updated from 3.0f to 6.0f
const float BALL_SPEED_INCREMENT = 1.0f; // Added to increase ball speed upon collision

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    if (!font.loadFromFile("/Users/bendonovan/Desktop/pong/arial.ttf")) {
        // Error handling
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);

    unsigned int score1 = 0;
    unsigned int score2 = 0;

    sf::RectangleShape paddle1(sf::Vector2f(paddleWidth, paddleHeight));
    paddle1.setPosition(50, (windowHeight - paddleHeight) / 2);

    sf::RectangleShape paddle2(sf::Vector2f(paddleWidth, paddleHeight));
    paddle2.setPosition(windowWidth - 50 - paddleWidth, (windowHeight - paddleHeight) / 2);

    sf::CircleShape ball(ballSize);
    ball.setPosition((windowWidth - ballSize) / 2, (windowHeight - ballSize) / 2);

    sf::Vector2f ballVelocity(BALL_VELOCITY, BALL_VELOCITY);

    bool gameStarted = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        scoreText.setString(std::to_string(score1) + " - " + std::to_string(score2));
        sf::FloatRect textBounds = scoreText.getLocalBounds();
        scoreText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        scoreText.setPosition(windowWidth / 2, 40);

        // Start the game if the Space key is pressed
        if (!gameStarted && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            gameStarted = true;
        }

        // Left paddle controls (W and S keys)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle1.getPosition().y > 0) {
            paddle1.move(0, -paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle1.getPosition().y + paddleHeight < windowHeight) {
            paddle1.move(0, paddleSpeed);
        }

        // Right paddle controls (Up and Down arrow keys)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle2.getPosition().y > 0) {
            paddle2.move(0, -paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle2.getPosition().y + paddleHeight < windowHeight) {
            paddle2.move(0, paddleSpeed);
        }

        if (gameStarted) {
            ball.move(ballVelocity);

            if (ball.getPosition().y <= 0 || ball.getPosition().y + ballSize >= windowHeight) {
                ballVelocity.y = -ballVelocity.y;
            }

            if (ball.getGlobalBounds().intersects(paddle1.getGlobalBounds())) {
                ballVelocity.x = std::abs(ballVelocity.x) + BALL_SPEED_INCREMENT;
                ballVelocity.y = (std::rand() % 3) - 1;
            }

            if (ball.getGlobalBounds().intersects(paddle2.getGlobalBounds())) {
                ballVelocity.x = -std::abs(ballVelocity.x) - BALL_SPEED_INCREMENT;
                ballVelocity.y = (std::rand() % 3) - 1;
            }

            // Score and reset the ball position
            if (ball.getPosition().x < 0) {
                score2++;
                ball.setPosition((windowWidth - ballSize) / 2, (windowHeight - ballSize) / 2);
                ballVelocity.x = BALL_VELOCITY;
            }
            if (ball.getPosition().x + ballSize > windowWidth) {
                score1++;
                ball.setPosition((windowWidth - ballSize) / 2, (windowHeight - ballSize) / 2);
                ballVelocity.x = -1*BALL_SPEED_INCREMENT;
            }

            scoreText.setString(std::to_string(score1) + " - " + std::to_string(score2));
        }

        window.clear();
        window.draw(paddle1);
        window.draw(paddle2);
        window.draw(ball);
        window.draw(scoreText);
        window.display();
    }

    return 0;
}
