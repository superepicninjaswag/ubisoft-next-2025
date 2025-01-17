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

===============================================================================
*/
class UI {
public:
	std::vector<Text>					texts;
	std::vector<Button>					buttons;
	std::vector<TextInput>				textInputs;

	void								Draw();
	void								Update();
	virtual void						OnUpdate() = 0;
};