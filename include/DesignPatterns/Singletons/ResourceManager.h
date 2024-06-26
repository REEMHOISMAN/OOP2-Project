#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Macros.h"


class ResourceManager
{
public:
	static ResourceManager& instance();
	sf::Texture& getTexture(const std::string);
	sf::Font& getFont();
	std::vector<sf::IntRect>& getAnimation(const ObjectAnimation);

private:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager();
	void initAnimations();
	void initTextures();
	void failedLoad(const std::string) const;

	std::unordered_map<std::string, sf::Texture>m_textures;
	std::unordered_map<ObjectAnimation, std::vector<sf::IntRect>> m_animations;
	sf::Font m_font;
};