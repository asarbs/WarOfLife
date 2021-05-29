#ifndef GAMEMAIN_H_INCLUDED
#define GAMEMAIN_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Node.h"
#include "brush/Brush.h"
#include "PlayerColor.h"

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

        std::map<int, Brush*> _brushMap;
        int _current_brush = 0;

        static int _worldSize;
        Node** _world1;
        Node** _world2;
        int* prev;
        int* next;
        bool _inEditStare;
        int _selectedPlayerType;

        sf::Color _bgColor;
        float _color[3] = {0.f, 0.f, 0.f };
        char _windowTitle[255] = "ImGui + SFML = <3";
        sf::Event::MouseMoveEvent _shadowMousePosition;

    void updateGame();

    void updateDisplay();

    void eventHandler();

    std::pair<int, PlayerColor> _calculateNumberOfAliveNeighbors(int x, int y);

    void switchEditMode();

    void resetWorld();

    void createAliveCell(const sf::Event &event) const;

    void drawWorld();

};

#endif // GAMEMAIN_H_INCLUDED
