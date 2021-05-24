#ifndef GAMEMAIN_H_INCLUDED
#define GAMEMAIN_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Node.h"

class GameMain
{
    public:
        GameMain();
        void mainGameLoop();
    protected:
    private:
        sf::RenderWindow _window;

        static int _worldSize;
        Node** _world1;
        Node** _world2;
        int* prev;
        int* next;

    void updateGame();

    void updateDisplay();

    void eventHandler();

    int _calculateNumberOfAliveNeighbors(int x, int y);

    bool _inEditStare;

    void switchEditMode();

    void resetWorld();

    void createAliveCell(const sf::Event &event) const;
};

#endif // GAMEMAIN_H_INCLUDED
