#pragma once

#include "element.h"
#include "control.h"

#include <iostream>
#include <SFML/Graphics.hpp>

namespace sfui
{
	typedef int CursorPosition;
	typedef int SelectionLength;

	const CursorPosition CURSOR_BEGINNING = 0;
	const CursorPosition CURSOR_END = -1;

    enum struct EventType
    {
        APPEND,
        OVERWRITE,
        SELECT
    };

    std::ostream& operator<<(std::ostream& os, const EventType& type) {
        switch (type) 
        {
            case EventType::APPEND: return os << "APPEND";
			case EventType::OVERWRITE: return os << "OVERWRITE";
			case EventType::SELECT: return os << "SELECT";
			default: return os << "UNKNOWN";
        }
        return os;
    }

	typedef DataModel<EventType, std::string, CursorPosition, SelectionLength> FieldModel;

	class Field : public Control<EventType, std::string, CursorPosition, SelectionLength> 
	{ };
}
