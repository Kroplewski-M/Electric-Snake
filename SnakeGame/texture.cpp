#include "texture.h"

texture::texture(int width, int height, std::string location)
{
	if (!m_texture.loadFromFile(location))
	{
		std::cout << "cannot load texture";
	}
	m_rec.setSize(sf::Vector2f(width,height) );
	m_rec.setTexture(&m_texture);
}

texture::~texture()
{

}

sf::Texture texture::getTexture()
{
	return m_texture;
}

sf::RectangleShape texture::getFinaltexture()
{
	return m_rec;
}

void texture::Render(Window& window)
{
	window.Draw(m_rec);
}
