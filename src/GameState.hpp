#pragma once

#include "State.hpp"
#include "Console.hpp"
#include "ConsoleScreen.hpp"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Canvas.hpp>
#include <Thor/Resources.hpp>

#include <string>

class GameState : public State
{
public:
    GameState(sf::RenderWindow& window, sfg::SFGUI& sfgui);

private:
    void process_events() final;
    void update(const sf::Time dt) final;
    void render() final;

    void load_resources();

private:
    sfg::SFGUI& m_sfgui;
    sfg::Desktop m_desktop;

    thor::ResourceHolder<sf::Texture, std::string> m_textures;
    thor::ResourceHolder<sf::Font, std::string> m_fonts;

    Console m_console;
};
