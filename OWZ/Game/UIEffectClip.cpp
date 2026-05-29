#include "stdafx.h"
#include "UIEffectClip.h"
#include "UIAnimationComponentBase.h"

void UIEffectClip::Play()
{
	for (auto animation : m_animations) {
		if (animation != nullptr) {
			animation->Play();
		}
	}


	for (auto soundKind : m_sounds) {
		SoundManager::Get().PlayBGM(soundKind);
	}
}

bool UIEffectClip::IsEmpty() const
{
	return m_animations.empty() && m_sounds.empty();
}
