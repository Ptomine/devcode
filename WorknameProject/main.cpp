#include "Core/include/GameSceneManager.hpp"
#include "Scenes/include/MainMenu.hpp"

void windowStateManager(sf::RenderWindow& window)
{
	sf::Event state;
	while(window.pollEvent(state))
	{
		switch(state.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}




int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "</> WorkName project", sf::Style::Close);

	GameSceneManager gameScene(window, new MainMenu);

	float deltaTime = 0.0f;
	sf::Clock clock;

	while(window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		windowStateManager(window);

		window.clear();

		gameScene.update(deltaTime);

		window.display();
	}
	return 0;
}
