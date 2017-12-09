#include <tinyxml.h>
#include <cmath>
#include "../include/Level.hpp"

bool Level::loadFromFile(std::string filename) {
	TiXmlDocument levelfile(filename);
	if(!levelfile.LoadFile()) {
		std::cout << "Loading the level failed." << std::endl;
		return false;
	}

	TiXmlElement* map = levelfile.FirstChildElement("map");

	width = atoi(map->Attribute("width"));
	height = atoi(map->Attribute("height"));
	tileWidth = atoi(map->Attribute("tilewidth"));
	tileHeight = atoi(map->Attribute("tileheight"));

	int pX = tileWidth / 2;
	int pY = tileHeight /2;
	float tileSide = sqrtf(powf(pX, 2) + powf(pY, 2));
	isomtry.cos = pX / tileSide;
	isomtry.sin = pY / tileSide;

	TiXmlElement* tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	TiXmlElement* image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");

	sf::Image img;
	if(!img.loadFromFile(imagepath)) {
		std::cout << "Failed to load the tileset." << std::endl;
		return false;
	}

	img.createMaskFromColor(sf::Color(255, 0, 255));
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);

	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	std::vector<sf::Rect<int>> subRects;

	for(int y = 0; y < rows; y++) {
		for(int x = 0; x < columns; x++) {
			sf::Rect<int> rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}
	}

	TiXmlElement* layerElement = map->FirstChildElement("layer");
	while(layerElement) {
		Layer layer;
		if(layerElement->Attribute("opacity") != nullptr) {
			float opacity = strtof(layerElement->Attribute("opacity"), nullptr);
			layer.opacity = 255*opacity;
		} else {
			layer.opacity = 255;
		}

		TiXmlElement* layerDataElement = layerElement->FirstChildElement("data");
		if(layerDataElement == nullptr) {
			std::cout << "No layer information found." << std::endl;
			return false;
		}

		int x = 0;
		int y = 0;
		std::stringstream ss(layerDataElement->GetText());
		int tileGID = 0;

		while(ss >> tileGID) {
			int subRectToUse = tileGID - firstTileID;
			if(subRectToUse >= 0) {
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(-pX + pX * (x-y), pY * (x+y));
				sprite.setColor(sf::Color(255,255,255,layer.opacity));

				layer.tiles.push_back(sprite);
			}

			x++;
			if(x >= width) {
				x = 0;
				y++;
				if(y >= height) {
					y = 0;
				}
			}

			if(ss.peek() == ',') {
				ss.ignore();
			}
		}

		layers.push_back(layer);
		layerElement = layerElement->NextSiblingElement("layer");
	}

	TiXmlElement* objectGroupElement;

	if(map->FirstChildElement("objectgroup") != nullptr) {
		objectGroupElement = map->FirstChildElement("objectgroup");
		while(objectGroupElement) {
			TiXmlElement* objectElement = objectGroupElement->FirstChildElement("object");
			while(objectElement) {
				std::string objectType;
				if(objectElement->Attribute("type") != nullptr) {
					objectType = objectElement->Attribute("type");
				}
				std::string objectName;
				if(objectElement->Attribute("name") != nullptr) {
					objectName = objectElement->Attribute("name");
				}

				float x[4] = {strtof(objectElement->Attribute("x"), nullptr), 0, 0, 0};
				float y[4] = {strtof(objectElement->Attribute("y"), nullptr), 0, 0, 0};
				float width = strtof(objectElement->Attribute("width"), nullptr);
				float height = strtof(objectElement->Attribute("height"), nullptr);
				x[1] = x[0];
				x[2] = x[1] + width;
				x[3] = x[2];
				y[1] = y[0] + height;
				y[2] = y[1];
				y[3] = y[0];

				for(int i = 0; i < 4; i++) {
					float a = x[i];
					float b = y[i];
					x[i] = ((b * (-isomtry.cos) + a * isomtry.cos) / isomtry.cos);
					y[i] = ((b * isomtry.sin + a * isomtry.sin) / isomtry.cos);
				}

				Object object;
				object.name = objectName;
				object.type = objectType;

				sf::ConvexShape objectShape(4);
				for(unsigned int i = 0; i < 4; i++) {
					objectShape.setPoint(i, sf::Vector2f(x[i], y[i]));
				}
				object.shape = objectShape;

				objects.push_back(object);

				objectElement = objectElement->NextSiblingElement("object");
			}

			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	} else {
		std::cout << "No objects layers found..." << std::endl;
	}

	return true;
}




Object Level::getObject(std::string name) {
	for(int i = 0; i < objects.size(); i++) {
		if(objects[i].name == name) {
			return objects[i];
		}
	}
}




std::vector<Object> Level::getObjects(std::string name) {
	std::vector<Object> vec;
	for(int i = 0; i < objects.size(); i++) {
		if(objects[i].name == name) {
			vec.push_back(objects[i]);
		}
	}
	return vec;
}




sf::Vector2i Level::getTileSize() {
	return sf::Vector2i(tileWidth, tileHeight);
}




void Level::draw(sf::RenderWindow& window) {
	for(int layer = 0; layer < layers.size(); layer++) {
		for(int tile = 0; tile < layers[layer].tiles.size(); tile++) {
			window.draw(layers[layer].tiles[tile]);
		}
	}
}

void Level::drawLayer(sf::RenderWindow& window, int layer) {
	for(int tile = 0; tile < layers[layer].tiles.size(); tile++) {
		window.draw(layers[layer].tiles[tile]);
	}
}
