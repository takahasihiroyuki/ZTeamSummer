#include "stdafx.h"
#include "DestructibleObject.h"

DestructibleObject::DestructibleObject()
{

}

DestructibleObject::~DestructibleObject()
{
}

// 外からパスと座標を受け取ってセットアップする関数
void DestructibleObject::InitParam(const char* intactModelPath, const char* brokenModelPath, const Vector3& position)
{
    // 破壊後のパスを変数に保存しておく
    m_brokenModelPath = brokenModelPath;

    if (m_model) {
        // 破壊前のモデルをセット
        m_model->SetModel(intactModelPath, false);
        m_model->SetDrawFlag(true);
        m_model->SetPosition(position);
    }
    if (m_transform) {
        m_transform->SetPosition(position);
    }
}

void DestructibleObject::PlayDestroyEffect()
{
    // 保存しておいたパスを使ってモデルを切り替える
    if (m_model && !m_brokenModelPath.empty()) {
        m_model->SetModel(m_brokenModelPath.c_str(), false);
    }
}

void DestructibleObject::Update()
{
    // すでに破壊されていたら何もしない
    if (m_isDestroyed) {
        return;
    }

    // デバッグ用：Xボタンで破壊テスト
    if (g_pad[0]->IsTrigger(enButtonX)) {
        TakeDamage();
    }
}

void DestructibleObject::Render()
{
    if (m_model) {
        m_model->Draw();
    }
}

void DestructibleObject::Initialize()
{
    m_isDestroyed = false;

    AddComponent<TransformComponent>();
    AddComponent<ModelComponent>();

    m_transform = GetComponent<TransformComponent>();
    m_model = GetComponent<ModelComponent>();
}

void DestructibleObject::TakeDamage()
{
    if (m_isDestroyed) return;

    m_isDestroyed = true;
    PlayDestroyEffect();
}