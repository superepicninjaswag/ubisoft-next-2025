#pragma once

#include <string>


enum class EventType {
	Click
};

class UIEvent {
public:
	std::string			uiElementName;
	EventType			eventType;

						UIEvent( std::string uiElementName, EventType eventType );
};