#ifndef BASIC_SCENE_HPP
#define BASIC_SCENE_HPP

#include <SFML/Graphics.hpp>

class BasicScene
{
public:
	BasicScene()
		: active(true)
	{
	}
	virtual ~BasicScene(){};

	virtual void initialize(sf::RenderWindow&) = 0;
	virtual BasicScene* update(sf::RenderWindow& window, float) = 0;
	virtual void render(sf::RenderWindow&) = 0;

	bool isActive()
	{
		return active;
	}
protected:
	bool active;
};

#endif //BASIC_SCENE_HPP
