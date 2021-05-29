//
// Created by asar on 22.05.2021.
//

#include <iostream>
#include "Node.h"

Node::Node(sf::Color color): sf::RectangleShape(sf::Vector2f(5.f, 5.f)), _state(false), _playerColor(PlayerColor::NULL_COLOR) {
    setFillColor(color);
}

void Node::alive(PlayerColor playerColor) {
    _playerColor = playerColor;
    setFillColor(selectColor(playerColor));
    _state = true;
}

int Node::isAlive() const {
    return int(_state);
}


void Node::die() {
    setFillColor(sf::Color::Yellow);
    _playerColor = PlayerColor::NULL_COLOR;
    _state = false;
}

sf::Color Node::selectColor(PlayerColor color) {
    switch (color) {
        case PlayerColor::BLUE:
            return sf::Color::Blue;
        case PlayerColor::RED:
            return sf::Color::Red;
        case PlayerColor::GREEN:
            return sf::Color::Green;
        default:
            return sf::Color::Yellow;
    }
}

PlayerColor Node::getPlayerColor() const {
    return _playerColor;
}

void Node::setTemp() {
    setFillColor(selectColor(PlayerColor::GREEN));
}

void Node::unsetTemp() {
    setFillColor(selectColor(_playerColor));
}
