#include "../include/MainMenu.hpp"
#include "../include/DemoLevel.hpp"

MainMenu::MainMenu()
	: BasicScene()
{
}




MainMenu::~MainMenu()
{
}




void MainMenu::initialize(sf::RenderWindow& window)
{
	font.loadFromFile("WorknameProject/Fonts/MainMenuFont.ttf");

	logo = sf::Text("</> WorkName Project", font, 64U);
	logo.setOrigin(logo.getGlobalBounds().width / 2.0f, 0.0f);
	logo.setPosition(window.getSize().x / 2.0f, 0.0f);

	playButton = sf::Text("Play", font, 44U);
	playButton.setOrigin(playButton.getGlobalBounds().width / 2.0f, 0.0f);
	playButton.setPosition(window.getSize().x / 2.0f, logo.getGlobalBounds().height * 1.5f);

	quitButton = sf::Text("Quit", font, 44U);
	quitButton.setOrigin(quitButton.getGlobalBounds().width / 2.0f, 0.0f);
	quitButton.setPosition(window.getSize().x / 2, logo.getGlobalBounds().height * 1.5f + playButton.getGlobalBounds().height * 1.5f);

	selected = BUTTON_PLAY;
}




BasicScene* MainMenu::update(sf::RenderWindow& window, float)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && selected > BUTTON_QUIT)
	{
		selected--;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && selected < BUTTON_PLAY)
	{
		selected++;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		switch(selected)
		{
		case BUTTON_QUIT:
			window.close();
			break;
		case BUTTON_PLAY:
			active = false;
			return new DemoLevel;
		}
	}
	return this;
}




void MainMenu::render(sf::RenderWindow& window)
{
	playButton.setColor(sf::Color::White);
	quitButton.setColor(sf::Color::White);

	switch(selected)
	{
	case BUTTON_QUIT:
		quitButton.setColor(sf::Color(128, 0, 0));
		break;
	case BUTTON_PLAY:
		playButton.setColor(sf::Color(128, 0, 0));
		break;
	}
	window.draw(logo);
	window.draw(playButton);
	window.draw(quitButton);
}
