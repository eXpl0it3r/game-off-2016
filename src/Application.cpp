#include "Application.hpp"

#include "GameState.hpp"

#include <memory>

Application::Application()
: m_sfgui{}
, m_window{{1024, 768}, "SmallGameFramework", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings{0, 0, 8}}
{
    m_window.setVerticalSyncEnabled(true);
}

void Application::run()
{
    // Simple state machine
    std::unique_ptr<State> state(new GameState(m_window, m_sfgui));

    while(state != nullptr)
    {
        state = state->run();
    }
}
