#include "element.h"
#include "application.h"
#include "window_manager.h"
#include <iostream>

namespace sfui
{
	Element::Element() : parent(nullptr) {}

	Element::Element(tinyxml2::XMLElement* e, Application* c) :
		parent(nullptr),
		id("")
	{
		if (e == nullptr)
			return;

		if (c != nullptr)
			std::cout << "CONTEXT:" << c->getID() << std::endl;

		setID(e->StringAttribute("id"));
		setPreferredWidth(e->FloatAttribute("width"));
		setPreferredHeight(e->FloatAttribute("height"));
	}

	void Element::add(Element& element)
	{
		if (element.parent != nullptr && element.parent != this)
			element.parent->remove(element);
		element.parent = this;
		if (std::find(children.begin(), children.end(), &element) == children.end())
			children.push_back(&element);
	}

	void Element::remove(Element& element)
	{
		children.erase
		(
			std::remove_if
			(
				children.begin(),
				children.end(),
				[&element](Element* e) { return e == &element; }
			),
			children.end()
		);
	}

	void Element::redraw(sf::RenderTarget& target, const sf::RenderStates states, const sf::FloatRect rect)
	{
	}

	void Element::close()
	{
		std::cout << "Closing" << std::endl;
	}

	std::string Element::getID()
	{
		return id;
	}

	void Element::setID(std::string id)
	{
		this->id = id;
	}

	void Element::setPreferredWidth(float width)
	{

	}

	void Element::setPreferredHeight(float height)
	{

	}

	void Element::setPreferredSize(float x, float y)
	{
		std::cout << "Setting size to " << x << ", " << y << std::endl;
	}

	void Element::setFillColor(sf::Color color)
	{

	}

	void Element::traverse(std::string inset)
	{
		std::cout << getID() << std::endl;
		for (Element* e : children)
			e->traverse(inset + "  ");
	}

	Element* Element::parse(tinyxml2::XMLElement* e, Application* context)
	{
		if (e == nullptr)
			return nullptr;

		std::string name = e->Name();
		//std::string text = e->GetText() ? e->GetText() : "";

		Element* element;

		if (name == "Application") element = context = new Application(e, context);
		else if (name == "Window") element = WindowManager::create(e, context);
		else element = new Element(e, context);

		for (tinyxml2::XMLElement* c = e->FirstChildElement(); c; c = c->NextSiblingElement())
		{
			Element* child = Element::parse(c, context);
			if (child != nullptr)
				element->add(*child);
		}

		return element;
	}
}
