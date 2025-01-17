#pragma once

#include "UI.h"

class MainMenuUI : public UI {
public:
	TextInput		test;

					MainMenuUI();
	void			OnUpdate() override;
};