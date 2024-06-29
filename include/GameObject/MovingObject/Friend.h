#pragma once
#include "GameObject/MovingObject/MovingObject.h"

class Level;
class UpDownStrategy;

class Friend : public MovingObject
{
public :
	Friend(sf::Sprite&, std::unique_ptr<UpDownStrategy>, std::pair<sf::IntRect, sf::IntRect>&, Level&);
	virtual void move(sf::Time)override;
	void setHappy();
	bool isHappy()const;


private:
	static bool m_register;
	std::unique_ptr<UpDownStrategy> m_strategy;
	std::pair<sf::IntRect, sf::IntRect> m_friendStatusRect;
	float m_collideWithCageHeight;
	bool m_isHappy;
	Level& m_level;
	sf::Time m_happyTimer;
};
