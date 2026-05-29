#pragma once
#include "UIObfect.h"

class ScreenSpaceUIObject;
class SpriteComponent;

class NumberSlotUIBaseObject : public UIObject
{
protected:
	std::array<UIObject*, 10> m_numberSprites;
	int m_currentNumber = 0;
	bool m_isVisible = true;

protected:
	void RefreshVisible();

public:
	virtual ~NumberSlotUIBaseObject() noexcept = default;

	virtual void Init(float width, float height) = 0;

	void SetNumber(int number)
	{
		if (number < 0) {
			number = 0;
		}
		if (number > 9) {
			number = 9;
		}

		m_currentNumber = number;
		RefreshVisible();
	}

	void SetVisible(bool isVisible)
	{
		m_isVisible = isVisible;
		RefreshVisible();
	}

	int GetCurrentNumber() const
	{
		return m_currentNumber;
	}
};

/// <summary>
/// スクリーンスペースUIの数字スロットUIオブジェクト
/// </summary>
class ScreenNumberSlotUIObject : public NumberSlotUIBaseObject
{
public:
	void Init(float width, float height) override;
};

/// <summary>
/// worldスペースのUIの数字スロットUIオブジェクト
/// </summary>
class WorldNumberSlotUIObject : public NumberSlotUIBaseObject
{
public:
	void Init(float width, float height) override;
};