#pragma once
#include"SoundTypes.h"
#include"SoundManager.h"

using SoundID = uint32_t;

struct UIScaleEffectData
{
	Vector3 from;
	Vector3 to;
	float duration;
	SoundID easing;
};

struct UIMoveEffectData
{
	Vector3 from;
	Vector3 to;
	float duration;
	SoundID easing;
};

struct UISoundEffectData
{
	const char* soundPath;
	float delay;
};

/// <summary>
/// 一つのUIの演出のまとまりのクラスです
/// 例：UIの選択時の演出、決定時の演出など
/// 一つの演出にこのクラスのインスタンスをひとつ作ります。
/// </summary>
class UIAnimationComponentBase;
class UIEffectClip
{
	appClass(UIEffectClip);
public:

	void AddSound(SoundID soundKind)
	{
		m_sounds.push_back(soundKind);
	}


	void AddAnimation(UIAnimationComponentBase* animation)
	{
		if (animation == nullptr) {
			return;
		}

		m_animations.push_back(animation);
	}


	void Play();

	bool IsEmpty() const;

private:
	std::vector<UIAnimationComponentBase*> m_animations;
	std::vector<SoundID> m_sounds;
};
