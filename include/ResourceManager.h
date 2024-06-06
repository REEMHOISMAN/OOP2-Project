#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "States/PlayerState/PlayerState.h"
#include "Macros.h"

using AnimationType = std::vector<sf::IntRect>;

class ResourceManager
{
public:
	static ResourceManager& instance();
	sf::Texture& getTexture(const std::string);
	sf::IntRect& getAnimationRect(PlayerStateTypes);

private:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager();
	void initTextures();
	void failedLoad(const std::string) const;

	std::unordered_map<std::string, sf::Texture>m_textures;
	std::unordered_map<PlayerStateTypes, AnimationType> m_animation;
	sf::Font m_font;
};