#pragma once
#include "UITransform.h"

class WorldUIFollowComponent : public Component
{
	appClass(WorldUIFollowComponent);
private:
	GameObject* m_target = nullptr;
	WorldUITransformComponent* m_transform = nullptr;
	Vector3 m_offset = Vector3::Zero;

public:
	WorldUIFollowComponent()
	{
	};

	void Init(GameObject* target, const Vector3& offset)
	{
		m_target = target;
		m_offset = offset;
	}

	void SetTarget(GameObject* target)
	{
		m_target = target;
	}

	void SetOffset(const Vector3& offset)
	{
		m_offset = offset;
	}

	bool Start() override
	{
		m_transform = GetOwner()->GetComponent<WorldUITransformComponent>();

		if (!m_target || !m_transform) {
			return false;
		}
		return true;
	}

	void Update() override
	{
		if (!m_target || !m_transform) {
			return;
		}


		auto targetTransform = m_target->GetComponent<TransformComponent>();
		if (!targetTransform) {
			return;
		}
		const Vector3 pos = targetTransform->GetPosition() + m_offset;

		m_transform->SetLocalPosition(pos);
	}
};