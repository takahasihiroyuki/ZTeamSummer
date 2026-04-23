#include "stdafx.h"
#include "UISelectorComponent.h"

class UISelectorComponent : public nsK2EngineLow::Component
{
	appClass(UISelectableComponent)

public:
	UISelectorComponent()
	{
	}
	virtual ~UISelectorComponent() noexcept = default;
	void Update() override
	{
		// ここで入力を見て、UIの選択を切り替える処理を書く。
		// 例えば、十字キーの左右で選択を切り替えるとか。
	}

	void SetSelected(bool isSelected)
	{
		if (!m_isSelectable) {
			return; // 選択不可なら選択状態を変更しない
		}
		m_isSelected = isSelected;

	}

	void SetSelectable(bool isSelectable)
	{
		m_isSelectable = isSelectable;
		if (!m_isSelectable) {
			m_isSelected = false; // 選択不可にしたら選択状態も解除する
		}
	
	}
	bool IsSelectable() const
	{
		return m_isSelectable;
	}

	bool IsSelected() const
	{
		return m_isSelected;
	}
private:
	bool m_isSelected = false;		// このUIが現在選択されているかどうか
	bool m_isSelectable = true;		// このUIが選択可能かどうか
};
