#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

class Animation
{
public:
	enum AnimationType
	{
		TYPE_REPEATING,
		TYPE_CYCLING,
		TYPE_SINGLE,
	};
	Animation(sf::Sprite&, const std::string&, const sf::Vector2u&, float, AnimationType = TYPE_REPEATING);
	~Animation();

	void initialize();
	void restart();
	void changeType(AnimationType);

	void update(unsigned, float);

	const sf::Texture& getTexture();
	const sf::Vector2u& getImageAmmount();
	float getSwitchTime();
	float getAnimationTime();
	bool isEnded();
private:
	void (Animation::*currentUpdateFunc)(unsigned, float);
	void updateRepeating(unsigned, float);
	void updateCycling(unsigned, float);
	void updateSingle(unsigned, float);

	sf::Sprite& sprite;
	sf::Texture imageList;
	sf::IntRect currentImage;
	sf::Vector2u currentImagePosition;
	sf::Vector2u imageAmmount;
	float switchTime;
	float totalTime;

	bool backwards;
	bool ended;
};

#endif //ANIMATION_HPP
