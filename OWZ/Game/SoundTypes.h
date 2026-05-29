#pragma once
#include <string>
#include <array>
#include <cstddef>

using SoundIndex = int;

constexpr SoundIndex InvalidSoundIndex = -1;


/** サウンドの情報の構造体 */
struct SoundInformation
{
	const char* name;		//サウンドの名前
	const std::string assetPath;

	SoundInformation(const std::string& path, const char* soundName) : assetPath(path), name(soundName) {}
};

inline SoundIndex GetSoundIndex(const std::string& name)
{
	for (std::size_t i = 0; i < soundInformation.size(); ++i) {
		if (soundInformation[i].name == name) {
			return static_cast<SoundIndex>(i);
		}
	}

	return InvalidSoundIndex;
}

static std::vector<SoundInformation> soundInformation =
{
	SoundInformation("Assets/sound/bgm_title.wav", "BgmTitle"),     // BgmTitle
	SoundInformation("Assets/sound/se_gun_shot.wav", "SeShot"),   // SeShot
	SoundInformation("Assets/sound/se_explosion.wav", "SeExplosion"),  // SeExplosion
};