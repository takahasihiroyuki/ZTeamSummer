#pragma once

namespace UIAnimationUtil
{
	using EaseFunction = float(*)(float);

	inline float Clamp(float t)
	{
		if (t < 0.0f)
		{
			return 0.0f;
		}
		else if (t > 1.0f) {
			return 1.0f;
		}
		return t;
	}

	inline float Lerp(float a, float b, float t)
	{
		t = Clamp(t);
		return a + (b - a) * t;
	}

	inline Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
	{
		t = Clamp(t);
		return a + (b - a) * t;
	}

	inline Vector4 Lerp(const Vector4& a, const Vector4& b, float t)
	{
		t = Clamp(t);
		return a + (b - a) * t;
	}

	/// <summary>
	///  終点に向かって減速する補間
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>
	inline float EaseOutQuad(float t)
	{
		t = Clamp(t);
		return 1.0f - (1.0f - t) * (1.0f - t);
	}

	/// <summary>
	/// 開始時と終了時をなめらかにする補間
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>
	inline float EaseInOutQuad(float t)
	{
		t = Clamp(t);
		if (t < 0.5f) {
			return 2.0f * t * t;
		}
		return 1.0f - ((-2.0f * t + 2.0f) * (-2.0f * t + 2.0f)) * 0.5f;
	}
}