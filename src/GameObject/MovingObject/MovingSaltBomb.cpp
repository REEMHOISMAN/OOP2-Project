#include "GameObject/MovingObject/MovingSaltBomb.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"

/*================== MovingSaltBomb Constructor =================*/
MovingSaltBomb::MovingSaltBomb(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy,bool rightDirection)
	:Weapon(sprite, std::move(strategy), rightDirection), m_toExplode(false), m_frame(0), m_elapsed(sf::seconds(0.f)), m_jumps(0)
{
	m_explodeAnimation =ResourceManager::instance().getAnimation(EXPLOSION);
}

/*================== move =================*/
void MovingSaltBomb::move(const sf::Time& time)
{
	if (m_toExplode) {
		updateExplodeAnimation(time);
		return;
	}
	if (!m_toExplode)
		activateGravity(0.2f);

	Weapon::move(time);
}

/*================== setExplode =================*/
void MovingSaltBomb::setExplode()
{
	m_toExplode = true;
}

/*================== isExplode =================*/
bool MovingSaltBomb::isExplode()const
{
	return m_toExplode;
}

/*================== setJumps =================*/
void MovingSaltBomb::setJumps()
{
	m_jumps++;
}

/*================== getJumps =================*/
int MovingSaltBomb::getJumps() const
{
	return m_jumps;
}

/*================== updateExplodeAnimation =================*/
void MovingSaltBomb::updateExplodeAnimation(sf::Time time)
{
	m_elapsed += time;
	if (m_elapsed >= sf::seconds(0.15f))
	{
		m_elapsed -= sf::seconds(0.15f);
		++m_frame;
		m_frame %= m_explodeAnimation.size();
		setTextureRect(m_explodeAnimation[m_frame]);
	}
	if (m_frame == m_explodeAnimation.size()-1)
		setToErase();
}

