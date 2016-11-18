#include "Console.hpp"

#include "PaletteEnums.hpp"

#include <SFGUI/Box.hpp>

#include <cmath>
#include <iostream>

Console::Console()
: m_mode{16, 9}
, m_tile_size{8, 12}
, m_console{sfg::Window::Create()}
, m_canvas{sfg::Canvas::Create()}
, m_screen{m_mode}
{
    m_screen.setTextureTileSize(m_tile_size);
    m_screen.setNumberOfTextureTilesPerRow(16);
    m_screen.setSize({ 128.f, 128.f });
    m_screen.setUseCursorColor(true);
    m_screen.setCursorColor(sw::Palette::Default::Green);
    m_screen << sw::ConsoleScreen::ColorPair(sw::Palette::Default::Green, sw::Palette::Default::Black);

    m_console->Add(m_canvas);
    m_console->SetTitle("Sombra Console");

    m_canvas->SetRequisition(m_screen.getSize());
    m_console->GetSignal(sfg::Window::OnSizeAllocate).Connect(std::bind(&Console::on_resize, this));
}

void Console::input(sf::Uint32 character)
{
    if(character == 8) // Backspace
    {
        if(!m_content.empty())
            m_content.pop_back();
        if(!m_line.empty())
            m_line.pop_back();
    }
    else
    {
        m_content.append(sf::String(character));

        if(character == 10 || character == 13) // Return
        {
            m_command = m_line;
            m_line.clear();
        }
        else
        {
            m_line.append(sf::String(character));
        }
    }

    print();
}

void Console::update(sf::Time& dt)
{
}

void Console::font(const sf::Texture& font)
{
    m_screen.setTexture(font);
}

sfg::Window::Ptr Console::window()
{
    return m_console;
}

void Console::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_canvas->Bind();
    m_canvas->Clear(sf::Color::Black);
    m_canvas->Draw(m_screen);
    m_canvas->Display();
    m_canvas->Unbind();
}

void Console::print()
{
    m_screen.clear();

    for(auto character : m_content)
    {
        if(character == 9)       // Tab
        {
            m_screen << sw::ConsoleScreen::CursorCommand::Tab;
        }
        else if(character == 10 || character == 13) // Return
        {
            m_screen << sw::ConsoleScreen::CursorCommand::Newline;
        }
        else
        {
            m_screen << sf::String(character);
        }
    }
}

void Console::on_resize()
{
    auto rect = m_console->GetClientRect();
    auto window_size = sf::Vector2f{rect.width, rect.height};
    auto mode = sf::Vector2u{static_cast<unsigned int>(std::floor(window_size.x / m_tile_size.x + 0.5f)),
                             static_cast<unsigned int>(std::floor(window_size.y / m_tile_size.y + 0.5f))};

    m_screen.setMode(mode);
    m_mode = mode;
    m_screen.setSize({static_cast<float>(mode.x * m_tile_size.x), static_cast<float>(mode.y * m_tile_size.y)});
    m_canvas->SetAllocation({0.f, 0.f, window_size.x, window_size.y});

    print();
}
