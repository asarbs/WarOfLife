//
// Created by asar on 27.05.2021.
//

#ifndef WAROFLIFE_BRUSH_H
#define WAROFLIFE_BRUSH_H


#include <vector>

class Brush {
public:
    Brush();
    std::vector<std::pair<int, int>> getNodeList() const;
protected:
    std::vector<std::pair<int, int>> _nodes_list;
private:

};



#endif //WAROFLIFE_BRUSH_H
