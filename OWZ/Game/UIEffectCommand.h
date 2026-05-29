#pragma once
#include"UIObfect.h"
class UIEffectCommand
{
public:
	virtual ~UIEffectCommand() = default;

	virtual void Play(UIObject* owner) = 0;
};

