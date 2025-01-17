#include "stdafx.h"
#include "DevSandboxUI.h"

DevSandboxUI::DevSandboxUI() {
	// Sandbox Title
	texts.emplace_back();
	texts.back().name = "title";
	texts.back().text = "You are in the SANDBOX!!!";
	texts.back().position.x = 400.0f;
	texts.back().position.y = 512.0f;
}

void DevSandboxUI::OnUpdate() {

}
