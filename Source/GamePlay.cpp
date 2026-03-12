#include "GamePlay.h"
#include "GameOver.h"
#include "PauseGame.h"

#include <SFML/Window/Event.hpp>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

GamePlay::GamePlay(shared_ptr<Context>& context) :m_context(context)
, cntScore(0), is_paused(false), SnakeDirection(16.f, 0.f),
ElapsedTime(sf::Time::Zero),
Food(m_context->m_assets->GetTexture(FOOD)),
Grass(m_context->m_assets->GetTexture(GRASS)),
Walls{
	sf::Sprite(m_context->m_assets->GetTexture(WALL)),
	sf::Sprite(m_context->m_assets->GetTexture(WALL)),
	sf::Sprite(m_context->m_assets->GetTexture(WALL)),
	sf::Sprite(m_context->m_assets->GetTexture(WALL))
},
Score(m_context->m_assets->GetFont(MAINFONT))
{
	srand(static_cast<unsigned int>(time(nullptr)));
}
GamePlay::~GamePlay(){}

void GamePlay::Init() {
	// m_context->m_assets->AddTexture(FOOD, "assets/Textures/food.png");
	// m_context->m_assets->AddTexture(GRASS, "assets/Textures/grass.png",true);
	// m_context->m_assets->AddTexture(WALL, "assets/Textures/wall.png",true);
	// m_context->m_assets->AddTexture(SNAKE, "assets/Textures/snake.png");
	//Grass full screen
	Grass.setTexture(m_context->m_assets->GetTexture(GRASS));
	Grass.setTextureRect(m_context->m_window->
		getViewport(m_context->m_window->getDefaultView()));
	
	for (auto& wall : Walls) {
		wall.setTexture(m_context->m_assets->GetTexture(WALL));
	}
	//Top wall
	Walls[0].setTextureRect
		(sf::IntRect({ 0,0 }, {(int)m_context->m_window->getSize().x, 16}));
	
	//Bottom wall
	Walls[1].setTextureRect
		(sf::IntRect({ 0,0 }, { (int)m_context->m_window->getSize().x, 16 }));
	Walls[1].setPosition({ 0.f, static_cast<float>( m_context->m_window->getSize().y - 16) });
	
	//left wall
	Walls[2].setTextureRect
	(sf::IntRect({ 0,0 }, { 16,(int)m_context->m_window->getSize().y }));
	
	//right wall
	Walls[3].setTextureRect
	(sf::IntRect({ 0,0 }, { 16,(int)m_context->m_window->getSize().y }));
	Walls[3].setPosition({static_cast<float>(m_context->m_window->getSize().x - 16),0.f });

	//Food it center
	Food.setTexture(m_context->m_assets->GetTexture(FOOD));
	Food.setPosition
		({ static_cast<float>(m_context->m_window->getSize().x / 2),
			static_cast<float>(m_context->m_window->getSize().y / 2 )});
	//Snake
	snake.Init(m_context->m_assets->GetTexture(SNAKE));
	//Score
	Score.setFont(m_context->m_assets->GetFont(MAINFONT));
	Score.setString("Score: " + to_string(cntScore));
	Score.setPosition({ 24.f,0.f });
	Score.setCharacterSize(18);
	Score.setFillColor(sf::Color::Black);

}

void GamePlay::ProcessInput()
{
	while (auto event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>()) {
			m_context->m_states->PopAll();
		}
		else if (const auto* KeyEvent = event->getIf<sf::Event::KeyPressed>())
		{
			sf::Vector2f NewDirection = SnakeDirection;
			switch (KeyEvent->code) {
			case sf::Keyboard::Key::Up:
			{
				NewDirection = { 0.f,-16.f };
				break;
			}
			case sf::Keyboard::Key::Down:
			{
				NewDirection = { 0.f,16.f };
				break;
			}
			case sf::Keyboard::Key::Left:
			{
				NewDirection = { -16.f,0.f };
				break;
			}
			case sf::Keyboard::Key::Right:
			{
				NewDirection = { 16.f,0.f };
				break;
			}
			case sf::Keyboard::Key::Escape:
			{
				m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
				break;
			}
			default:
				break;
			}
			if (abs(SnakeDirection.x) != abs(NewDirection.x) ||
				abs(SnakeDirection.y) != abs(NewDirection.y))
			{
				SnakeDirection = NewDirection;
			}
		}
	}
}


void GamePlay::Update(const sf::Time& deltaTime)
{
	if (!is_paused) {
		ElapsedTime += deltaTime;
		if (ElapsedTime.asSeconds() > 0.1) {
			for (auto& wall : Walls) {
				if (snake.IsOn(wall)) {
					m_context->m_states->Add(make_unique<GameOver>(m_context), true);
					return;
				}
			}
			if (snake.IsOn(Food)) {
				snake.Grow(SnakeDirection);
				int x = 0; int y = 0;
				bool IsValidPosition = false;		// To prevent the food created on snake body
				while (!IsValidPosition) {
					x = clamp<int>(rand() % m_context->m_window->getSize().x, 
						16,
						m_context->m_window->getSize().x - 2 * 16);
					y = clamp<int>(rand() % m_context->m_window->getSize().y,
						16,
						m_context->m_window->getSize().y - 2 * 16);
					Food.setPosition({ static_cast<float>(x),static_cast<float>(y) });
					IsValidPosition = !snake.IsOn(Food);
				}
				cntScore += 1;
				Score.setString("Score: " + to_string(cntScore));
			}
			else
			{
				snake.Move(SnakeDirection);
			}
			if (snake.IsSelfIntersect()) {
				m_context->m_states->Add(make_unique<GameOver>(m_context), true);

			}
			ElapsedTime = sf::Time::Zero;
		}
	}
}

void GamePlay::Draw() {
	m_context->m_window->clear();
	m_context->m_window->draw(Grass);

	for (auto& wall : Walls)
	{
		m_context->m_window->draw(wall);
	}
	m_context->m_window->draw(Food);
	m_context->m_window->draw(snake);
	m_context->m_window->draw(Score);

	m_context->m_window->display();
}

void GamePlay::Pause() {
	is_paused = true;
}
void GamePlay::Start() {
	is_paused = false;

}