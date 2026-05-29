#pragma once
#include "UITransform.h"
#include "UIAnimationUtil.h"
#include "UIAnimationComponentBase.h"

class UIMoveAnimationComponent : public UIAnimationComponentBase
{
	appClass(UIMoveAnimationComponent);
private:
	UITransformBase* m_transform = nullptr;

	Vector3 m_startPosition = Vector3::Zero;
	Vector3 m_endPosition = Vector3::Zero;

public:

	void Init(const Vector3& startPos, const Vector3& endPos, float duration, bool isLoop = false)
	{
		m_startPosition = startPos;
		m_endPosition = endPos;
		m_duration = duration;
		m_isLoop = isLoop;
		m_isPlaying = false;
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

		Vector3 pos = UIAnimationUtil::Lerp(m_startPosition, m_endPosition, easedT);
		m_transform->SetLocalPosition(pos);

		if (t >= 1.0f) {
			if (m_isLoop) {
				m_elapsed = 0.0f;
			}
			else {
				m_isPlaying = false;
				m_transform->SetLocalPosition(m_endPosition);
			}
		}
	}

public:
	void Play(const Vector3& startPos, const Vector3& endPos, float duration, bool isLoop = false)
	{
		m_startPosition = startPos;
		m_endPosition = endPos;
		PlayBase(duration, isLoop);

		if (m_transform != nullptr) {
			m_transform->SetLocalPosition(m_startPosition);
		}
	}

	void Play(bool isLoop)
	{
		PlayBase(m_duration, isLoop);
		if (m_transform != nullptr) {
			m_transform->SetLocalPosition(m_startPosition);
		}
	}

	void Play()
	{
		PlayBase(m_duration, m_isLoop);
		if (m_transform != nullptr) {
			m_transform->SetLocalPosition(m_startPosition);
		}
	}

	/// <summary>
	/// 位置と経過時間をリセットして、アニメーションを最初からやり直せるようにする。
	/// この関数だけだとストップはしません。
	/// </summary>
	void Reset() override
	{
		m_elapsed = 0.0f;
		if (m_transform != nullptr) {
			m_transform->SetLocalPosition(m_startPosition);
		}
	}

	void SetStartPosition(const Vector3& startPos)
	{
		m_startPosition = startPos;
	}

	void SetEndPosition(const Vector3& endPos)
	{
		m_endPosition = endPos;
	}

	Vector3 GetStartPosition() const
	{
		return m_startPosition;
	}

	Vector3 GetEndPosition() const
	{
		return m_endPosition;
	}
};