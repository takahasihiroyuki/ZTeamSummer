#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "UISystem.h"
#include "UIObfect.cpp"

GameScene::GameScene()
{
	m_test = std::make_shared<Soldier>();
	m_test->Init();

	m_tower = std::make_shared<DestructibleObject>();
	m_tower->Initialize();


}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	m_test = new Soldier;
	m_tower = new DestructibleObject();
	m_tower->InitParam(
		"Assets/modelData/gimmick/breakObj/model/ObjTower.tkm",      // 破壊前
		"Assets/modelData/gimmick/breakObj/model/breakObjTower.tkm", // 破壊後
		Vector3(0.0f, 0.0f, 0.0f)                                    // 座標
	);

	m_tower2 = new DestructibleObject();
	m_tower2->InitParam(
		"Assets/modelData/gimmick/breakObj/model/ObjTower.tkm",
		"Assets/modelData/gimmick/breakObj/model/breakObjTower.tkm",
		Vector3(150.0f, 0.0f, 0.0f)
	);

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

	m_resultUI = std::make_shared<ResultUI>();
	m_resultUI->Init();
	m_resultUI->ShowVictory();
	UISystem::Get().GetCanvas(CanvasType::HUD).AddUI(m_resultUI);

	// 破壊ミッションの生成と登録
	//DestructionMission* mission = new DestructionMission();
	//mission->AddTarget(m_tower);  // 1つ目を登録
	//mission->AddTarget(m_tower2); // 2つ目を登録

	// 管理を任せる
	//m_currentMission = mission;
}

void GameScene::Update(SceneManager& manager)
{

}

void GameScene::Draw()
{
}

void GameScene::Finalize()
{
	delete m_test;
	m_test = nullptr;

	delete m_tower;
	m_tower = nullptr;

	delete m_tower2;
	m_tower2 = nullptr;

	delete m_currentMission;
	m_currentMission = nullptr;
}
