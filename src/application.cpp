#include "application.h"
#include "element.h"

namespace sfui
{
	Application::Application(tinyxml2::XMLElement* e, Application* context) :
		Element(e, context),
		version(e->Attribute("version"))
	{
		std::cout << "Created Application " << e->StringAttribute("id", "") << std::endl;
	}
}

