#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "UISystem.h"
#include "UIObfect.cpp"

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
