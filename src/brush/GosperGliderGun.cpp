//
// Created by asar on 27.05.2021.
//

#include "GosperGliderGun.h"

GosperGliderGun::GosperGliderGun():Brush() {
    _nodes_list.push_back(std::make_pair(0,5));
    _nodes_list.push_back(std::make_pair(1,5));
    _nodes_list.push_back(std::make_pair(0,6));
    _nodes_list.push_back(std::make_pair(1,6));
    _nodes_list.push_back(std::make_pair(11,2));
    _nodes_list.push_back(std::make_pair(11,3));
    _nodes_list.push_back(std::make_pair(11,7));
    _nodes_list.push_back(std::make_pair(11,8));
    _nodes_list.push_back(std::make_pair(13,3));
    _nodes_list.push_back(std::make_pair(13,7));
    _nodes_list.push_back(std::make_pair(14,4));
    _nodes_list.push_back(std::make_pair(14,5));
    _nodes_list.push_back(std::make_pair(14,6));
    _nodes_list.push_back(std::make_pair(15,4));
    _nodes_list.push_back(std::make_pair(15,5));
    _nodes_list.push_back(std::make_pair(15,6));
    _nodes_list.push_back(std::make_pair(18,3));
    _nodes_list.push_back(std::make_pair(19,2));
    _nodes_list.push_back(std::make_pair(19,3));
    _nodes_list.push_back(std::make_pair(19,4));
    _nodes_list.push_back(std::make_pair(20,1));
    _nodes_list.push_back(std::make_pair(20,5));
    _nodes_list.push_back(std::make_pair(21,3));
    _nodes_list.push_back(std::make_pair(22,0));
    _nodes_list.push_back(std::make_pair(22,6));
    _nodes_list.push_back(std::make_pair(23,0));
    _nodes_list.push_back(std::make_pair(23,6));
    _nodes_list.push_back(std::make_pair(24,1));
    _nodes_list.push_back(std::make_pair(24,5));
    _nodes_list.push_back(std::make_pair(25,2));
    _nodes_list.push_back(std::make_pair(25,3));
    _nodes_list.push_back(std::make_pair(25,4));
    _nodes_list.push_back(std::make_pair(34,3));
    _nodes_list.push_back(std::make_pair(34,4));
    _nodes_list.push_back(std::make_pair(35,3));
    _nodes_list.push_back(std::make_pair(35,4));
}
