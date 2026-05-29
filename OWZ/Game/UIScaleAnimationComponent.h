#pragma once
#include "UITransform.h"
#include "UIAnimationUtil.h"
#include "UIAnimationComponentBase.h"

class UIScaleAnimationComponent : public UIAnimationComponentBase
{
	appClass(UIScaleAnimationComponent);
private:

	UITransformBase* m_transform = nullptr;

	Vector3 m_startScale = Vector3::One;
	Vector3 m_endScale = Vector3::One;

public:

	void Init(const Vector3& startScale, const Vector3& endScale, float duration, bool isLoop = false)
	{
		m_startScale = startScale;
		m_endScale = endScale;
		m_duration = duration;
		m_isLoop = isLoop;
	}

	bool Start() override
	{
		m_transform = GetOwner()->GetComponent<UITransformBase>();
		return true;
	}

	void Update() override
	{
		if (!m_isPlaying || m_transform == nullptr) {
			return;
		}

		m_elapsed += g_gameTime->GetFrameDeltaTime();

		float t = GetAnimationT();
		float easedT = UIAnimationUtil::EaseOutQuad(t);

		Vector3 scale = UIAnimationUtil::Lerp(m_startScale, m_endScale, easedT);
		m_transform->SetScale(scale);

		if (t >= 1.0f) {
			if (m_isLoop) {
				m_elapsed = 0.0f;
			}
			else {
				m_isPlaying = false;
				m_transform->SetScale(m_endScale);
			}
		}
	}

public:
	void Play(const Vector3& startScale, const Vector3& endScale, float duration, bool isLoop = false)
	{
		m_startScale = startScale;
		m_endScale = endScale;
		PlayBase(duration, isLoop);

		if (m_transform != nullptr) {
			m_transform->SetScale(m_startScale);
		}
	}

	void Play(bool isLoop)
	{
		PlayBase(m_duration, isLoop);
		if (m_transform != nullptr) {
			m_transform->SetScale(m_startScale);
		}
	}

	void Play()
	{
		PlayBase(m_duration, m_isLoop);
		if (m_transform != nullptr) {
			m_transform->SetScale(m_startScale);
		}
	}


	void SetStartScale(const Vector3& startScale)
	{
		m_startScale = startScale;
	}

	void SetEndScale(const Vector3& endScale)
	{
		m_endScale = endScale;
	}

	Vector3 GetStartScale() const
	{
		return m_startScale;
	}

	Vector3 GetEndScale() const
	{
		return m_endScale;
	}

	/// <summary>
	/// スケールと経過時間をリセットして、アニメーションを最初からやり直せるようにする。
	/// この関数だけだとストップはしません。
	/// </summary>
	void Reset() override
	{
		m_elapsed = 0.0f;
		if (m_transform != nullptr) {
			m_transform->SetScale(m_startScale);
		}
	}

};