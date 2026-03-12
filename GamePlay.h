#pragma once
#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.h"
#include "State.h"
#include "Snake.h"

class GamePlay :public Engine::State
{
private:
	shared_ptr<Context>m_context;
	
	sf::Sprite Food;
	sf::Sprite Grass;
	array<sf::Sprite,4> Walls;
	Snake snake;
	
	sf::Text Score;
	int cntScore;
	
	sf::Vector2f SnakeDirection;
	sf::Time ElapsedTime;
	
	bool is_paused;
	
	
public:
	GamePlay(shared_ptr<Context>& context);
	~GamePlay();
	 void Init() override;
	 void ProcessInput() override;
	 void Update(const sf::Time& deltaTime) override;
	 void Draw() override;
	 void Pause() override;
	 void Start() override;
};

