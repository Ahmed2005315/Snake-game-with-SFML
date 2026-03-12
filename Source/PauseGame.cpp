#include "PauseGame.h"
#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(shared_ptr<Context>& context):m_context(context),
PauseText(m_context->m_assets->GetFont(MAINFONT))
{
}
PauseGame::~PauseGame() {}

void PauseGame::Init()
{ 
	PauseText.setFont(m_context->m_assets->GetFont(MAINFONT));
	PauseText.setString("Paused");
	PauseText.setOrigin(PauseText.getLocalBounds().getCenter());
	PauseText.setPosition({ static_cast<float>(m_context->m_window->getSize().x / 2),
		static_cast<float>(m_context->m_window->getSize().y / 2 )});
	PauseText.setFillColor(sf::Color::Yellow);
	PauseText.setOutlineColor(sf::Color::Black);
}

void PauseGame::ProcessInput()
{
	while (auto event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>()) {
			m_context->m_states->PopAll();
		}
		else if (const auto* KeyEvent = event->getIf<sf::Event::KeyPressed>())
		{
			switch (KeyEvent->code)
			{
			case sf::Keyboard::Key::Escape:
			{
				m_context->m_states->PopCurrent();
				break;
			}
			default:
				break;
			}
		}
	}
}

void PauseGame::Update(const sf::Time& deltaTime)
{
}

void PauseGame::Draw()
{
	m_context->m_window->draw(PauseText);
	m_context->m_window->display();
}
