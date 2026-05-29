#include "stdafx.h"
#include "UITransform.h"

void ScreenUITransformComponent::UpdateTransform()
{
	m_renderPosition = m_localPosition;

	auto owner = GetOwner();
	if (owner != nullptr) {
		auto parent = owner->GetParent();

		if (parent != nullptr) {//オーナーが親オブジェクトなら

			auto parentTransform = parent->GetComponent<UITransformBase>();

			if (parentTransform != nullptr) {
				m_renderPosition =
					parentTransform->GetRenderPosition() + m_localPosition;
			}
		}
	}

	m_isDirty = false;
}

void WorldUITransformComponent::UpdateTransform()
{

	Vector3 worldPosition = m_localPosition;

	auto owner = GetOwner();
	if (owner != nullptr) {
		auto parent = owner->GetParent();

		if (parent != nullptr) {
			auto parentTransform = parent->GetComponent<UITransformBase>();

			if (parentTransform != nullptr) {
				worldPosition =
					parentTransform->GetLocalPosition() + m_localPosition;
			}
		}
	}

	Matrix view = g_camera3D->GetViewMatrix();
	Matrix proj = g_camera3D->GetProjectionMatrix();

	// ワールド座標をクリップ座標に変換
	Vector4 clipPos(worldPosition.x, worldPosition.y, worldPosition.z, 1.0f);
	view.Apply(clipPos);
	proj.Apply(clipPos);

	// カメラの後ろにある
	if (clipPos.w <= 0.0f)
	{
		m_isVisible = false;
		return;
	}

	// NDC座標に変換
	float invW = 1.0f / clipPos.w;
	float ndcX = clipPos.x * invW;
	float ndcY = clipPos.y * invW;
	float ndcZ = clipPos.z * invW;

	// 画面外なら非表示
	if (ndcX < -1.0f || ndcX > 1.0f ||
		ndcY < -1.0f || ndcY > 1.0f ||
		ndcZ < 0.0f || ndcZ > 1.0f)
	{
		m_isVisible = false;
		return;
	}

	m_isVisible = true;

	// NDC(-1～1) -> スクリーン座標
	m_renderPosition.x = ((ndcX + 1.0f) * 0.5f) * FRAME_BUFFER_W;
	m_renderPosition.y = ((1.0f - ndcY) * 0.5f) * FRAME_BUFFER_H;
	m_renderPosition.z = 0.0f;

	m_isDirty = false;
}
