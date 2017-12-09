#ifndef RGLK_LEVEL_HPP
#define RGLK_LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

struct Object {
	std::string name;
	std::string type;
	sf::ConvexShape shape;
};

struct IsometricPatameters {
	float cos;
	float sin;
};

struct Layer {
	int opacity;
	std::vector<sf::Sprite> tiles;
};

class Level {
public:
	bool loadFromFile(std::string filename);
	Object getObject(std::string name);
	std::vector<Object> getObjects(std::string name);
	void draw(sf::RenderWindow& window);
	void drawLayer(sf::RenderWindow& window, int layer);
	sf::Vector2i getTileSize();

private:
	int width, height, tileWidth, tileHeight, firstTileID;
	IsometricPatameters isomtry;
	sf::Texture tilesetImage;
	std::vector<Object> objects;
	std::vector<Layer> layers;
};

#endif //RGLK_LEVEL_HPP
