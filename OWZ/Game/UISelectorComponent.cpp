#include "stdafx.h"
#include "UISelectorComponent.h"
#include "UISelectableComponent.h"
#include "UIObfect.h"

void UISelectorComponent::DecideCurrent()
{
	auto currentItem = GetCurrentItem();
	if (currentItem != nullptr) {
		currentItem->OnDecide();
	}
}

void UISelectorComponent::AdjustValue(float delta)
{
	auto currentItem = GetCurrentItem();
	if (currentItem != nullptr) {
		currentItem->AdjustValue(delta);
	}
}

void UISelectorComponent::AddItem(UISelectableComponent* item)
{
	if (item == nullptr) {
		return;
	}

	m_items.push_back(item);

	if (m_items.size() == 1) {
		m_index = 0;
		m_items[0]->SetSelected(true);
	}
	else {
		item->SetSelected(false);
	}
}

void UISelectorComponent::AddItem(UIObject* item)
{
	if (item == nullptr) {
		return;
	}

	auto selectable = item->GetComponent<UISelectableComponent>();

	if (selectable == nullptr) {
		return;
	}

	AddItem(selectable);

}

void UISelectorComponent::SelectNext()
{
	//　インデックスが不正な値は早期リターン
	if (m_index < 0 || m_index >= static_cast<int>(m_items.size())) {
		return;
	}

	//現在のインデックスが最後のアイテムを指している場合は早期リターン
	if (m_index >= static_cast<int>(m_items.size()) - 1) {
		return;
	}

	m_items[m_index]->SetSelected(false);

	m_index++;

	m_items[m_index]->SetSelected(true);
}

void UISelectorComponent::SelectPrev()
{

	//インデックスが不正な値は早期リターン
	if (m_index < 0 || m_index >= static_cast<int>(m_items.size())) {
		return;
	}

	//現在のインデックスが最初のアイテムを指している場合は早期リターン
	if (m_index <= 0) {
		return;
	}

	m_items[m_index]->SetSelected(false);

	m_index--;

	m_items[m_index]->SetSelected(true);
}

UISelectableComponent* UISelectorComponent::GetCurrentItem() const
{
	if (m_index < 0 || m_index >= static_cast<int>(m_items.size())) {
		return nullptr;
	}
	return m_items[m_index];

}
