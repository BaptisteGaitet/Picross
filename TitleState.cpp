#include "TitleState.h"

// Calls State constructor and initialize id as "title"
TitleState::TitleState() : State("title")
{
	// TEST //
	UIBackground* bg = new UIBackground("background", 0, "img/bg3.png");
	uiholder.addUIElement(bg);
	UIImage* img = new UIImage("image", sf::IntRect(400, 0, 400, 600), 1, "img/cover.png");
	uiholder.addUIElement(img);
	UIButton* btnStart = new UIButton("btn_start", sf::IntRect(550, 300, 128, 64), 2, "img/btn1.png");
	uiholder.addUIElement(btnStart);
	UIButton* btnSettings = new UIButton("btn_settings", sf::IntRect(550, 380, 128, 64), 2, "img/btn2.png");
	uiholder.addUIElement(btnSettings);
	UIButton* btnExit = new UIButton("btn_exit", sf::IntRect(550, 460, 128, 64), 2, "img/btn3.png");
	uiholder.addUIElement(btnExit);
	//////////
}

// Updates the state
void TitleState::update()
{
	uiholder.update();

	UIButton* btnExit = (UIButton*)uiholder.getUIElement("btn_exit");
	if (btnExit->getClic())
	{
		WindowManager::getInstance().setRequestExit(true);
	}

	UIButton* btnSettings = (UIButton*)uiholder.getUIElement("btn_settings");
	if (btnSettings->getClic())
	{
		setNextStateId("settings");
	}

	UIButton* btnStart = (UIButton*)uiholder.getUIElement("btn_start");
	if (btnStart->getClic())
	{
		setNextStateId("levelselect");
	}
}

// Draws the state
void TitleState::draw(sf::RenderWindow* window)
{
	uiholder.draw(window);
}

TitleState::~TitleState()
{
}
