#include "GameMain.h"
#include "brush/GosperGliderGun.h"
#include "brush/Glider.h"
#include "brush/Dot.h"
#include <functional>
#include <numeric>
#include <iostream>


GameMain::GameMain(): _window(sf::VideoMode(1900, 1200),
                              _windowTitle),
                              _inEditStare(true),
                              _current_brush(0),
                              _selectedPlayerType(PlayerColor::RED),
                              _shadowMousePosition{0,0} {
    _window.setFramerateLimit(60);
    _window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(_window);

    _brushMap[0] = new Glider();
    _brushMap[1] = new GosperGliderGun();
    _brushMap[2] = new Dot();

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
            _world1[x][y].setPosition(10 + x * 5.0, 10 + y * 5.0);
            _world2[x][y].setPosition(10 + x * 5.0, 10 + y * 5.0);
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
                break;
            case sf::Event::MouseButtonPressed :
                createAliveCell(event);
                break;
            case sf::Event::MouseMoved :
                _shadowMousePosition = event.mouseMove;
                break;
        }
    }
}

void GameMain::createAliveCell(const sf::Event &event) const {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f hitVec(event.mouseButton.x, event.mouseButton.y);
        for (int x = 0; x < _worldSize; ++x)
            for (int y = 0; y < _worldSize; ++y) {
                Node &node = _world1[x][y];
                const sf::FloatRect &nodeBounds = node.getGlobalBounds();
                if (nodeBounds.contains(hitVec)) {
                    Brush *brush = _brushMap.at(_current_brush);
                    auto nodeList = brush->getNodeList();
                    for (auto pair : nodeList) {
                        _world1[x + pair.first][y + pair.second].alive(static_cast<PlayerColor>(_selectedPlayerType));
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

void GameMain::updateDisplay() {
    ImGui::SFML::Update(_window, _deltaClock.restart());
    drawWorld();

    ImGui::Begin("Sample window");

    ImGui::LabelText("FPS", "0");

    const char* items[] = { "Gliber", "Gosper Glider Gun", "Dot"};
    ImGui::Combo("Select template", &_current_brush, items, IM_ARRAYSIZE(items));

    const char* players_color[] = {"red", "blue"};
    ImGui::Combo("Player Color", &_selectedPlayerType, players_color, IM_ARRAYSIZE(players_color));

    ImGui::End();

    ImGui::SFML::Render(_window);
    _window.display();
}

void GameMain::drawWorld() {
    bool setCursor = false;
    _window.clear(_bgColor);
    sf::Vector2f hitVec(_shadowMousePosition.x, _shadowMousePosition.y);
    for(int x = 0 ; x < _worldSize ; ++x) {
        for (int y = 0; y < _worldSize; ++y) {


            Node &node = _world1[x][y];
            const sf::FloatRect &nodeBounds = node.getGlobalBounds();
            if (nodeBounds.contains(hitVec)) {
                Brush *brush = _brushMap.at(_current_brush);
                auto nodeList = brush->getNodeList();
                for (auto pair : nodeList) {
                    int tmp_x = x + pair.first;
                    int tmp_y = y + pair.second;
                    if(tmp_x < _worldSize && tmp_y < _worldSize) {
                        _world1[tmp_x][tmp_y].setTemp();
                        setCursor = true;
                    }
                }
            }
            _window.draw(_world1[x][y]);
            _world1[x][y].unsetTemp();
        }
    }
}

void GameMain::updateGame() {
    if(_inEditStare)
        return;
    for(int x = 0 ; x < _worldSize ; ++x) {
        for (int y = 0; y < _worldSize; ++y) {
            std::pair<int, PlayerColor> res = _calculateNumberOfAliveNeighbors(x, y);
            if(res.first == 3)
                _world2[x][y].alive(res.second);
            else if (_world1[x][y].isAlive() && res.first == 2)
                _world2[x][y].alive(res.second);
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
std::pair<int, PlayerColor> GameMain::_calculateNumberOfAliveNeighbors(int x, int y) {
    static std::vector<Node const*> nodeVector;
    nodeVector.push_back( &_world1[prev[x]][prev[y]] );
    nodeVector.push_back( &_world1[prev[x]][y] );
    nodeVector.push_back( &_world1[prev[x]][next[y]] );
    nodeVector.push_back( &_world1[x][prev[y]] );
    nodeVector.push_back( &_world1[x][next[y]] );
    nodeVector.push_back( &_world1[next[x]][prev[y]] );
    nodeVector.push_back( &_world1[next[x]][y] );
    nodeVector.push_back( &_world1[next[x]][next[y]] );
    auto lambda = [&](int a, Node const* b){return a + b->isAlive() ;};
    int numberOfAliveNeighbors = std::accumulate(nodeVector.begin(), nodeVector.end(), 0, lambda);

    static std::array<int, 2> playerColor;
    playerColor[PlayerColor::RED] = 0;
    playerColor[PlayerColor::BLUE] = 0;
    for(auto node : nodeVector) {
        playerColor[node->getPlayerColor()]++;
    }
    PlayerColor resColor = playerColor[PlayerColor::RED] >= playerColor[PlayerColor::BLUE] ? PlayerColor::RED : PlayerColor::BLUE;
    nodeVector.clear();
    return std::pair<int, PlayerColor>(numberOfAliveNeighbors, resColor);
}

GameMain::~GameMain() {
    ImGui::SFML::Shutdown();
}
