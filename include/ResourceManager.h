#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
	static ResourceManager& instance();
	sf::Texture& getTexture(const std::string);

private:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager();
	void initTextures();
	void failedLoad(const std::string) const;

	std::unordered_map<std::string, sf::Texture>m_textures;
	sf::Font m_font;
};