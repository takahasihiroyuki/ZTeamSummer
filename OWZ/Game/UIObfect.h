#pragma once
#include"UITransform.h"
#include"SpriteComponent.h"

class UIObject :public nsK2EngineLow::GameObject
{
protected:
	bool m_isDestroyRequested = false;	//削除のリクエスト
	bool m_hasVisual = false;			//見た目があるかどうか
public:

	UIObject()
	{
	}

	virtual ~UIObject() noexcept = default;

	virtual void Init() {};

	/// <summary>
	/// 初期化
	/// 見た目をつけたい場合だけ呼び出してください
	/// </summary>
	/// <param name="filePath"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="alphaBlendMode"></param>
	virtual void Init(
		const char* filePath,
		float w,
		float h,
		AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans
	)
	{
		m_hasVisual = true;
		auto sprite = AddComponent<SpriteComponent>();
		if (sprite != nullptr) {
			sprite->Init(filePath, w, h, alphaBlendMode);
		}
	}

	void Render() override
	{
		if (!m_hasVisual)return;
		auto sprite = GetComponent<SpriteComponent>();
		sprite->Render();
	}

	/// <summary>
	/// このUIオブジェクトを破棄したい時に呼びます。
	/// このUIオブジェクトを消すことをリクエストします。
	/// そのリクエストを見てキャンバスが削除します。
	/// </summary>
	void RequestDestroy()
	{
		if (m_isDestroyRequested) {
			return;
		}

		m_isDestroyRequested = true;
		Deactivate();
	}

	bool IsDestroyRequested() const
	{
		return m_isDestroyRequested;
	}
};

class ScreenSpaceUIObject : public UIObject
{
private:

public:
	ScreenSpaceUIObject()
	{
	}

	void Init()
	{
		UIObject::Init();
		AddComponent<ScreenUITransformComponent>();
	}

	void Init(
		const char* filePath,
		float w,
		float h,
		AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans)
	{
		UIObject::Init(filePath, w, h, alphaBlendMode);

		//必要なコンポーネントを追加。
		AddComponent<ScreenUITransformComponent>();

	}

	virtual ~ScreenSpaceUIObject() noexcept = default;
};

class WorldSpaceUIObject : public UIObject
{
private:

public:

	WorldSpaceUIObject()
	{
	}

	void Init() override
	{
		AddComponent<WorldUITransformComponent>();
	}

	void Init(
		const char* filePath,
		float w,
		float h,
		AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans)override
	{
		UIObject::Init(filePath, w, h, alphaBlendMode);

		//必要なコンポーネントを追加。
		AddComponent<WorldUITransformComponent>();
	}

	virtual ~WorldSpaceUIObject() noexcept = default;
};



