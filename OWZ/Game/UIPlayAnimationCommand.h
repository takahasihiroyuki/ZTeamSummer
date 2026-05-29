#pragma once
#include"UIEffectCommand.h"

class UIPlayAnimationCommand : public UIEffectCommand
{
	UIPlayAnimationCommand(const std::string& animationName)
		: m_animationName(animationName)
	{
	}

	void Play(UIObject* owner) override;


private:
	std::string m_animationName;
};

