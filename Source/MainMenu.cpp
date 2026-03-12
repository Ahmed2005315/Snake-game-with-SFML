#include "MainMenu.h"
#include"GamePlay.h"
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(shared_ptr<Context>& context) :m_context(context),
	gameTitle(context->m_assets->GetFont(MAINFONT)),
	PlayButton(context->m_assets->GetFont(MAINFONT)), 
	ExitButton(context->m_assets->GetFont(MAINFONT)) 
{
	IsPlayButtonSelected = true;
	 IsPlayButtonPressed=false;

	 IsExitButtonSelected=false;
	 IsExitButtonPressed=false;
} 
MainMenu::~MainMenu(){}

/*
void MainMenu::Init() {
	//m_context->m_assets->AddFont(MAINFONT, "assets/Fonts/Pacifico-Regular.ttf");
	//Title
	gameTitle.setFont(m_context->m_assets->GetFont(MAINFONT));
	gameTitle.setString("Snake Game");
	gameTitle.setOrigin(gameTitle.getLocalBounds().getCenter());
	gameTitle.setPosition({ static_cast<float>(m_context->m_window->getSize().x / 2),
		static_cast<float>(m_context->m_window->getSize().y / 2 - 150.f )});
	gameTitle.setFillColor(sf::Color::Cyan);
	//Play Button
	PlayButton.setFont(m_context->m_assets->GetFont(MAINFONT));
	PlayButton.setString("Play");
	PlayButton.setOrigin(PlayButton.getLocalBounds().getCenter());
	PlayButton.setPosition({ static_cast<float>(m_context->m_window->getSize().x / 2),
		static_cast<float>(m_context->m_window->getSize().y / 2 - 25.f) });
	PlayButton.setCharacterSize(20);
	
	//Exit Button
	ExitButton.setFont(m_context->m_assets->GetFont(MAINFONT));
	ExitButton.setString("Exit");
	ExitButton.setOrigin(ExitButton.getLocalBounds().getCenter());
	ExitButton.setPosition({ static_cast<float>(m_context->m_window->getSize().x / 2),
		static_cast<float>(m_context->m_window->getSize().y / 2 + 25.f )});
	ExitButton.setCharacterSize(20);
}
*/

void MainMenu::Init() {
	float windowCenterX = static_cast<float>(m_context->m_window->getSize().x / 2.f);
	float windowCenterY = static_cast<float>(m_context->m_window->getSize().y / 2.f);

	// 1. Game Title - Made larger and higher up
	gameTitle.setFont(m_context->m_assets->GetFont(MAINFONT));
	gameTitle.setString("SNAKE ADVENTURE"); // A more dynamic title
	gameTitle.setCharacterSize(45);
	gameTitle.setFillColor(sf::Color::Cyan);
	gameTitle.setOutlineColor(sf::Color::White);
	gameTitle.setOutlineThickness(2.f);

	// Re-center origin after changing character size/string
	sf::FloatRect titleRect = gameTitle.getLocalBounds();
	gameTitle.setOrigin({titleRect.position.x + titleRect.size.x / 2.0f, titleRect.position.y + titleRect.size.y / 2.0f});
	gameTitle.setPosition({ windowCenterX, windowCenterY - 140.f });

	// 2. Play Button - Increased size and distinct color
	PlayButton.setFont(m_context->m_assets->GetFont(MAINFONT));
	PlayButton.setString("START GAME");
	PlayButton.setCharacterSize(25);
	PlayButton.setFillColor(sf::Color::Green);

	//sf::FloatRect playRect = PlayButton.getLocalBounds();
	sf::FloatRect playRect = PlayButton.getLocalBounds();
	//PlayButton.setOrigin(playRect.left + playRect.width / 2.0f, playRect.top + playRect.height / 2.0f);
	PlayButton.setOrigin({ playRect.position.x + playRect.size.x / 2.f, playRect.position.y + playRect.size.y / 2.f });
	PlayButton.setPosition({ windowCenterX, windowCenterY });

	// 3. Exit Button - Positioned further down for better breathing room
	ExitButton.setFont(m_context->m_assets->GetFont(MAINFONT));
	ExitButton.setString("EXIT");
	ExitButton.setCharacterSize(25);
	ExitButton.setFillColor(sf::Color::White);

	//sf::FloatRect exitRect = ExitButton.getLocalBounds();
	sf::FloatRect exitRect = ExitButton.getLocalBounds();
	//ExitButton.setOrigin(exitRect.left + exitRect.width / 2.0f, exitRect.top + exitRect.height / 2.0f);
	ExitButton.setOrigin({ exitRect.position.x + exitRect.size.x / 2.f, exitRect.position.y + exitRect.size.y / 2.f });
	ExitButton.setPosition({ windowCenterX, windowCenterY + 80.f });
}


void MainMenu::ProcessInput()
{
	if (!IsPaused) {
		while (auto event = m_context->m_window->pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				m_context->m_states->PopAll();
			}
			else if (const auto* KeyEvent = event->getIf<sf::Event::KeyPressed>())
			{
				switch (KeyEvent->code)
				{
				case sf::Keyboard::Key::Up:
				{
					if (!IsPlayButtonSelected)
					{
						IsPlayButtonSelected = true;
						IsExitButtonSelected = false;
					}
					break;
				}
				case sf::Keyboard::Key::Down:
				{
					if (!IsExitButtonSelected)
					{
						IsExitButtonSelected = true;
						IsPlayButtonSelected = false;
					}
					break;
				}
				case sf::Keyboard::Key::Enter:
				{
					IsPlayButtonPressed = false;
					IsExitButtonPressed = false;
					if (IsPlayButtonSelected)
						IsPlayButtonPressed = true;
					else
						IsExitButtonPressed = true;
					break;
				}
				default:
					break;
				}
			}



		}
	}
}

void MainMenu::Update(const sf::Time& deltaTime) 
{
	if (!IsPaused) {
		if (IsPlayButtonSelected) {
			//PlayButton.setFillColor(sf::Color::Green);
			//ExitButton.setFillColor(sf::Color::Black);
			PlayButton.setFillColor(sf::Color::Green);
			PlayButton.setScale({ 1.2f, 1.2f }); // Slight "pop" effect

			ExitButton.setFillColor(sf::Color(150, 150, 150)); // Dimmed Gray
			ExitButton.setScale({ 1.0f, 1.0f });
		}
		else
		{
			//PlayButton.setFillColor(sf::Color::Black);
			//ExitButton.setFillColor(sf::Color::Red);
			PlayButton.setFillColor(sf::Color(150, 150, 150)); // Dimmed Gray
			PlayButton.setScale({ 1.0f, 1.0f });

			ExitButton.setFillColor(sf::Color::Red);
			ExitButton.setScale({ 1.2f, 1.2f }); // Slight "pop" effect
		}
		if (IsPlayButtonPressed) {
			m_context->m_states->Add(make_unique<GamePlay>(m_context),true);
		}
		else if (IsExitButtonPressed)
		{
			m_context->m_states->PopAll();
		}
	}
}
/*
void MainMenu::Draw()
{
	m_context->m_window->clear(sf::Color::Blue);
	m_context->m_window->draw(gameTitle);
	m_context->m_window->draw(PlayButton);
	m_context->m_window->draw(ExitButton);
	m_context->m_window->display();
}
*/

void MainMenu::Draw()
{
	// Using a softer Dark Blue or Charcoal for a more modern look
	m_context->m_window->clear(sf::Color(20, 20, 40));

	m_context->m_window->draw(gameTitle);
	m_context->m_window->draw(PlayButton);
	m_context->m_window->draw(ExitButton);

	m_context->m_window->display();
}

void MainMenu::Pause() { IsPaused = true; }
void MainMenu::Start() { IsPaused = false; }