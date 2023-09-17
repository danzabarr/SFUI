#pragma once

#include "element.h"
#include "tinyxml2.h"

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
