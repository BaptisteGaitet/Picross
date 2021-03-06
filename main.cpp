#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "TitleState.h"
#include "SettingsState.h"
#include "LevelSelectState.h"
#include "MouseManager.h"
#include "WindowManager.h"
#include "Nonogram.h"
#include "Level.h"
#include "LevelManager.h"
#include "GameState.h"
#include "AudioManager.h"

int main()
{
	srand(time(NULL));
	
	LevelManager::getInstance().loadLevels();
	LevelManager::getInstance().loadProgress();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Archeo-Gram");
	WindowManager::getInstance().initialize(&window);
	window.setMouseCursorVisible(false);

	MouseManager::getInstance().setWindow(&window);
	WindowManager::getInstance().updateDisplayArea(window.getSize(), sf::Vector2i(0,0));
	StateManager stateManager;
	TitleState* titleState = new TitleState();
	SettingsState* settingsState = new SettingsState();
	LevelSelectState* levelSelectState = new LevelSelectState();
	GameState* gameState = new GameState();
	stateManager.addState(titleState);
	stateManager.addState(settingsState);
	stateManager.addState(levelSelectState);
	stateManager.addState(gameState);
	stateManager.setCurrentStateId(titleState->getId());

	TextureManager::getInstance().addTexture("img/cursor.png");
	sf::RectangleShape cursor = sf::RectangleShape(sf::Vector2f(32,32));
	cursor.setTexture(TextureManager::getInstance().getTexture("img/cursor.png"));
	cursor.setTextureRect(sf::IntRect(0, 0, 32, 32));

	AudioManager::getInstance().addMusic("msc/ArcheoGram-Title.ogg");
	AudioManager::getInstance().setMusicLoop("msc/ArcheoGram-Title.ogg", true);
	AudioManager::getInstance().playMusic("msc/ArcheoGram-Title.ogg");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || WindowManager::getInstance().getRequestExit())
			{
				window.close();
			}
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				WindowManager::getInstance().updateDisplayArea(window.getSize(), sf::Vector2i(0,0));
			}
		}

		MouseManager::getInstance().update();
		WindowManager::getInstance().update();
		stateManager.update();
		cursor.setPosition(sf::Vector2f(MouseManager::getInstance().getPosition()));

		window.clear();
		
		stateManager.draw(&window);
		window.draw(cursor);

		window.display();
	}
	
	return 0;
}