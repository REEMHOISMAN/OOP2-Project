#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	void playSound(const std::string&,bool val=false);
	void setSoundStatus();

private:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager();
	void initAnimations();
	void initTextures();
	void initSounds();
	void failedLoad(const std::string) const;


	std::unordered_map<std::string, sf::Texture>m_textures;
	std::unordered_map<ObjectAnimation, std::vector<sf::IntRect>> m_animations;
	std::unordered_map<std::string, sf::SoundBuffer> m_sounds;
	sf::Font m_font;
	sf::Sound m_currentSound;
	bool m_muteSound;
};