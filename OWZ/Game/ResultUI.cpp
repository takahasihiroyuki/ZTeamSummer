#include "stdafx.h"
#include "ResultUI.h"
#include "UITransform.h"
#include "SpriteComponent.h"
#include "UIScaleAnimationComponent.h"

void ResultUI::Init()
{
	// 親自身は見た目なし
	ScreenSpaceUIObject::Init();

	// 子UIを作る
	AddChildren<ScreenSpaceUIObject>("resultText");

	m_resultText = static_cast<ScreenSpaceUIObject*>(GetChildren("resultText"));

	if (m_resultText == nullptr) {
		return;
	}

	// 画像初期化
	// 最初仮でclearを入れておく
	m_resultText->Init("Assets/image/ui/result/victory.DDS", 800.0f, 180.0f);

	m_resultText->AddComponent<UIScaleAnimationComponent>();

	// 位置設定
	{
		auto trans = m_resultText->GetComponent<ScreenUITransformComponent>();
		trans->SetLocalPosition({ 960.0f, 380.0f, 0.0f });
		trans->SetScale({ 1.0f, 1.0f, 1.0f });
	}

	m_resultType = ResultType::None;
	m_isShown = false;
	SetChildrenVisible(false);
}

void ResultUI::ShowVictory()
{
	if (m_resultText != nullptr) {
		SetSprite(m_resultText, "Assets/image/ui/result/victory.DDS", 1600.0f, 600.0f);
	}

	m_resultType = ResultType::Victory;
	m_isShown = true;
	SetChildrenVisible(true);
	Activate();
	PlayAnimation();
}

void ResultUI::ShowDefeat()
{
	if (m_resultText != nullptr) {
		SetSprite(m_resultText, "Assets/image/ui/result/defeat.DDS", 1600.0f, 600.0f);
	}

	m_resultType = ResultType::Defeat;
	m_isShown = true;
	SetChildrenVisible(true);
	Activate();
	PlayAnimation();
}

void ResultUI::Hide()
{
	m_resultType = ResultType::None;
	m_isShown = false;
	SetChildrenVisible(false);
	Deactivate();
}

void ResultUI::Render()
{
}

void ResultUI::SetChildrenVisible(bool isVisible)
{
	if (m_resultText) {
		if (isVisible) m_resultText->Activate();
		else m_resultText->Deactivate();
	}
}

void ResultUI::SetSprite(
	ScreenSpaceUIObject* ui,
	const char* filePath,
	float width,
	float height)
{
	if (ui == nullptr) {
		return;
	}

	auto sprite = ui->GetComponent<SpriteComponent>();
	if (sprite == nullptr) {
		return;
	}

	sprite->Init(filePath, width, height);
}

void ResultUI::PlayAnimation()
{
	if (m_resultText == nullptr) {
		return;
	}

	auto anim = m_resultText->GetComponent<UIScaleAnimationComponent>();
	if (anim == nullptr) {
		return;
	}

	anim->Play(
		Vector3(2.0f, 2.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		0.3f,
		false
	);
}
