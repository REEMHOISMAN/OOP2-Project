#pragma once
#include "States/PlayerState/PlayerState.h"
#include "Entity.h"
#include "Macros.h"

const sf::Time ANIMATION_TIME = sf::seconds(0.1f);
using AnimationType = std::vector<sf::IntRect>;

class Player :public Entity
{
public:
    Player(sf::Sprite&);
	void move(sf::Time);
	Input getUserInput()const;
	void draw(sf::RenderWindow&)const override ;
	void setPosition(const sf::Vector2f& pos);

	void setAnimationRect(PlayerStateTypes state, sf::Time delta);

private:
	std::unique_ptr<PlayerState> m_state;
	bool m_rightDirection;

	std::unordered_map<PlayerStateTypes, AnimationType> m_animation;
	int m_animationIndex;
	sf::Time m_elapsed;
};