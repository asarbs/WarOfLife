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

        static int worldSize;
        Node** _world;
        int* prev;
        int* next;

    void updateGame();

    void updateDisplay();

    void eventHandler();
};

#endif // GAMEMAIN_H_INCLUDED
