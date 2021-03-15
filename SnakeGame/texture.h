#pragma once
#include <SFMl/Graphics.hpp>
#include <iostream>
#include "Window.h"

class texture
{
public:
	texture(int width,int height,std::string location);
	~texture();
	sf::Texture getTexture();
	sf::RectangleShape getFinaltexture();
	void Render(Window& window);
private:
	sf::RectangleShape m_rec;
	sf::Texture m_texture;
};

