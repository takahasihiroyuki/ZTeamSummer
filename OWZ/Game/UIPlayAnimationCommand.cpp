#include "stdafx.h"
#include "UIPlayAnimationCommand.h"
#include"UIAnimationComponentBase.h"

void UIPlayAnimationCommand::Play(UIObject* owner)
{
	if (owner == nullptr) {
		return;
	}

	auto anim = owner->GetComponent<UIAnimationComponentBase>();
	if (anim == nullptr) {
		return;
	}

	anim->Play(m_animationName);
}
