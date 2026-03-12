#pragma once
#include<memory>
#include <SFML/Graphics/Text.hpp>
#include"State.h"
#include"Game.h"
using namespace std;
class GameOver :public Engine::State
{
private:

	shared_ptr<Context>m_context;
	sf::Text gameOverTitle;
	sf::Text RetryButton;
	sf::Text ExitButton;

	bool IsRetryButtonSelected;
	bool IsRetryButtonPressed;

	bool IsExitButtonSelected;
	bool IsExitButtonPressed;

public:
	GameOver(shared_ptr<Context>& context);
	~GameOver();
	void Init() override;
	void ProcessInput() override;
	void Update(const sf::Time& deltaTime) override;
	void Draw() override;
};


