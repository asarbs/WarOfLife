#include "GameMain.h"
#include <iostream>

GameMain::GameMain(): _window(sf::VideoMode(1200, 1200), "SFML works!") {
    _window.setFramerateLimit(3);

    _world = new Node*[rowCount];
    for(int i = 0; i < rowCount; ++i) {
        _world[i] = new Node[rowCount];
    }

    for(int x = 0 ; x < rowCount ; ++x)
        for(int y = 0 ; y < rowCount ; ++y)
            _world[x][y].setPosition(x * 11.0, y * 11.0);

}

void GameMain::mainGameLoop() {
    while (_window.isOpen()) {
        eventHandler();
        updateGame();
        updateDisplay();
    }
}

void GameMain::eventHandler() {
    sf::Event event;
    while (_window.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed:
                _window.close();
                break;
            case sf::Event::MouseButtonPressed :
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f hitVec(event.mouseButton.x, event.mouseButton.y);
                    for(int x = 0 ; x < rowCount ; ++x)
                        for (int y = 0; y < rowCount; ++y) {
                            Node &node = _world[x][y];
                            const sf::FloatRect &nodeBounds = node.getGlobalBounds();
                            if(nodeBounds.contains(hitVec))
                                node.activate();
                        }
                }
                break;
        }
    }
}

void GameMain::updateDisplay() {
    _window.clear();
    for(int x = 0 ; x < rowCount ; ++x)
        for(int y = 0 ; y < rowCount ; ++y)
            _window.draw(_world[x][y]);
    _window.display();
}

void GameMain::updateGame() {
}

int GameMain::rowCount = 80;