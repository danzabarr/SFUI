#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>

#include <sstream>
#include <vector>

#include "rect.h"
#include "vector2_ext.h"

#include "color.h"

using namespace sfui;

int main()
{
	ColorData data(0x00112233);

	Color c1;
	c1.data = data;

	Color c2;
	c2.data = data;

	c1 = 0xDECEA5ED;


	c1 *= 2.f;

	c1 = Color("#DECEA5ED");

	std::cout << "c1: " << c1 << std::endl;
	std::cout << "c2: " << c2 << std::endl;

	return 0;


	Color color("#00112233");
	std::cout << "declare color(\"#00112233\")" << std::endl;

	std::cout << "Red:   " << color.red << std::endl;
	std::cout << "Green: " << color.green << std::endl;
	std::cout << "Blue:  " << color.blue << std::endl;
	std::cout << "Alpha: " << color.alpha << std::endl;
	std::cout << "Color: " << color << std::endl;
	std::cout << std::endl;

	std::cout << "assign color to Color(.2f, .2f, .2f)" << std::endl;
	color = Color(.2f, .2f, .2f) * 2.f;

	std::cout << "Red:   " << color.red << std::endl;
	std::cout << "Green: " << color.green << std::endl;
	std::cout << "Blue:  " << color.blue << std::endl;
	std::cout << "Alpha: " << color.alpha << std::endl;
	std::cout << "Color: " << color << std::endl;
	std::cout << std::endl;
	
	color = 0x99887766;
	std::cout << "assign color to 0x9988776" << std::endl;

	std::cout << "Red:   " << color.red << std::endl;
	std::cout << "Green: " << color.green << std::endl;
	std::cout << "Blue:  " << color.blue << std::endl;
	std::cout << "Alpha: " << color.alpha << std::endl;
	std::cout << "Color: " << color << std::endl;
	std::cout << std::endl;

	color /= 10.f;
	std::cout << "divide color by 10" << std::endl;

	std::cout << "Red:   " << color.red << std::endl;
	std::cout << "Green: " << color.green << std::endl;
	std::cout << "Blue:  " << color.blue << std::endl;
	std::cout << "Alpha: " << color.alpha << std::endl;
	std::cout << "Color: " << color << std::endl;
	std::cout << std::endl;

	std::cout << (color.red == 0.141592653f) << std::endl;

	

//	std::cout << color << std::endl;

	return 0;

	float x0 = 0;
	float x1 = 1;
	float x2 = 2;

	float y0 = 0;
	float y1 = 2;
	float y2 = 3;

	ReferencePoint<float> pr0 = { x0, y0 };
	ReferencePoint<float> pr1 = { x1, y1 };
	ReferencePoint<float> pr2 = { x2, y2 };

	sf::Vector2f vec = { 9, 9 };

	std::cout << "assigning pr0 = vec" << std::endl;
	pr0 = vec;

	std::cout << "0: " << pr0 << std::endl;
	std::cout << "1: " << pr1 << std::endl;
	std::cout << "2: " << pr2 << std::endl;
	std::cout << "v: " << vec << std::endl;
	std::cout << std::endl;

	std::cout << "assigning vec = {3, 3}" << std::endl;
	vec = { 3, 3 };

	std::cout << "0: " << pr0 << std::endl;
	std::cout << "1: " << pr1 << std::endl;
	std::cout << "2: " << pr2 << std::endl;
	std::cout << "v: " << vec << std::endl;

	std::cout << "assigning x0 = 15" << std::endl;
	x0 = 15;

	std::cout << "0: " << pr0 << std::endl;
	std::cout << "1: " << pr1 << std::endl;
	std::cout << "2: " << pr2 << std::endl;
	std::cout << "v: " << vec << std::endl;
	std::cout << std::endl;
	
	std::cout << "assigning pr1.x = 2" << std::endl;
	pr1.x = 2;

	std::cout << "0: " << pr0 << std::endl;
	std::cout << "1: " << pr1 << std::endl;
	std::cout << "2: " << pr2 << std::endl;
	std::cout << "v: " << vec << std::endl;
	std::cout << std::endl;

	std::cout << "assigning pr1 = pr2" << std::endl;
	pr1 = pr2;

	std::cout << "0: " << pr0 << std::endl;
	std::cout << "1: " << pr1 << std::endl;
	std::cout << "2: " << pr2 << std::endl;
	std::cout << "v: " << vec << std::endl;
	std::cout << std::endl;

	std::cout << "assigning pr2.y += 200" << std::endl;
	pr2.y += 200;

	std::cout << "0: " << pr0 << std::endl;
	std::cout << "1: " << pr1 << std::endl;
	std::cout << "2: " << pr2 << std::endl;
	std::cout << "v: " << vec << std::endl;
	std::cout << std::endl;

	return 1;

	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		window.clear(sf::Color::White);

		window.display();
	}


	return 0;
}

#ifdef FALSE
#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include <TinyXML-2/tinyxml2.h>
#include <SFML/Graphics.hpp>

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