#pragma once
#include"UIObfect.h"

class SkillSlotUIObfect : public ScreenSpaceUIObject
{
private:
	ScreenSpaceUIObject* m_frame;
	ScreenSpaceUIObject* m_icon;
	ScreenSpaceUIObject* m_cooldownGauge;

	ScreenUITransformComponent* m_cooldownGaugeTransform = nullptr;

	float m_width = 64.0f;
	float m_height = 64.0f;

	float m_remainCooldown = 0.0f;	//�N�[���_�E���̎c�莞��
	float m_maxCooldown = 1.0f;		//�N�[���_�E���̍ő厞��

public:
	void Init(
		float width,
		float height);

	void SetCooldown(float remain, float max)
	{
		m_remainCooldown = remain;
		if (max <= 0.0f)
		{
			m_maxCooldown = 1.0f;
		}
		else
		{
			m_maxCooldown = max;
		}
		UpdateCooldownVisual();
	}

	void UpdateCooldownVisual()
	{
		float rate = 1.0f - (m_remainCooldown / m_maxCooldown);

		if (rate < 0.0f) rate = 0.0f;
		if (rate > 1.0f) rate = 1.0f;

		float fillHeight = m_height * rate;

		if (m_cooldownGaugeTransform) {
			m_cooldownGaugeTransform->SetScale({ m_width, fillHeight, 1.0f });

			// �������ɐL�΂����߈ʒu�␳
			float y = -(m_height * 0.5f) + (fillHeight * 0.5f);
			m_cooldownGaugeTransform->SetLocalPosition({ 0.0f, y, 0.0f });
		}
	}
};
