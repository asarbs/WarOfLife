//
// Created by asar on 22.05.2021.
//

#ifndef WAROFLIFE_NODE_H
#define WAROFLIFE_NODE_H

#include <SFML/Graphics.hpp>
#include "PlayerColor.h"

class Node: public sf::RectangleShape {
    public:
        Node(sf::Color color =  sf::Color::Yellow);
        void activate();

    int isAlive() const;
    void alive(PlayerColor playerColor);
    void die();
    PlayerColor getPlayerColor() const;

    void setTemp();

    void unsetTemp();

protected:
    private:
        bool _state;
        PlayerColor _playerColor;
        sf::Color selectColor(PlayerColor color);
        Node(const Node &p1);
        Node& operator= (const Node &t);
};


#endif //WAROFLIFE_NODE_H
