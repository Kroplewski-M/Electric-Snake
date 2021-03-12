#pragma once
#include <SFML\Graphics.hpp>


class Window
{
public:
	Window();
	Window(const std::string& l_tittle, const sf::Vector2u& l_size);
	~Window();

	void BeginDraw(); //CLEAR THE WINDOW
	void EndDraw();  //DISPLAY TO SCREEN
	void Update();
	bool isDone();
	sf::Vector2u getWindowSize();
	void Draw(sf::Drawable& l_drawable);
private:
	void Setup(const std::string& l_tittle, const sf::Vector2u& l_size);
	void Destory();
	void Create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullScreen;


};

