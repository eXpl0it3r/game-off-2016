#pragma once

#include "ConsoleScreen.hpp"

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Canvas.hpp>

class Console : public sf::Drawable
{
public:
    Console();

    void input(sf::Uint32 character);
    void update(sf::Time& dt);
    void font(const sf::Texture& font);
    sfg::Window::Ptr window();

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    void print();
    void on_resize();

protected:
    sf::Vector2u m_mode;
    sf::Vector2u m_tile_size;
    std::string m_content;
    std::string m_line;
    std::string m_command;

    sfg::Window::Ptr m_console;
    sfg::Canvas::Ptr m_canvas;
    sw::ConsoleScreen m_screen;
};
