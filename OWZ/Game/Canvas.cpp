#include "stdafx.h"
#include "Canvas.h"
#include "UIObfect.h"

Canvas::Canvas(CanvasRenderMode renderMode)
	: m_renderMode(renderMode)
{
}

Canvas::Canvas()
	: Canvas(CanvasRenderMode::ScreenSpace)
{
}

Canvas::~Canvas() = default;

void Canvas::AddUI(std::unique_ptr<UIObject> ui)
{
	if (ui == nullptr) {
		return;
	}

	// 二重追加防止
	auto existsInMain = std::find(m_uiObjects.begin(), m_uiObjects.end(), ui);
	if (existsInMain != m_uiObjects.end()) {// すでにメインのリストにあるなら追加しない
		return;
	}

	auto existsInPending = std::find(m_pendingAddObjects.begin(), m_pendingAddObjects.end(), ui);
	if (existsInPending != m_pendingAddObjects.end()) {// すでに追加待ちのリストにあるなら追加しない
		return;
	}

	if (m_isUpdating) {// 更新中なら追加待ちリストに追加。
		m_pendingAddObjects.push_back(std::move(ui));
	}
	else {
		m_uiObjects.push_back(std::move(ui));
	}
}

void Canvas::RemoveUI(UIObject* ui)
{
	if (ui == nullptr) {
		return;
	}

	if (m_isUpdating) {
		// 追加まちのリストにあれば、そちらからすぐに削除して、更新後に追加されないようにする
		{
			auto addIt = std::remove_if(
				m_pendingAddObjects.begin(),
				m_pendingAddObjects.end(),
				[ui](const std::unique_ptr<UIObject>& obj)
				{
					return obj.get() == ui;
				}
			);

			if (addIt != m_pendingAddObjects.end()) {
				m_pendingAddObjects.erase(addIt, m_pendingAddObjects.end());
				return;
			}
		}

		// 削除待ちのリストに登録。
		{
			// すでに削除待ちのリストにあるか確認して、なければ追加する
			auto existsInPending = std::find(m_pendingRemoveObjects.begin(), m_pendingRemoveObjects.end(), ui);
			if (existsInPending == m_pendingRemoveObjects.end()) {
				m_pendingRemoveObjects.push_back(ui);
			}
		}
	}
	else {
		// 更新中でなければすぐに削除
		auto it = std::remove_if(
			m_uiObjects.begin(),
			m_uiObjects.end(),
			[ui](const std::unique_ptr<UIObject>& obj)
			{
				return obj.get() == ui;
			}
		);
		m_uiObjects.erase(it, m_uiObjects.end());
	}
}

void Canvas::Clear()
{

	if (m_isUpdating) {// 更新中は保留リストに追加して、更新後に反映する

		//古い保留リストをクリア
		m_pendingRemoveObjects.clear();

		//現在のUIオブジェクトをすべて削除保留リストに追加
		for (auto& ui : m_uiObjects) {
			m_pendingRemoveObjects.push_back(ui.get());
		}

		// 追加待ちも全部破棄
		m_pendingAddObjects.clear();
	}
	else {// 更新中でなければすぐにクリア
		m_uiObjects.clear();
		m_pendingAddObjects.clear();
		m_pendingRemoveObjects.clear();
	}
}

void Canvas::FlushPending()
{
	// 削除を先に反映
	for (const auto& ui : m_pendingRemoveObjects) {
		//m_pendingRemoveObjectsと同じUIオブジェクトをm_uiObjectsから削除
		auto it = std::remove_if(
			m_uiObjects.begin(),
			m_uiObjects.end(),
			[ui](const std::unique_ptr<UIObject>& obj)
			{
				return obj.get() == ui;
			}
		);
		m_uiObjects.erase(it, m_uiObjects.end());
	}
	m_pendingRemoveObjects.clear();

	// 追加を反映
	for (auto& ui : m_pendingAddObjects) {
		if (ui == nullptr) {
			continue;
		}

		auto it = std::find(m_uiObjects.begin(), m_uiObjects.end(), ui);
		if (it == m_uiObjects.end()) {
			m_uiObjects.push_back(std::move(ui));
		}
	}
	m_pendingAddObjects.clear();

	//　UIオブジェクトの中で破棄リクエストが来ているものを削除
	auto it = std::remove_if(
		m_uiObjects.begin(),
		m_uiObjects.end(),
		[](const std::unique_ptr<UIObject>& ui)
		{
			return ui == nullptr || ui->IsDestroyRequested();
		}
	);
	m_uiObjects.erase(it, m_uiObjects.end());
}

bool Canvas::Start()
{
	for (auto& ui : m_uiObjects) {
		if (ui == nullptr) {
			continue;
		}

		ui->StartWrapper();
	}

	return true;
}

void Canvas::Update()
{
	m_isUpdating = true;

	for (auto& ui : m_uiObjects) {
		if (ui == nullptr) {
			continue;
		}

		ui->StartWrapper();
		ui->UpdateWrapper();
	}

	m_isUpdating = false;

	FlushPending();
}

void Canvas::Render()
{
	for (auto& ui : m_uiObjects) {
		if (ui == nullptr) {
			continue;
		}

		ui->Render();
	}
}