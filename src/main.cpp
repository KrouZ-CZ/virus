#include <SFML/Graphics.hpp>
#include "drawing.hpp"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1920, 1080), "NotAVirus");

    window.setMouseCursorVisible(false);
    Virus drawing(window);
    while (window.isOpen()) 
    {
        drawing.event();

        drawing.loop();
    }
    return 0;   
}