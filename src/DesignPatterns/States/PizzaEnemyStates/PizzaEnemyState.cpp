#include "DesignPatterns/States/PizzaEnemyStates/PizzaEnemyState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"

PizzaEnemyState::PizzaEnemyState(const ObjectAnimation animation): m_animation(ResourceManager::instance().getAnimation(animation)), m_frame(0)
{}