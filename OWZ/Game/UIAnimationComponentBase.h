#pragma once
#include"UIAnimationUtil.h"
class UIAnimationComponentBase : public Component
{
protected:
	float m_duration = 1.0f;
	float m_elapsed = 0.0f;

	bool m_isPlaying = false;
	bool m_isLoop = false;

	UIAnimationUtil::EaseFunction m_easeFunction = UIAnimationUtil::EaseOutQuad;	//アニメーションのイージング関数

public:


	/// <summary>
	/// イージング関数を設定します
	/// 渡された関数が nullptr の場合は何も変更しません
	/// </summary>
	/// <param name="easeFunction"></param>
	void SetEaseFunction(UIAnimationUtil::EaseFunction easeFunction)
	{
		if (easeFunction == nullptr) {
			return;
		}

		m_easeFunction = easeFunction;
	}

	float GetEasedT() const
	{
		float t = GetAnimationT();
		if (m_easeFunction == nullptr) {
			return t;
		}

		return m_easeFunction(t);
	}

	/// <summary>
	/// アニメーションを開始
	/// 初めから再生される
	/// 途中から再生したい場合はContinue()を呼び出してください
	/// </summary>
	virtual void Play() = 0;

	/// <summary>
	/// 途中からアニメーションを再開
	/// </summary>
	void Continue() {
		m_isPlaying = true;

	}

	/// <summary>
	/// アニメーションを一時停止
	/// アニメーションの状態は保持され、Continue()で再開でる
	/// </summary>
	void Pause()
	{
		m_isPlaying = false;
	}

	/// <summary>
	/// 処理を一時停止してからリセットを実行
	/// </summary>
	void StopAndReset()
	{
		Pause();
		Reset();
	}

	bool IsPlaying() const
	{
		return m_isPlaying;
	}

	void SetLoop(bool isLoop)
	{
		m_isLoop = isLoop;
	}

	void SetDuration(float duration)
	{
		m_duration = duration;
	}

	virtual void Reset() = 0;

protected:
	void PlayBase(float duration, bool isLoop)
	{
		m_duration = duration;
		m_elapsed = 0.0f;
		m_isLoop = isLoop;
		m_isPlaying = true;
	}

	float GetAnimationT() const
	{
		if (m_duration <= 0.0f) {
			return 1.0f;
		}

		float t = m_elapsed / m_duration;

		if (t > 1.0f) {
			t = 1.0f;
		}

		return t;
	}
};

