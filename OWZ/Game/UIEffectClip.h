#pragma once

/// <summary>
/// 一つのUIの演出のまとまりのクラスです
/// 例：UIの選択時の演出、決定時の演出など
/// 一つの演出にこのクラスのインスタンスをひとつ作ります。
/// 演出で使うアニメーションやサウンドはメンバとして持ちません
/// 代わりに、AddAction()の引数でアニメーションなどをキャプチャして再生する関数オブジェクトを渡してください
/// </summary>
class UIEffectClip
{
public:

	/// <summary>
	/// アクションを追加
	///　演出に使うUIアニメーションやサウンドの再生などを関数オブジェクトとしてください
	/// </summary>
	/// <param name="action"></param>
	void AddAction(std::function<void()> action)
	{
		// アクションを追加
		//コピーコストを避けるため、ムーブで追加する
		m_actions.push_back(std::move(action));
	}

	void Play()
	{
		for (auto& action : m_actions) {
			action();
		}
	}

	bool IsEmpty() const
	{
		return m_actions.empty();
	}

private:
	std::vector<std::function<void()>> m_actions;
};
