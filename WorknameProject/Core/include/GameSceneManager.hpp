#ifndef GAME_SCENE_MANAGER_HPP
#define GAME_SCENE_MANAGER_HPP

#include <stack>
#include "BasicScene.hpp"

class GameSceneManager
{
public:
	GameSceneManager(sf::RenderWindow&, BasicScene*);
	~GameSceneManager();

	void update(float);

	void pushScene(BasicScene*);
private:
	sf::RenderWindow& window;
	std::stack<BasicScene*, std::deque<BasicScene*>> scenes;
};

#endif //GAME_SCENE_MANAGER_HPP
