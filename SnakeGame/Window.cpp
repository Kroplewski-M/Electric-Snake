#include "Window.h"

Window::Window()
{
	Setup("Window", { 640,480 });
}

Window::Window(const std::string& l_tittle, const sf::Vector2u& l_size)
{
	Setup(l_tittle, l_size);
}

Window::~Window()
{
	Destory();
}

void Window::BeginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_isDone = true;
		}
	}
}

bool Window::isDone()
{
	return m_isDone;
}

sf::Vector2u Window::getWindowSize()
{
	return m_windowSize;
}

void Window::Draw(sf::Drawable& l_drawable)
{
	m_window.draw(l_drawable);
}

void Window::Setup(const std::string& l_tittle, const sf::Vector2u& l_size)
{
	m_windowTitle = l_tittle;
	m_windowSize = l_size;
	m_isDone = false;
	Create();
}

void Window::Create()
{
	m_window.create({ m_windowSize.x,m_windowSize.y,32 }, m_windowTitle, sf::Style::Default);
}

void Window::Destory()
{
	m_window.close();
}

