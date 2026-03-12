#pragma once
#include<memory>
#include <SFML/Graphics/Text.hpp>
#include"State.h"
#include"Game.h"
using namespace std;
class MainMenu:public Engine::State
{
private:
	bool IsPaused = false;
	shared_ptr<Context>m_context;
	sf::Text gameTitle;
	sf::Text PlayButton;
	sf::Text ExitButton;

	bool IsPlayButtonSelected;
	bool IsPlayButtonPressed;

	bool IsExitButtonSelected;
	bool IsExitButtonPressed;

public:
	MainMenu(shared_ptr<Context>&context);
	~MainMenu();
	 void Init() override;
	 void ProcessInput() override;
	 void Update(const sf::Time& deltaTime) override;
	 void Draw() override;
	 void Pause() override;
	 void Start() override ;
};

