#pragma once
enum class CanvasRenderMode
{
	ScreenSpace,
	WorldSpace
};

enum class CanvasType
{
	WorldPersistent = 0,	// 頭上HPバーや名前など
	WorldEffect,		// ダメージ数字など一時表示
	HUD,
	Menu,
	Overlay,
	DebugCanvas,
	Count
};

class UIObject;
class Canvas
{
private:
	// 現在保持しているUI
	std::vector<std::unique_ptr<UIObject>> m_uiObjects;
	// Update中に直接追加削除すると危険なので保留リストを持つ
	std::vector<std::unique_ptr<UIObject>> m_pendingAddObjects;		// 追加保留リスト
	std::vector<UIObject*> m_pendingRemoveObjects;					// 削除保留リスト(所有権は持たない)
	bool m_isUpdating = false;
	CanvasRenderMode m_renderMode = CanvasRenderMode::ScreenSpace;

private:
	/// <summary>
	/// 保留していた追加削除を反映。
	/// </summary>
	void FlushPending();

public:
	Canvas(CanvasRenderMode renderMode);
	Canvas();
	~Canvas();

	/// <summary>
	/// CanvasにUIを追加。
	/// </summary>
	void AddUI(std::unique_ptr<UIObject> ui);

	/// <summary>
	/// Canvasから指定のUIを削除。
	/// </summary>
	void RemoveUI(UIObject* ui);

	/// <summary>
	/// Canvas内のUIを全部消す。
	/// </summary>
	void Clear();

	void Update();

	void Render();

	bool Start();

	CanvasRenderMode GetRenderMode() const
	{
		return m_renderMode;
	}

	bool IsScreenSpace() const
	{
		return m_renderMode == CanvasRenderMode::ScreenSpace;
	}

	bool IsWorldSpace() const
	{
		return m_renderMode == CanvasRenderMode::WorldSpace;
	}

	const std::vector<std::unique_ptr<UIObject>>& GetUIObjects() const
	{
		return m_uiObjects;
	}

};

