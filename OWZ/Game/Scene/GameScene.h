#pragma once
#include "Scene/SceneBase.h"

class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:
	//�f�o�b�O�p
	std::unique_ptr<Soldier> m_soldier;

	std::shared_ptr<ResultUI> m_resultUI;

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};
