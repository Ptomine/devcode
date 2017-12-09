#include "../include/Animation.hpp"

Animation::Animation(sf::Sprite& _sprite, const std::string& filename, const sf::Vector2u& _imageAmmount, float animTime, AnimationType type)
	: sprite(_sprite)
	, imageList()
	, currentImagePosition(0, 0)
	, imageAmmount(_imageAmmount)
	, switchTime(animTime / _imageAmmount.x)
	, totalTime(0.0f)
	, backwards(false)
	, ended(false)
{
	imageList.loadFromFile(filename);
	currentImage.width  = imageList.getSize().x / imageAmmount.x;
	currentImage.height = imageList.getSize().y / imageAmmount.y;
	switch(type)
	{
	case TYPE_REPEATING:
		currentUpdateFunc = &Animation::updateRepeating;
		break;
	case TYPE_CYCLING:
		currentUpdateFunc = &Animation::updateCycling;
		break;
	case TYPE_SINGLE:
		currentUpdateFunc = &Animation::updateSingle;
		break;
	}
}




Animation::~Animation()
{
}




void Animation::initialize()
{
	sprite.setTexture(imageList);
	sprite.setTextureRect(currentImage);
}




void Animation::restart()
{
	currentImagePosition.x = 0;
	ended = false;
}



void Animation::changeType(AnimationType type)
{
	switch(type)
	{
		case TYPE_REPEATING:
		currentUpdateFunc = &Animation::updateRepeating;
		break;
		case TYPE_CYCLING:
		currentUpdateFunc = &Animation::updateCycling;
		break;
		case TYPE_SINGLE:
		currentUpdateFunc = &Animation::updateSingle;
		break;
	}
	restart();
}




void Animation::update(unsigned row, float deltaTime)
{
	(this->*currentUpdateFunc)(row, deltaTime);
}




const sf::Texture& Animation::getTexture()
{
	return imageList;
}




const sf::Vector2u& Animation::getImageAmmount()
{
	return imageAmmount;
}




float Animation::getSwitchTime()
{
	return switchTime;
}




float Animation::getAnimationTime()
{
	return switchTime * imageAmmount.x;
}




bool Animation::isEnded()
{
	return ended;
}




void Animation::updateRepeating(unsigned row, float deltaTime)
{
	currentImagePosition.y = row;
	totalTime += deltaTime;

	if(totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImagePosition.x++;

		if(currentImagePosition.x >= imageAmmount.x)
		{
			currentImagePosition.x = 0;
		}
	}

	currentImage.left = currentImagePosition.x * currentImage.width;
	currentImage.top  = currentImagePosition.y * currentImage.height;
	sprite.setTextureRect(currentImage);
}




void Animation::updateCycling(unsigned row, float deltaTime)
{
	currentImagePosition.y = row;
	totalTime += deltaTime;

	if(totalTime >= switchTime)
	{
		totalTime -= switchTime;
		backwards ? currentImagePosition.x-- : currentImagePosition.x++;

		if(currentImagePosition.x == 0)
		{
			backwards = false;
		}
		if(currentImagePosition.x >= imageAmmount.x)
		{
			backwards = true;
			currentImagePosition.x--;
		}
	}
	currentImage.left = currentImagePosition.x * currentImage.width;
	currentImage.top  = currentImagePosition.y * currentImage.height;
	sprite.setTextureRect(currentImage);
}




void Animation::updateSingle(unsigned row, float deltaTime)
{
	if(ended)
	{
		return;
	}

	currentImagePosition.y = row;
	totalTime += deltaTime;

	if(totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImagePosition.x++;

		if(currentImagePosition.x >= imageAmmount.x)
		{
			ended = true;
			currentImagePosition.x--;
		}
	}
	currentImage.left = currentImagePosition.x * currentImage.width;
	currentImage.top  = currentImagePosition.y * currentImage.height;
	sprite.setTextureRect(currentImage);
}
