#include "stdafx.h"
#include "UIEvent.h"

UIEvent::UIEvent(std::string uiElementName, EventType eventType)
	: uiElementName(uiElementName), eventType(eventType) {

}
