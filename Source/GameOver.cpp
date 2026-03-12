#include "GameOver.h"
#include"GamePlay.h"
#include"MainMenu.h"
#include <SFML/Window/Event.hpp>

GameOver::GameOver(shared_ptr<Context>& context) :m_context(context),
gameOverTitle(context->m_assets->GetFont(MAINFONT)),
RetryButton(context->m_assets->GetFont(MAINFONT)),
ExitButton(context->m_assets->GetFont(MAINFONT))
{
	IsRetryButtonSelected = true;
	IsRetryButtonPressed = false;

	IsExitButtonSelected = false;
	IsExitButtonPressed = false;
}
GameOver::~GameOver() {}

/*
void GameOver::Init() {
	//m_context->m_assets->AddFont(MAINFONT, "assets/Fonts/Pacifico-Regular.ttf");
	//Title
	gameOverTitle.setFont(m_context->m_assets->GetFont(MAINFONT));
	gameOverTitle.setString("Game Over");
	gameOverTitle.setOrigin(gameOverTitle.getLocalBounds().getCenter());
	gameOverTitle.setPosition({ static_cast<float>(m_context->m_window->getSize().x / 2),
		static_cast<float>(m_context->m_window->getSize().y / 2 - 150.f )});
	gameOverTitle.setFillColor(sf::Color::Red);
	//Retry Button
	RetryButton.setFont(m_context->m_assets->GetFont(MAINFONT));
	RetryButton.setString("Retry");
	RetryButton.setOrigin(RetryButton.getLocalBounds().getCenter());
	RetryButton.setPosition({ static_cast<float>(m_context->m_window->getSize().x / 2),
		static_cast<float>(m_context->m_window->getSize().y / 2 - 25.f) });
	RetryButton.setCharacterSize(20);

	//Exit Button
	ExitButton.setFont(m_context->m_assets->GetFont(MAINFONT));
	ExitButton.setString("Exit");
	ExitButton.setOrigin(ExitButton.getLocalBounds().getCenter());
	ExitButton.setPosition({ static_cast<float>(m_context->m_window->getSize().x / 2),
		static_cast<float>(m_context->m_window->getSize().y / 2 + 25.f )});
	ExitButton.setCharacterSize(20);
}
*/

void GameOver::Init() {
	auto windowSize = m_context->m_window->getSize();
	float centerX = static_cast<float>(windowSize.x / 2.f);
	float centerY = static_cast<float>(windowSize.y / 2.f);

	// 1. Game Over Title
	gameOverTitle.setFont(m_context->m_assets->GetFont(MAINFONT));
	gameOverTitle.setString("GAME OVER");
	gameOverTitle.setCharacterSize(45); // Bigger for impact
	gameOverTitle.setFillColor(sf::Color::Red);
	gameOverTitle.setOutlineColor(sf::Color::Black);
	gameOverTitle.setOutlineThickness(3.f);

	sf::FloatRect titleBounds = gameOverTitle.getLocalBounds();
	gameOverTitle.setOrigin({
		titleBounds.position.x + titleBounds.size.x / 2.f,
		titleBounds.position.y + titleBounds.size.y / 2.f
		});
	gameOverTitle.setPosition({ centerX, centerY - 140.f });

	// 2. Retry Button
	RetryButton.setFont(m_context->m_assets->GetFont(MAINFONT));
	RetryButton.setString("TRY AGAIN");
	RetryButton.setCharacterSize(25);

	sf::FloatRect retryBounds = RetryButton.getLocalBounds();
	RetryButton.setOrigin({
		retryBounds.position.x + retryBounds.size.x / 2.f,
		retryBounds.position.y + retryBounds.size.y / 2.f
		});
	RetryButton.setPosition({ centerX, centerY + 20.f });

	// 3. Exit Button
	ExitButton.setFont(m_context->m_assets->GetFont(MAINFONT));
	ExitButton.setString("QUIT TO MENU");
	ExitButton.setCharacterSize(20);

	sf::FloatRect exitBounds = ExitButton.getLocalBounds();
	ExitButton.setOrigin({
		exitBounds.position.x + exitBounds.size.x / 2.f,
		exitBounds.position.y + exitBounds.size.y / 2.f
		});
	ExitButton.setPosition({ centerX, centerY + 100.f });
}


void GameOver::ProcessInput()
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
			case sf::Keyboard::Key::Up:
			{
				if (!IsRetryButtonSelected)
				{
					IsRetryButtonSelected = true;
					IsExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Key::Down:
			{
				if (!IsExitButtonSelected)
				{
					IsExitButtonSelected = true;
					IsRetryButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Key::Enter:
			{
				IsExitButtonPressed = false;
				IsRetryButtonPressed = false;
				if (IsRetryButtonSelected)
					IsRetryButtonPressed = true;
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

/*
void GameOver::Update(const sf::Time& deltaTime)
{
	if (IsRetryButtonSelected) {
		RetryButton.setFillColor(sf::Color::Green);
		ExitButton.setFillColor(sf::Color::Black);
	}
	else
	{
		RetryButton.setFillColor(sf::Color::Black);
		ExitButton.setFillColor(sf::Color::Red);
	}
	if (IsRetryButtonPressed) {
		m_context->m_states->Add(make_unique<GamePlay>(m_context), true);
	}
	else if (IsExitButtonPressed)
	{
		m_context->m_states->PopAll();
	}
}

void GameOver::Draw()
{
	m_context->m_window->clear(sf::Color::White);
	m_context->m_window->draw(gameOverTitle);
	m_context->m_window->draw(RetryButton);
	m_context->m_window->draw(ExitButton);
	m_context->m_window->display();
}*/

void GameOver::Update(const sf::Time& deltaTime) {
	if (IsRetryButtonSelected) {
		RetryButton.setFillColor(sf::Color::Green);
		RetryButton.setScale({ 1.1f, 1.1f }); // Selection pop

		ExitButton.setFillColor(sf::Color(100, 100, 100)); // Dimmed
		ExitButton.setScale({ 1.0f, 1.0f });
	}
	else {
		RetryButton.setFillColor(sf::Color(100, 100, 100));
		RetryButton.setScale({ 1.0f, 1.0f });

		ExitButton.setFillColor(sf::Color::Red);
		ExitButton.setScale({ 1.1f, 1.1f });
	}

	if (IsRetryButtonPressed) {
		// Use Replace instead of Add if your state machine supports it 
		// to avoid stacking multiple game states.
		m_context->m_states->Add(make_unique<GamePlay>(m_context), true);
	}
	else if (IsExitButtonPressed) {
		m_context->m_states->Add(make_unique<MainMenu>(m_context));
		//m_context->m_states->PopAll();
	}
}

void GameOver::Draw() {
	// A very dark grey background feels much more "Game Over" than white
	m_context->m_window->clear(sf::Color(15, 15, 15));

	m_context->m_window->draw(gameOverTitle);
	m_context->m_window->draw(RetryButton);
	m_context->m_window->draw(ExitButton);

	m_context->m_window->display();
}