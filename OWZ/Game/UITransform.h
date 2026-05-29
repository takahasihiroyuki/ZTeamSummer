#pragma once

class UITransformBase :public Component
{
	appClass(UITransformBase);
protected:
	Vector3 m_localPosition = Vector3::Zero;			//
	Vector3 m_renderPosition = Vector3::Zero;   // 最終的に表示する画面の座標。
	Vector3 m_scale = Vector3::One;
	Vector2 m_pivot = { 0.5f, 0.5f };
	Quaternion m_rotation = Quaternion::Identity;
	bool m_isDirty = true;

public:
	virtual ~UITransformBase() = default;
	virtual void UpdateTransform() = 0;

	void SetLocalPosition(const Vector3& pos)
	{
		m_localPosition = pos;
		m_isDirty = true;
	}

	void SetPivot(const Vector2& pivot)
	{
		m_pivot = pivot;
		m_isDirty = true;
	}

	void SetScale(const Vector3& size)
	{
		m_scale = size;
		m_isDirty = true;
	}

	void AddPosition(const Vector3& pos)
	{
		m_localPosition += pos;
		m_isDirty = true;
	}

	void AddScale(const Vector3& size)
	{
		m_scale += size;
		m_isDirty = true;
	}

	Vector3 GetLocalPosition() const
	{
		return m_localPosition;
	}

	Vector2 GetPivot() const
	{
		return m_pivot;
	}

	Vector3 GetScale() const
	{
		return m_scale;
	}

	Quaternion GetRotation() const
	{
		return m_rotation;
	}

	Vector3 GetRenderPosition() const
	{
		return m_renderPosition;
	}

};

class WorldUITransformComponent :public UITransformBase
{
private:
	appClass(WorldUITransformComponent);

	bool    m_isVisible = true;
public:

	void UpdateTransform() override;

	void Update() override
	{
		UpdateTransform();
	}

};

class ScreenUITransformComponent :public UITransformBase
{
private:


public:


	void UpdateTransform() override;

	void Update() override
	{
		UpdateTransform();
	}


};
