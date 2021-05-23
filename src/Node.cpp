//
// Created by asar on 22.05.2021.
//

#include "Node.h"

Node::Node(sf::Color color): sf::RectangleShape(sf::Vector2f(10.f, 10.f)){
    setFillColor(color);
}

void Node::activate() {
    setFillColor(sf::Color::Blue);
}
