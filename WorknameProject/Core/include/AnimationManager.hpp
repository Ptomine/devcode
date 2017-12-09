#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include <unordered_map>
#include "Animation.hpp"

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	void update(unsigned, float);

	void addAnimation(int, Animation*);
	void setAnimation(int);
	int whatAnimation();
	float getThisAnimationTime();
	float getAnimationTime(int);
	bool isAnimationEnded();
private:
	std::unordered_map<int, Animation*> animations;
	std::unordered_map<int, Animation*>::iterator currentAnimation;
};

#endif //ANIMATION_MANAGER_HPP
