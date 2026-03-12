#pragma once
#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"
class PauseGame :public Engine::State
{
private:
	shared_ptr<Context>m_context;
	sf::Text PauseText;
public:
	PauseGame(shared_ptr<Context>& context);
	~PauseGame();

	void Init() override;
	void ProcessInput() override;
	void Update(const sf::Time& deltaTime) override;
	void Draw() override;
};

