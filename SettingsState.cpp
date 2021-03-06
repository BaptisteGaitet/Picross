#include "SettingsState.h"


SettingsState::SettingsState() : State("settings")
{
	warning = false;
	// TEST //

	UIBackground* bg = new UIBackground("background", 0, "img/bg5.png");
	uiholder.addUIElement(bg);
	UIImage* img = new UIImage("image", sf::IntRect(0, 0, 800, 600), 1, "img/book.png");
	uiholder.addUIElement(img);
	UIImage* sketch = new UIImage("sketch", sf::IntRect(400, 50, 300, 500), 1, "img/settingsSketch.png");
	uiholder.addUIElement(sketch);

	UIButton* btnBack = new UIButton("btn_back", sf::IntRect(100, 500, 64, 64), 2, "img/btn4.png");
	uiholder.addUIElement(btnBack);

	UILabel* lblMusic = new UILabel("lbl_music", sf::Vector2f(120, 70), 30, 2, "Music volume");
	uiholder.addUIElement(lblMusic);
	UISlider* sldMusic = new UISlider("sld_music", sf::IntRect(120, 120, 250, 20), 3);
	uiholder.addUIElement(sldMusic);

	UILabel* lblSfx= new UILabel("lbl_sfx", sf::Vector2f(120, 150), 30, 2, "Sound effects volume");
	uiholder.addUIElement(lblSfx);
	UISlider* sldSfx = new UISlider("sld_sfx", sf::IntRect(120, 200, 250, 20), 3);
	uiholder.addUIElement(sldSfx);

	UILabel* lblFull= new UILabel("lbl_full", sf::Vector2f(120, 270), 30, 2, "Fullscreen");
	uiholder.addUIElement(lblFull);
	UIButton* btnFullOn = new UIButton("btn_full_on", sf::IntRect(270, 272, 64, 64), 2, "img/btnFullOn.png");
	uiholder.addUIElement(btnFullOn);
	UIButton* btnFullOff = new UIButton("btn_full_off", sf::IntRect(270, 272, 64, 64), 2, "img/btnFullOff.png");
	uiholder.addUIElement(btnFullOff);

	UILabel* lblReset = new UILabel("lbl_reset", sf::Vector2f(120, 390), 30, 2, "Reset save");
	uiholder.addUIElement(lblReset);
	UIButton* btnBomb= new UIButton("btn_bomb", sf::IntRect(270, 392, 64, 64), 2, "img/btnBomb.png");
	uiholder.addUIElement(btnBomb);

	UIImage* imgWarning = new UIImage("img_warning", sf::IntRect(250, 100, 300, 400), 3, "img/sheet.png");
	imgWarning->setEnabled(false);
	uiholder.addUIElement(imgWarning);
	UILabel* lblWarning = new UILabel("lbl_warning", sf::Vector2f(280, 200), 40, 4, "Are you sure ?");
	lblWarning->setEnabled(false);
	uiholder.addUIElement(lblWarning);
	UIButton* btnYes = new UIButton("btn_yes", sf::IntRect(290, 350, 64, 64), 4, "img/btnYes.png");
	btnYes->setEnabled(false);
	uiholder.addUIElement(btnYes);
	UIButton* btnNo = new UIButton("btn_no", sf::IntRect(450, 350, 64, 64), 4, "img/btnNo.png");
	btnNo->setEnabled(false);
	uiholder.addUIElement(btnNo);

	//////////
}

// Updates the state
void SettingsState::update()
{
	uiholder.update();
	if (!warning)
	{
		UIButton* btnBack = (UIButton*)uiholder.getUIElement("btn_back");
		if (btnBack->getClic())
		{
			setNextStateId("title");
		}

		UIButton* btnFullOff = (UIButton*)uiholder.getUIElement("btn_full_off");
		UIButton* btnFullOn = (UIButton*)uiholder.getUIElement("btn_full_on");
		if (WindowManager::getInstance().getFullscreen())
		{
			btnFullOn->setEnabled(true);
			btnFullOff->setEnabled(false);
		}
		else
		{
			btnFullOn->setEnabled(false);
			btnFullOff->setEnabled(true);
		}

		if (btnFullOff->getClic())
		{
			WindowManager::getInstance().setFullscreen(true);
		}

		if (btnFullOn->getClic())
		{
			WindowManager::getInstance().setFullscreen(false);
		}

		UIButton* btnBomb = (UIButton*)uiholder.getUIElement("btn_bomb");
		UIImage* imgWarning = (UIImage*)uiholder.getUIElement("img_warning");
		UILabel* lblWarning = (UILabel*)uiholder.getUIElement("lbl_warning");
		UIButton* btnYes = (UIButton*)uiholder.getUIElement("btn_yes");
		UIButton* btnNo = (UIButton*)uiholder.getUIElement("btn_no");
		if (btnBomb->getClic())
		{
			warning = true;

			imgWarning->setEnabled(true);
			lblWarning->setEnabled(true);
			btnYes->setEnabled(true);
			btnNo->setEnabled(true);
		}

		UISlider* sldSfx = (UISlider*)uiholder.getUIElement("sld_sfx");
		UISlider* sldMusic = (UISlider*)uiholder.getUIElement("sld_music");
		if (sldSfx->hasChanged())
		{
			AudioManager::getInstance().setSoundVolume(sldSfx->getAmount());
		}
		if (sldMusic->hasChanged())
		{
			AudioManager::getInstance().setMusicVolume(sldMusic->getAmount());
		}
	}
	else
	{
		UIButton* btnYes = (UIButton*)uiholder.getUIElement("btn_yes");
		UIButton* btnNo = (UIButton*)uiholder.getUIElement("btn_no");
		UIImage* imgWarning = (UIImage*)uiholder.getUIElement("img_warning");
		UILabel* lblWarning = (UILabel*)uiholder.getUIElement("lbl_warning");
		if (btnYes->getClic())
		{
			imgWarning->setEnabled(false);
			lblWarning->setEnabled(false);
			btnYes->setEnabled(false);
			btnNo->setEnabled(false);
			warning = false;
			LevelManager::getInstance().resetProgress();
			LevelManager::getInstance().loadProgress();
		}
		else if (btnNo->getClic())
		{
			imgWarning->setEnabled(false);
			lblWarning->setEnabled(false);
			btnYes->setEnabled(false);
			btnNo->setEnabled(false);
			warning = false;
		}
	}
}

// Draws the state
void SettingsState::draw(sf::RenderWindow* window)
{
	uiholder.draw(window);
}


SettingsState::~SettingsState()
{
}
