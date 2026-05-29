#pragma once
#include "SpriteComponent.h"
#include "UIAnimationUtil.h"
#include "UIAnimationComponentBase.h"

class UIColorAnimationComponent : public UIAnimationComponentBase
{
	appClass(UIColorAnimationComponent);
private:
	SpriteComponent* m_sprite = nullptr;

	Vector4 m_startColor = Vector4(1, 1, 1, 1);
	Vector4 m_endColor = Vector4(1, 1, 1, 1);


public:

	void Init(const Vector4& startColor, const Vector4& endColor, float duration, bool isLoop = false)
	{
		m_startColor = startColor;
		m_endColor = endColor;
		m_duration = duration;
		m_isLoop = isLoop;
	}

	bool Start() override
	{
		m_sprite = GetOwner()->GetComponent<SpriteComponent>();
		return true;
	}

	void Update() override
	{
		if (!m_isPlaying || m_sprite == nullptr) {
			return;
		}

		m_elapsed += g_gameTime->GetFrameDeltaTime();

		float easedT = GetEasedT();

		Vector4 color = UIAnimationUtil::Lerp(m_startColor, m_endColor, easedT);
		m_sprite->SetMulColor(color);

		if (easedT >= 1.0f) {
			if (m_isLoop) {
				m_elapsed = 0.0f;
			}
			else {
				m_isPlaying = false;
				m_sprite->SetMulColor(m_endColor);
			}
		}
	}

public:
	void Play(const Vector4& startColor, const Vector4& endColor, float duration, bool isLoop = false)
	{
		m_startColor = startColor;
		m_endColor = endColor;
		PlayBase(duration, isLoop);

		if (m_sprite != nullptr) {
			m_sprite->SetMulColor(m_startColor);
		}
	}

	void Play(bool isLoop)
	{
		PlayBase(m_duration, isLoop);
		if (m_sprite != nullptr) {
			m_sprite->SetMulColor(m_startColor);
		}
	}

	void Play() override
	{
		PlayBase(m_duration, m_isLoop);
		if (m_sprite != nullptr) {
			m_sprite->SetMulColor(m_startColor);
		}
	}


	/// <summary>
	/// 色と経過時間をリセットして、アニメーションを最初からやり直せるようにする。
	/// この関数だけだとストップはしません。
	/// </summary>
	void Reset() override
	{
		m_elapsed = 0.0f;
		if (m_sprite != nullptr) {
			m_sprite->SetMulColor(m_startColor);
		}
	}

	void SetStartColor(const Vector4& startColor)
	{
		m_startColor = startColor;
	}

	void SetEndColor(const Vector4& endColor)
	{
		m_endColor = endColor;
	}

	Vector4 GetStartColor() const
	{
		return m_startColor;
	}

	Vector4 GetEndColor() const
	{
		return m_endColor;
	}

};