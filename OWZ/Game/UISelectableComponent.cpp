#include "stdafx.h"
#include "UISelectableComponent.h"
#include "UIEffectComponent.h"
#include "UIEffectID.h"

bool UISelectableComponent::Start()
{
	m_effect = GetOwner()->GetComponent<UIEffectComponent>();
	return true;
}

void UISelectableComponent::OnDecide()
{
	//UIの演出
	if (m_effect != nullptr) {
		m_effect->Play(UIEffectIDs::Decide);
	}

	//外から設定された処理
	if (m_onDecide) {
		m_onDecide();
	}
}

void UISelectableComponent::AdjustValue(float delta)
{
	//UI側の演出
	if (m_effect != nullptr) {
		m_effect->Play(UIEffectIDs::ValueAdjusted);
	}

	//外から設定された処理
	if (m_onValueAdjusted) {
		m_onValueAdjusted(delta);
	}
}

void UISelectableComponent::OnSelectionChanged()
{
	if (m_effect == nullptr) {
		return;
	}

	//UIの演出
	if (m_isSelected) {
		m_effect->Play(UIEffectIDs::SelectEnter);
	}
	else {
		m_effect->Play(UIEffectIDs::SelectExit);
	}

}