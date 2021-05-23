//
// Created by asar on 22.05.2021.
//

#include "Node.h"

Node::Node(sf::Color color): sf::RectangleShape(sf::Vector2f(10.f, 10.f)), _state(false) {
    setFillColor(color);
}

void Node::alive() {
    setFillColor(sf::Color::Blue);
    _state = true;
}

int Node::isAlive() {
    return int(_state);
}


void Node::die() {
    setFillColor(sf::Color::Yellow);
    _state = false;
}
