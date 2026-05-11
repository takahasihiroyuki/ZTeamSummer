#pragma once

/// <summary>
/// 選択可能なUIそれぞれに着けるコンポーネントです。
/// UISelectorComponentによって管理されます。
/// 選択状態の管理や決定時のコールバックを提供します。
/// 選択時や決定時の演出をしたい場合は、オーナーが持っているUIEffectComponentに、選択時や決定時の演出をUIEffectClipとして登録しておかないと演出が再生されません。
/// </summary>
class UIColorAnimationComponent;
class UIScaleAnimationComponent;
class UIEffectComponent;
class UISelectableComponent : public Component
{
	appClass(UISelectableComponent);
public:

	bool Start() override
	{
		m_effect = GetOwner()->GetComponent<UIEffectComponent>();
		return true;
	}

	virtual void SetSelected(bool isSelected)
	{
		if (m_isSelected == isSelected) {
			return;
		}

		m_isSelected = isSelected;
		OnSelectionChanged();
	}

	/// <summary>
	/// 決定時に呼び出されるコールバックを設定します。
	/// </summary>
	/// <param name="onDecide">決定時に呼び出される関数オブジェクト。
	/// 引数・戻り値はなく、ムーブによって内部メンバに移動されます。</param>
	void SetOnDecide(std::function<void()> onDecide)
	{
		m_onDecide = std::move(onDecide);
	}

	void SetOnValueAdjusted(std::function<void(float)> onValueAdjusted)
	{
		m_onValueAdjusted = std::move(onValueAdjusted);
	}

	virtual void OnDecide();

	virtual void AdjustValue(float delta);

	bool IsSelected() const
	{
		return m_isSelected;
	}

protected:

	virtual void OnSelectionChanged();

private:
	bool m_isSelected = false;						// 選択されているか
	std::function<void()> m_onDecide;				// 決定時の処理
	std::function<void(float)> m_onValueAdjusted;	// 値変更時の処理(スライダーなどで使用)
	UIEffectComponent* m_effect = nullptr;

};

