#include "GameMain.h"

GameMain::GameMain(): window(sf::VideoMode(1200, 1200), "SFML works!"), rectangle(sf::Vector2f(120.f, 50.f)) {
    window.setFramerateLimit(3);
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(sf::Vector2f(50.f, 50.f));
}

void GameMain::mainGameLoop() {
    while (window.isOpen()) {
        eventHandler();
        updateGame();
        updateDisplay();
    }
}

void GameMain::eventHandler() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void GameMain::updateDisplay() {
    window.clear();
    window.draw(rectangle);
    window.display();
}

void GameMain::updateGame() {
    rectangle.move(sf::Vector2f(10.f, 10.f));
}
