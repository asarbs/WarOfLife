
#include "GameMain.h"

static int rowCount = 10;

int main()
{
    int** world = new int*[rowCount];
    for(int i = 0; i < rowCount; ++i)
    {
        world[i] = new int[rowCount];
    }



    sf::RenderWindow window(sf::VideoMode(1200, 1200), "SFML works!");
    window.setFramerateLimit(3);
    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(sf::Vector2f(50.f, 50.f));
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        rectangle.move(sf::Vector2f(10.f,10.f));
        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
