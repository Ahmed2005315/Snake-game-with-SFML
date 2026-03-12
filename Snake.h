#pragma once
#include<list>
#include <SFML/Graphics/Texture.hpp>	//image
#include <SFML/Graphics/Sprite.hpp>		//image on screen
#include <SFML/Graphics/Drawable.hpp>	//make snake be drawn using window
#include <SFML/Graphics/RenderTarget.hpp>//required for custom drawing
#include <SFML/Graphics/RenderStates.hpp>	
using namespace std;
class Snake:public sf::Drawable
{
private:
	list<sf::Sprite>body;
	list<sf::Sprite>::iterator head;
	list<sf::Sprite>::iterator tail;
public:
	Snake();
	~Snake();

	void Init(const sf::Texture &texture);
	
	void Move(const sf::Vector2f &direction);
	void Grow(const sf::Vector2f& direction);

	bool IsOn(const sf::Sprite& other)const;
	bool IsSelfIntersect()const;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

