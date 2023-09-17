#include "window.h"

namespace sfui
{
	Window::Window(tinyxml2::XMLElement* e, Application* context) :
		Element(e, context),
		sf::RenderWindow
		(
			sf::VideoMode
			(
				e->IntAttribute("width", 800),
				e->IntAttribute("height", 600)
			),
			e->StringAttribute("title", "New Window")
		),
		title(e->StringAttribute("title", "New Window")),
		content(nullptr)
	{}

	Window::Window(std::string title, int width, int height, Element* content) :
		sf::RenderWindow(sf::VideoMode(width, height), title),
		title(title),
		content(content)
	{}

	std::string Window::getTitle() const
	{
		return title;
	}

	void Window::setTitle(const std::string title)
	{
		this->title = title; 
		sf::RenderWindow::setTitle(title);
	}

	void Window::close()
	{
		sf::RenderWindow::close();
	}

	bool Window::isOpen()
	{
		return sf::RenderWindow::isOpen();
	}

	void Window::handle(sf::Event event)
	{
		if (event.type == sf::Event::Closed)
		{
			close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				close();
		}

		if (event.type == sf::Event::Resized)
		{
			float width = static_cast<float>(event.size.width);
			float height = static_cast<float>(event.size.height);
			setView(sf::View(sf::FloatRect(0, 0, width, height)));
			doLayout();
		}
	}
	
	void Window::redraw()
	{
		if (content != nullptr)
		{
			content->redraw(*this, sf::RenderStates::Default, sf::FloatRect(0, 0, static_cast<float>(getSize().x), static_cast<float>(getSize().y)));
			display();
		}

	}

	void Window::doLayout() {}
}
