#include "GameState.hpp"

#include "PaletteEnums.hpp"
#include <SFML/OpenGL.hpp>
#include <SFGUI/Window.hpp>

GameState::GameState(sf::RenderWindow& window, sfg::SFGUI& sfgui)
: State{window}
, m_sfgui{sfgui}
, m_console{sfg::Window::Create()}//sfg::Window::TITLEBAR || sfg::Window::BACKGROUND || sfg::Window::SHADOW || sfg::Window::CLOSE)}
, m_canvas{sfg::Canvas::Create()}
, m_screen{{ 16, 9 }}
{
    load_resources();

    m_screen.setTexture(m_textures["console"]);
    m_screen.setTextureTileSize({ 8, 12 });
    m_screen.setNumberOfTextureTilesPerRow(16);
    m_screen.setSize({ 128.f, 128.f }); // scaled x2
    m_screen.crash(); // randomise cells' values and colours
    m_screen << sw::ConsoleScreen::Direct::Begin
             << sw::ConsoleScreen::Bg(sw::Palette::Default::Black)
             << sw::ConsoleScreen::Fg(sw::Palette::Default::Green)
             << sw::ConsoleScreen::Location(0, 0) << "SFML> !"
             << sw::ConsoleScreen::Direct::End;
    //m_screen << sw::ConsoleScreen::ColorPair(sw::Palette::Default::Green, sw::Palette::Default::Black);
    //m_screen << sw::ConsoleScreen::Location(3, 5) << "Console" << sw::ConsoleScreen::Location(7, 6) << "Screen";


    m_console->Add(m_canvas);

    m_console->SetTitle(L"Sombra Console");
    m_desktop.Add(m_console);
    m_desktop.SetProperties("Window { BackgroundColor: #000000ff; Gap: 5.0f; BorderColor: #FFFFFFFF; }");
}

void GameState::process_events()
{
    sf::Event event;

    while(m_window.pollEvent(event))
    {
        m_desktop.HandleEvent(event);

        if(event.type == sf::Event::Closed)
            m_window.close();
    }
}

void GameState::update(const sf::Time dt)
{
    process_events();
    m_canvas->SetRequisition(m_screen.getSize());
    m_desktop.Update(dt.asSeconds());
}

void GameState::render()
{
    m_canvas->Bind();
	m_canvas->Clear(sf::Color::Black);
	m_canvas->Draw(m_screen);
	m_canvas->Display();
    m_canvas->Unbind();

    m_window.clear();
    m_window.setActive(true);
    m_sfgui.Display(m_window);
    m_window.display();
}

void GameState::load_resources()
{
    m_textures.acquire("console", thor::Resources::fromFile<sf::Texture>("Windows Console ASCII.png"));
}
