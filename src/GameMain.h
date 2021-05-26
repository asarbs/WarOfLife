#ifndef GAMEMAIN_H_INCLUDED
#define GAMEMAIN_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Node.h"

class GameMain
{
    public:
        GameMain();
        ~GameMain();
        void mainGameLoop();
    protected:
    private:
        sf::RenderWindow _window;
        sf::Clock _deltaClock;

        static int _worldSize;
        Node** _world1;
        Node** _world2;
        int* prev;
        int* next;
        bool _inEditStare;
        bool _createOscillator;

        sf::Color _bgColor;
        float _color[3] = {0.f, 0.f, 0.f };
        char _windowTitle[255] = "ImGui + SFML = <3";

    void updateGame();

    void updateDisplay();

    void eventHandler();

    int _calculateNumberOfAliveNeighbors(int x, int y);

    void switchEditMode();

    void resetWorld();

    void createAliveCell(const sf::Event &event) const;

    void addPredefinedPattern();

};

#endif // GAMEMAIN_H_INCLUDED
