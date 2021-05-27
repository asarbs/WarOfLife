//
// Created by asar on 27.05.2021.
//

#include "Glider.h"

Glider::Glider() {
    _nodes_list.push_back(std::make_pair(0,0));
    _nodes_list.push_back(std::make_pair(0,1));
    _nodes_list.push_back(std::make_pair(0,2));
    _nodes_list.push_back(std::make_pair(1,0));
    _nodes_list.push_back(std::make_pair(2,1));
}
