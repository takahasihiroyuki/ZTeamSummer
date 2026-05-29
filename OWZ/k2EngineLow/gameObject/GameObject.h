#pragma once
namespace nsK2EngineLow
{
	class Component;
	class GameObject : public Noncopyable
	{
	public:
		GameObject();
		virtual ~GameObject();
	public:
		virtual bool Start() { return true; }
		virtual void Update() {}
		virtual void Render() {}

	public:
		bool IsStart() const { return m_isStart; }
		bool IsActive() const { return m_isActive; }


		void Activate() { m_isActive = true; }
		void Deactivate() { m_isActive = false; }

	public:
		void UpdateWrapper();

		void StartWrapper()
		{
			if (m_isActive && !m_isStart) {
				if (Start()) {
					//初期化処理完了。
					m_isStart = true;
				}

			}
		}

		//NOTE:ムーブ後の空の変数を返していたので、ムーブ後も有効な変数を返すように修正しました。
		template <typename T, class... Args>
		T* AddComponent(Args&&... args) {
			auto t = std::make_unique<T>(std::forward<Args>(args)...);

			T* result = t.get();

			result->SetOwner(this);
			result->Active();
			m_componentList.emplace(T::ID(), std::move(t));

			return result;
		}

		template <typename T>
		T* GetComponent() {
			return static_cast<T*>(m_componentList.find(T::ID())->second.get());
		}

		template <typename T, class... Args>
		void AddChildren(std::string name, Args&&... args) {
			std::unique_ptr<GameObject> gameObject = std::make_unique<T>(std::forward<Args>(args)...);
			gameObject->SetParent(this);
			//NOTE:ユニークをコピーしていたので、ムーブするように修正しました。
			m_children.emplace(name, std::move(gameObject));
		}

		void AddChildren(std::string name, std::unique_ptr<GameObject> gameObject) {
			gameObject->SetParent(this);
			m_children.emplace(name, std::move(gameObject));
		}

		void SetParent(GameObject* parent) {
			m_parent = parent;
		}

		GameObject* GetParent() {
			return m_parent;
		}

		void SetChildren(std::string name, std::unique_ptr<GameObject> gameObject) {
			m_children.emplace(name, std::move(gameObject));
		}
		GameObject* GetChildren(std::string name) {
			return m_children.find(name)->second.get();
		}

	protected:
		bool m_isStart = false;							//Startの開始フラグ。
		bool m_isActive = true;							//Activeフラグ。

		GameObject* m_parent = nullptr;//ヌルが入っていなかったので修正しました
		std::unordered_map <std::string, std::unique_ptr<GameObject>> m_children;

		std::unordered_map <uint32_t, std::unique_ptr<Component>> m_componentList;
	};

}
