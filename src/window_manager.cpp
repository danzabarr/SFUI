#include "window_manager.h"

namespace sfui
{
	static std::vector<Window*> windows;

	Window* WindowManager::create(std::string title, int width, int height, Element* content)
	{
		Window* window = new Window(title, width, height, content);
		windows.push_back(window);
		return window;
	}

	Window* WindowManager::create(tinyxml2::XMLElement* e, Application* context)
	{
		Window* window = new Window(e, context);
		windows.push_back(window);
		return window;
	}

	void WindowManager::start()
	{
		for (Window* window : windows)
		{
			window->clear(sf::Color::White);
			window->redraw();
		}

		while (!windows.empty())
		{
			sf::Event event;
			for (Window* window : windows)
				while (window->pollEvent(event))
				{
					window->handle(event);
					window->redraw();
				}

			windows.erase
			(
				std::remove_if
				(
					windows.begin(),
					windows.end(),
					[](Window* window) { return !window->isOpen(); }
				),
				windows.end()
			);
		}
	}

	void WindowManager::close(Window& window)
	{
		windows.erase
		(
			std::remove_if
			(
				windows.begin(),
				windows.end(),
				[&window](Window* w) { return w == &window; }
			),
			windows.end()
		);
		window.close();
	}

	void WindowManager::closeAllWindows()
	{
		for (Window* window : windows)
			window->close();
	}
}
