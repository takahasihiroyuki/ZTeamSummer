#pragma once

/// <summary>
/// 選択可能なUIを管理するコンポーネント。
/// </summary>
class UISelectableComponent;
class UIObject;
class UISelectorComponent : public Component
{
	appClass(UISelectorComponent);
private:
	std::vector<UISelectableComponent*> m_items;
	int m_index = -1;

public:

	/// <summary>
	/// 現在選択されているアイテムを決定する
	/// </summary>
	void DecideCurrent();

	/// <summary>
	/// 現在選択されているアイテムの値を増減する
	/// </summary>
	/// <param name="newValue"></param>
	void AdjustValue(float delta);

	void AddItem(UISelectableComponent* item);

	void AddItem(UIObject* item);

	void SelectNext();

	void SelectPrev();

	UISelectableComponent* GetCurrentItem() const;
};