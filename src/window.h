#pragma once
#include "element.h"
#include <string>

#include <SFML/Graphics.hpp>
#include <TinyXML-2/tinyxml2.h>

namespace sfui
{
	class Window : private sf::RenderWindow, public Element
	{
		friend class WindowManager;

	public:
		std::string getTitle() const;
		void setTitle(const std::string title);
		virtual void close() override;
		virtual bool isOpen();

	public:
		Window(tinyxml2::XMLElement* e, Application* context);
		Window(std::string title, int width, int height, Element* content);
		void handle(sf::Event event);
		void redraw();
		void doLayout();

	private:
		std::string title;
		Element* content;
	};
}
