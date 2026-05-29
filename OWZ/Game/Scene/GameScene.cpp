#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "UISystem.h"
#include "NumberDisplayUIObject.h"
#include "UITransform.h"
#include "UIObfect.h"
#include"ResultUI.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{

	//UI登録
	{
		auto crosshair = std::make_unique<ScreenSpaceUIObject>();
		crosshair->Init("Assets/image/ui/crosshair/crosshair.dds", 64.0f, 64.0f);

		auto transform = crosshair->GetComponent<ScreenUITransformComponent>();
		if (transform != nullptr) {
			transform->SetLocalPosition({ 960.0f, 540.0f, 0.0f });
		}

		UISystem::Get().GetCanvas(CanvasType::HUD).AddUI(std::move(crosshair));
	}

	// ナンバーUIの表示テスト
	{
		auto numberUI = std::make_unique<ScreenNumberDisplayUIObject>();

		// 5桁、1文字32x48、文字間隔4
		numberUI->Init(
			5,
			32.0f,
			48.0f,
			4.0f
		);

		auto transform = numberUI->GetComponent<ScreenUITransformComponent>();
		if (transform != nullptr) {
			transform->SetLocalPosition({ 960.0f, 540.0f, 0.0f });
		}

		numberUI->SetValue(12345);

		UISystem::Get().GetCanvas(CanvasType::HUD).AddUI(std::move(numberUI));
	}

	//リザルトUI
	{
		auto result = std::make_unique<ResultUI>();
		result->Init();

		auto transform = result->GetComponent<ScreenUITransformComponent>();
		if (transform != nullptr) {
			transform->SetLocalPosition({ 960.0f, 540.0f, 0.0f });
		}
		result->ShowVictory();
		UISystem::Get().GetCanvas(CanvasType::HUD).AddUI(std::move(result));
	}
}

void GameScene::Update(SceneManager& manager)
{

}

void GameScene::Draw()
{
}

void GameScene::Finalize()
{
}
