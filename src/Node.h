//
// Created by asar on 22.05.2021.
//

#ifndef WAROFLIFE_NODE_H
#define WAROFLIFE_NODE_H

#include <SFML/Graphics.hpp>

class Node: public sf::RectangleShape {
    public:
        Node(sf::Color color =  sf::Color::Yellow);
        void activate();
    protected:
    private:
};


#endif //WAROFLIFE_NODE_H
