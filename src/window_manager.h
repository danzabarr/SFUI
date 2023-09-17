#pragma once
#include <string>

#include "tinyxml2.h"

#include "window.h"
#include "element.h"
#include "application.h"

namespace sfui
{
	class WindowManager
	{
	public:
		WindowManager() = delete;
		WindowManager(const WindowManager&) = delete;
		static Window* create(std::string title, int width, int height, Element* content);
		static Window* create(tinyxml2::XMLElement* e, Application* context);

		static void start();
		static void close(Window& window);
		static void closeAllWindows();
	};
}
