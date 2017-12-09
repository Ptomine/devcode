#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "../../Core/include/GameSceneManager.hpp"

class MainMenu : public BasicScene
{
public:
	MainMenu();
	~MainMenu();

	void initialize(sf::RenderWindow&);
	BasicScene* update(sf::RenderWindow&, float);
	void render(sf::RenderWindow&);
private:
	enum MainMenuButtons
	{
		BUTTON_QUIT,
		BUTTON_PLAY,
	};
	unsigned selected;
	sf::Font font;
	sf::Text logo;
	sf::Text playButton;
	sf::Text quitButton;
};

#endif //MAIN_MENU_HPP
