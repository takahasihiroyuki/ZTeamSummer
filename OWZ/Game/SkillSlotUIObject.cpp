#include "stdafx.h"
#include "SkillSlotUIObject.h"

void SkillSlotUIObfect::Init(float width, float height)
{
	ScreenSpaceUIObject::Init();

	m_width = width;
	m_height = height;

	AddChildren<ScreenSpaceUIObject>("icon");
	AddChildren<ScreenSpaceUIObject>("fill");
	AddChildren<ScreenSpaceUIObject>("frame");

	m_icon = static_cast<ScreenSpaceUIObject*>(GetChildren("icon"));
	m_cooldownGauge = static_cast<ScreenSpaceUIObject*>(GetChildren("fill"));
	m_frame = static_cast<ScreenSpaceUIObject*>(GetChildren("frame"));

	m_icon->Init("Assets/image/ui/skill/icon/.DDS", width, height);
	m_cooldownGauge->Init("Assets/image/ui/skill/cooldownGauge.DDS", width, height);
	m_frame->Init("Assets/image/ui/skill/skill_frame.DDS", width, height);

	m_cooldownGaugeTransform = m_cooldownGauge->GetComponent<ScreenUITransformComponent>();

	UpdateCooldownVisual();
}
