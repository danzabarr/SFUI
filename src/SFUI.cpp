#ifdef FALSE
#else
#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include "tinyxml2.h"

#include "element.h"
#include "control.h"
#include "field.h"
#include "window.h"
#include "vector2_ext.h"


namespace sfui
{
	class Button : public Element, public Control<> {};

	class Toggle : public Element, public Control<bool> {};

	class Slider : public Element, public Control<float, float> {};
}

using namespace sfui;

enum struct MouseEvent
{
	Pressed,
	Released,
	Dragged,
	WheelScrolled,
	Moved,
	Entered,
	Left
};

typedef int MouseButton;

static const MouseButton BUTTON_1 = 0;
static const MouseButton BUTTON_2 = 1;

class MousePressed : public Control<MouseButton, sf::Vector2i> {};
class MouseReleased : public Control<MouseButton, sf::Vector2i> {};
class MouseMoved : public Control<sf::Vector2i> {};

int main()
{

	Element* e1 = new Element();

	Control<float, float>* resizer = new Control<float, float>();

	sf::Color color;
	e1->call("hello", color, 3);// .2f);

	resizer->bind(*e1, "size");
	resizer->push(.5f, .5f);


//	resizer->push(2.2f, 2);

	//tinyxml2::XMLDocument doc;
	//doc.LoadFile("xml/test_app.xml");
	//Element* fromXML = Element::parse(doc.RootElement());
	return 0;

#ifdef IGNORE
	MousePressed mousePressed;
	MouseReleased mouseReleased;
	MouseMoved mouseMoved;

	mousePressed.bind([](MouseButton button, sf::Vector2i position)
	{
		std::cout << "Mouse pressed: " << button << " at " << position << std::endl;
	});

	Button* button = new Button();
	DataModel<>* model = new DataModel<>();
	button->bind(*model);

	delete button;
	model->notify();


	//Element* element = new Element();

	FieldModel* document = new FieldModel();
	Field* field = new Field();
	field->bind(*document);

	Field* field_2 = new Field();
	//field_2->bind(*field);

	document->notify(EventType::APPEND, "Notified from document", CURSOR_END, 0);
	//field->notify(EventType::APPEND, "Notified from field 1", CURSOR_END, 0);
	field->push(EventType::APPEND, "Pushed from field 1", CURSOR_END, 0);
	//field->notify(EventType::APPEND, "Hello, world!", CURSOR_END, 0);

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
				mousePressed.push(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

			if (event.type == sf::Event::MouseButtonReleased)
				mouseReleased.push(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

			if (event.type == sf::Event::MouseMoved)
				mouseMoved.push(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

		}

		window.clear(sf::Color::White);


		window.display();
	}

	return 0;

	Button* button_1 = new Button();
	button_1->bind([]() { std::cout << "Pressed" << std::endl; }); // Binds to a function

	Button* button_2 = new Button();
	Element* folder = new Element();
	button_2->bind(*folder, "close"); // Binds to a function in an element

	Field* field = new Field();
	Document* document = new Document();
	field->bind(*document);
	document->notify(EventType::OVERWRITE, "This is the new text.", CURSOR_BEGINNING, 0);

	button_1->push();
	button_2->push();

	field->push(EventType::APPEND, "a", CURSOR_END, 0);

	return 0;

	tinyxml2::XMLDocument doc;
	doc.LoadFile("xml/test_app.xml");
	tinyxml2::XMLPrinter printer;
	doc.Print(&printer);
	std::cout << printer.CStr();

	std::cout << std::endl << std::endl << std::endl;


	TraverseXMLElement(doc.RootElement());



	return 0;
	sf::Text text;
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setString("Hello, world!");

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		window.clear(sf::Color::White);

		window.draw(text, sf::RenderStates::Default);

		window.display();
	}
#endif // TEST


}
#endif