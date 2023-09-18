#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <string>

#include <TinyXML-2/tinyxml2.h>
#include <SFML/Graphics.hpp>

#include <any>

#define PRINT_WARNINGS

namespace sfui
{
	class Application;

	class Element
	{


	public:
		Element();
		Element(tinyxml2::XMLElement* e, Application* c);
		void add(Element& e);
		void remove(Element& e);
		virtual void redraw(sf::RenderTarget& target, const sf::RenderStates states, const sf::FloatRect rect);

		void close();
		std::string getID();
		void setID(std::string id);
		void setPreferredSize(float x, float y);
		void setPreferredWidth(float width);
		void setPreferredHeight(float height);
		void setFillColor(sf::Color color);
		void traverse(std::string inset);

		template <typename... Args>
		void call(const std::string& name, Args... args)
		{
			auto fn = get_function<Args...>(name);
			if (fn) fn(args...);
		}

		template <int index, typename... Params> //requires (index < sizeof...(Params))
		using nth_param = typename std::tuple_element_t<index, std::tuple<Params...>>;

		template <int index, typename T, typename... Params> //requires (index < sizeof...(Params))
		using check_nth_param = std::is_convertible<std::tuple_element_t<index, std::tuple<Params...>>, T>;

		template <typename... Params>
		std::function<void(Params...)> get_function(const std::string& name)
		{
			constexpr auto size = sizeof...(Params);

			if constexpr
				(
					size == 2 &&
					//check_nth_param<0, sf::Color,	Params...>::value &&
					//check_nth_param<2, int,			Params...>::value

					std::is_same_v<std::tuple_element_t<0, std::tuple<Params...>>, sf::Color>&&
					std::is_same_v<std::tuple_element_t<1, std::tuple<Params...>>, int>
				)
			{
				if (name == "hello") return [this](sf::Color color, int blue) { std::cout << "oaou" << std::endl; };
			}
			else if constexpr
			(
				size == 2 &&
				std::is_same_v<std::tuple_element_t<0, std::tuple<Params...>>, float> &&
				std::is_same_v<std::tuple_element_t<1, std::tuple<Params...>>, float>
			)
			{
				if (name == "size") return [this](float x, float y) { setPreferredSize(x, y); };
			}
			else if constexpr
			(
				size == 1 &&
				std::is_same_v<std::tuple_element_t<0, std::tuple<Params...>>, float>
			)
			{
				if (name == "width") return [this](float width) { setPreferredWidth(width); };
				if (name == "height") return [this](float height) { setPreferredWidth(height); };
			}
			else if constexpr
			(
				size == 1 &&
				std::is_same_v<std::tuple_element_t<0, std::tuple<Params...>>, std::string>
			)
			{
				if (name == "id") return [this](std::string id) { setID(id); };
			}
			else if constexpr
			(
				size == 0
			)
			{
				if (name == "close") return [this]() { close(); };
			}

#ifdef PRINT_WARNINGS
			std::cout << "Warning: function \"" << name << "\" not found." << std::endl;
#endif

			return nullptr;
		}

		static Element* parse(tinyxml2::XMLElement* e, Application* context = nullptr);

	private:
		std::string id;
		Element* parent;
		std::vector<Element*> children;
	};
}
