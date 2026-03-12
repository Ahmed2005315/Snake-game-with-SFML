#include "Snake.h"
Snake::Snake() 
{

}
Snake::~Snake(){}

void Snake::Init(const sf::Texture& texture) {
	body.clear();
	float x = 16.f;

	for (int i = 0; i < 4; ++i) {
		sf::Sprite piece(texture);  // construct with texture immediately
		piece.setPosition({ x, 16.f });
		body.push_back(piece);
		x += 16.f;
	}
	head = --body.end();
	tail = body.begin();
}

void Snake::Move(const sf::Vector2f& direction) {
	tail->setPosition(head->getPosition() + direction);
	head = tail;
	++tail;
	if (tail == body.end())
		tail = body.begin();
}

bool Snake::IsOn(const sf::Sprite& other)const {
	return other.getGlobalBounds().findIntersection(head->getGlobalBounds()).has_value();
}

void Snake::Grow(const sf::Vector2f& direction) {
	sf::Sprite NewPeice(body.begin()->getTexture());
	NewPeice.setPosition(head->getPosition() + direction);
	head = body.insert(++head, NewPeice);
}

bool Snake::IsSelfIntersect()const {
	for (auto piece=body.begin();piece!=body.end();++piece)
	{
		if (piece != head) {
			if (IsOn(*piece)) //why *
			{
				return true;
			}
		}
	}
	return false;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& piece : body) {
		target.draw(piece,states);
	}
}