#pragma once
#include "Scene/SceneBase.h"

class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};
