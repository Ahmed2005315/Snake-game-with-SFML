#include "Game.h"
#include"MainMenu.h"
#include <SFML/Graphics/CircleShape.hpp>

Game::Game() :m_context(make_shared<Context>()) 
{
	m_context->m_assets->AddFont(MAINFONT, "assets/Fonts/Pacifico-Regular.ttf");

	m_context->m_assets->AddTexture(FOOD, "assets/Textures/food.png");
	m_context->m_assets->AddTexture(GRASS, "assets/Textures/grass.png", true);
	m_context->m_assets->AddTexture(WALL, "assets/Textures/wwall.png", true);
	m_context->m_assets->AddTexture(SNAKE, "assets/Textures/snake.png");

	m_context->m_window->create(sf::VideoMode({ 640u, 352u }), "Snake Game", sf::Style::Close);
	 m_context->m_states->Add(make_unique<MainMenu>(m_context));
}

Game::~Game()
{
}

void Game::Run() {
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	sf::Clock clock;
	sf::Time TimeSinceLastFrame = sf::Time::Zero;

	while (m_context->m_window->isOpen()) 
	{
		TimeSinceLastFrame += clock.restart();
		while (TimeSinceLastFrame > TIME_PER_FRAME) 
		{
			TimeSinceLastFrame -= TIME_PER_FRAME;
			m_context->m_states->Process_State_Change();
			
			if (!m_context->m_states->IsEmpty()) 
			{
				//m_context->m_states->GetCurrent()->Init();
				m_context->m_states->GetCurrent()->ProcessInput();
				m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
			}
			else
			{
				m_context->m_window->close();
				break;
			}
		}
		if (!m_context->m_states->IsEmpty())
			m_context->m_states->GetCurrent()->Draw();
	}
}