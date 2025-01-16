#pragma once

#include "Button.h"
#include "Text.h"
#include "TextInput.h"
#include <vector>

/*
===============================================================================

	This class is the parent class for all UIs.
	Every scene only makes use of one UI class and that class inherits from this class.
	UI elements are to be created in the child classes as memeber variables and then appended to the corresponding vector.
	e.g. you might have classes like MainMenuUI, LobbyUI, GameUI
	and in those classes you might have something like Button exitButton; followed by buttons.push_back(exitButton)

	list of elements
	make your element and then appent it's reference to list
	ui.draw will iterate through lists and call UIElement.draw
	Now i can design a whole new ui with member functions for each ui element.
	should i make an event queue? button clicked? 
	the ui object reads from there and calls the corresponding member function which has internal access to other ui elements and pointer to ecs to read

===============================================================================
*/
class UI {
public:
	std::vector<Text>					texts;
	std::vector<Button>					buttons;
	std::vector<TextInput>				textInputs;

	void								draw();
	void								update();
	virtual void						onUpdate() = 0;
};