#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

class Application
{
public:
    Application();

    void run();

private:
    sfg::SFGUI m_sfgui;
    sf::RenderWindow m_window;
};
