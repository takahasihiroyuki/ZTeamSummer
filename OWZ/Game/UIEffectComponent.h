#pragma once
#include "UIEffectID.h"
#include"UIEffectClip.h"

/// <summary>
/// UIの演出を管理するコンポーネントです
/// UIの演出は、UIEffectClipクラスのインスタンスとして登録されます。
/// UIEffectClipは、UIのアニメーションやサウンドの再生などを関数オブジェクトとして登録するクラスです。
/// </summary>
class UIEffectComponent : public nsK2EngineLow::Component
{
	appClass(UIEffectComponent);

public:
	/// <summary>
	/// UIの演出のクリップを登録します
	/// </summary>
	/// <param name="id">uint32_t型です Hash32("SelectEnter")のように入れてください</param>
	/// <param name="clip"></param>
	void SetEffectClip(UIEffectID id, const UIEffectClip& clip)
	{
		m_clips[id] = clip;
	}

	void Play(UIEffectID id)
	{
		auto it = m_clips.find(id);

		if (it == m_clips.end()) {
			return;
		}

		it->second.Play();
	}

private:
	std::unordered_map<UIEffectID, UIEffectClip> m_clips;
};

