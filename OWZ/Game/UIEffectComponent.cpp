#include "stdafx.h"
#include "UIEffectComponent.h"
#include "UIEffectClip.h"

void UIEffectComponent::SetEffectClip(UIEffectID id, const UIEffectClip& clip)
{
	m_clips[id] = clip;
}
