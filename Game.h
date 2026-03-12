#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>//to draw graphics and event handling
#include "Asset_Manager.h" //load Textures & Fonts
#include "State_Manger.h" //manage game states MainMenu, GamePause,...
using namespace std;
struct Context {
	unique_ptr<Engine::Asset_Manager>m_assets;
	unique_ptr<Engine::State_Manger>m_states;
	unique_ptr<sf::RenderWindow>m_window;
	
	Context() {
		m_assets=make_unique<Engine::Asset_Manager>();
		m_states = make_unique<Engine::State_Manger>();
		m_window = make_unique<sf::RenderWindow>();
	}
};
enum AsssetID {
	MAINFONT = 0,
	GRASS,
	FOOD,
	WALL,
	SNAKE
};

class Game
{
private:
	shared_ptr<Context>m_context;
	const sf::Time TIME_PER_FRAME =sf::seconds( 1.f / 60.f);
public:
	Game();
	~Game();

	void Run();
};

