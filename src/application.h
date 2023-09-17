#pragma once

#include <TinyXML-2/tinyxml2.h>

#include "element.h"

namespace sfui
{
	class Application : public Element
	{
	public:
		Application(tinyxml2::XMLElement* e, Application* context);

	public:
		const std::string version;
	};
}
