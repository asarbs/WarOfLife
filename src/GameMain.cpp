#include "GameMain.h"
#include "GosperGliderGun.h"
#include <iostream>

GameMain::GameMain(): _window(sf::VideoMode(1200, 1200), _windowTitle), _inEditStare(true), _createOscillator(false) {
    _window.setFramerateLimit(30);
    _window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(_window);

    _world1 = new Node*[_worldSize];
    _world2 = new Node*[_worldSize];
    prev = new int[_worldSize];
    next = new int[_worldSize];

    for(int i = 0; i < _worldSize; ++i) {
        _world1[i] = new Node[_worldSize];
        _world2[i] = new Node[_worldSize];
        prev[i] = i - 1;
        next[i] = i + 1;
    }

    prev[0] = _worldSize - 1;
    prev[_worldSize - 1] = _worldSize - 2;
    next[_worldSize - 1] = 0;

    for(int x = 0 ; x < _worldSize ; ++x)
        for(int y = 0 ; y < _worldSize ; ++y) {
            _world1[x][y].setPosition(x * 6.0, y * 6.0);
            _world2[x][y].setPosition(x * 6.0, y * 6.0);
        }
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
    while (_window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        switch (event.type) {
            case sf::Event::Closed:
                _window.close();
                break;
            case sf::Event::KeyPressed:
                switchEditMode();
                resetWorld();
                addPredefinedPattern();
            case sf::Event::MouseButtonPressed :
                createAliveCell(event);
                break;
        }
    }
}

void GameMain::createAliveCell(const sf::Event &event) const {
    if(event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f hitVec(event.mouseButton.x, event.mouseButton.y);
        for(int x = 0 ; x < _worldSize ; ++x)
            for (int y = 0; y < _worldSize; ++y) {
                if(_createOscillator) {
                    Node &node = _world1[x][y];
                    const sf::FloatRect &nodeBounds = node.getGlobalBounds();
                    if(nodeBounds.contains(hitVec)) {
                        GosperGliderGun ggg;
                        auto nodeList = ggg.getNodeList();
                        for(auto pair : nodeList) {
                            _world1[x+pair.first][y+pair.second].alive();
                        }
                    }
                }
                else {
                    Node &node1 = _world1[x][y];
                    const sf::FloatRect &nodeBounds = node1.getGlobalBounds();
                    if(nodeBounds.contains(hitVec)) {
                        node1.alive();
                    }
                }
            }
    }
}

void GameMain::resetWorld() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        for(int x = 0 ; x < _worldSize ; ++x)
            for(int y = 0 ; y < _worldSize ; ++y) {
                _world1[x][y].die();
            }
    }
}

void GameMain::switchEditMode() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        _inEditStare = !_inEditStare;
    }
}

void GameMain::addPredefinedPattern() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
        _createOscillator = true;
    }
}

void GameMain::updateDisplay() {
    ImGui::SFML::Update(_window, _deltaClock.restart());
    _window.clear(_bgColor);
    for(int x = 0 ; x < _worldSize ; ++x)
        for(int y = 0 ; y < _worldSize ; ++y)
            _window.draw(_world1[x][y]);

    ImGui::Begin("Sample window");

    ImGui::Begin("Sample window"); // begin window

    // Background _color edit
    if (ImGui::ColorEdit3("Background _color", _color)) {
        // this code gets called if _color value changes, so
        // the background _color is upgraded automatically!
        _bgColor.r = static_cast<sf::Uint8>(_color[0] * 255.f);
        _bgColor.g = static_cast<sf::Uint8>(_color[1] * 255.f);
        _bgColor.b = static_cast<sf::Uint8>(_color[2] * 255.f);
    }

    // Window title text edit
    ImGui::InputText("Window title", _windowTitle, 255);

    if (ImGui::Button("Update window title")) {
        // this code gets if user clicks on the button
        // yes, you could have written if(ImGui::InputText(...))
        // but I do this to show how buttons work :)
        _window.setTitle(_windowTitle);
    }

    ImGui::End();

    ImGui::SFML::Render(_window);
    _window.display();
}

void GameMain::updateGame() {
    if(_inEditStare)
        return;
    for(int x = 0 ; x < _worldSize ; ++x) {
        for (int y = 0; y < _worldSize; ++y) {
            int numberOfAliveNeighbors = _calculateNumberOfAliveNeighbors(x, y);
            if(numberOfAliveNeighbors == 3)
                _world2[x][y].alive();
            else if (_world1[x][y].isAlive() && numberOfAliveNeighbors == 2)
                _world2[x][y].alive();
            else
                _world2[x][y].die();
        }
    }
    Node** tmp;
    tmp = _world1;
    _world1 = _world2;
    _world2 = tmp;
}

int GameMain::_worldSize = 150;

/*
 *  cell1=(x-1,y-1) | cell2=(x-1, y ) | cell3=(x-1,y+1)
 *  ----------------+-----------------+----------------
 *  cell4=( x ,y-1) |    ( x , y )    | cell5=( x ,y+1)
 *  ----------------+-----------------+----------------
 *  cell6=(x+1,y-1) | cell7=(x+1, y ) | cell8=(x+1,y+1)
 */
int GameMain::_calculateNumberOfAliveNeighbors(int x, int y) {
    Node& cell1 = _world1[prev[x]][prev[y]];
    Node& cell2 = _world1[prev[x]][y];
    Node& cell3 = _world1[prev[x]][next[y]];
    Node& cell4 = _world1[x][prev[y]];
    Node& cell5 = _world1[x][next[y]];
    Node& cell6 = _world1[next[x]][prev[y]];
    Node& cell7 = _world1[next[x]][y];
    Node& cell8 = _world1[next[x]][next[y]];
    return cell1.isAlive() + cell2.isAlive() + cell3.isAlive() + cell4.isAlive() + cell5.isAlive() + cell6.isAlive() + cell7.isAlive() + cell8.isAlive();
}

GameMain::~GameMain() {
    ImGui::SFML::Shutdown();
}
