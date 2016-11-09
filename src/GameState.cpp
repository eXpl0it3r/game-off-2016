#include "GameState.hpp"

#include <SFML/OpenGL.hpp>
#include <SFGUI/Window.hpp>

GameState::GameState(sf::RenderWindow& window, sfg::SFGUI& sfgui)
: State{window}
, m_sfgui{sfgui}
, m_console()
{
    load_resources();

    m_console.font(m_textures["WindowsConsoleFont"]);

    m_desktop.Add(m_console.window());
    m_desktop.SetProperties("* { FontSize: 16; FontName: TimesNewPixel.ttf; } Window { BackgroundColor: #000000ff; Gap: 5.0f; }");
}

void GameState::process_events()
{
    sf::Event event;

    while(m_window.pollEvent(event))
    {
        m_desktop.HandleEvent(event);

        if(event.type == sf::Event::Closed)
            m_window.close();
        else if(event.type == sf::Event::TextEntered)
            m_console.input(event.text.unicode);
    }
}

void GameState::update(const sf::Time dt)
{
    process_events();
    m_desktop.Update(dt.asSeconds());
}

void GameState::render()
{
    m_window.resetGLStates();
    m_window.clear();
    m_window.draw(m_console);
    m_sfgui.Display(m_window);
    m_window.display();
}

void GameState::load_resources()
{
    m_textures.acquire("WindowsConsoleFont", thor::Resources::fromFile<sf::Texture>("Windows Console ASCII.png"));
    m_fonts.acquire("TimesNewPixel", thor::Resources::fromFile<sf::Font>("TimesNewPixel.ttf"));
}
