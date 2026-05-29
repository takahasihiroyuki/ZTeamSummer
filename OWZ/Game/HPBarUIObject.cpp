#include "stdafx.h"
#include "HPBarUIObject.h"
#include "DummyEnemy.h"

void PlayerHUDHPBarUI::Init(HPComponent* hp)
{
	m_hp = hp;

	ScreenSpaceUIObject::Init(); // 親は見た目なし

	AddChildren<ScreenSpaceUIObject>("background");
	AddChildren<ScreenSpaceUIObject>("health");
	AddChildren<ScreenSpaceUIObject>("shield");
	AddChildren<ScreenSpaceUIObject>("armor");
	AddChildren<ScreenSpaceUIObject>("overHealth");
	AddChildren<ScreenSpaceUIObject>("frame");

	m_background = static_cast<ScreenSpaceUIObject*>(GetChildren("background"));
	m_healthBar = static_cast<ScreenSpaceUIObject*>(GetChildren("health"));
	m_shieldBar = static_cast<ScreenSpaceUIObject*>(GetChildren("shield"));
	m_armorBar = static_cast<ScreenSpaceUIObject*>(GetChildren("armor"));
	m_overHealthBar = static_cast<ScreenSpaceUIObject*>(GetChildren("overHealth"));
	m_frame = static_cast<ScreenSpaceUIObject*>(GetChildren("frame"));

	if (!m_background || !m_healthBar || !m_shieldBar || !m_armorBar || !m_overHealthBar || !m_frame) {
		return;
	}

	// 画像は色ごとに別DDS
	m_background->Init("Assets/UI/hp_bar_bg.dds", m_totalWidth, m_height);
	m_healthBar->Init("Assets/UI/hp_bar_fill_health.dds", m_totalWidth, m_height);
	m_shieldBar->Init("Assets/UI/hp_bar_fill_shield.dds", m_totalWidth, m_height);
	m_armorBar->Init("Assets/UI/hp_bar_fill_armor.dds", m_totalWidth, m_height);
	m_overHealthBar->Init("Assets/UI/hp_bar_fill_overhealth.dds", m_totalWidth, m_height);
	m_frame->Init("Assets/UI/hp_bar_frame.dds", m_totalWidth, m_height);

	auto bgTr = m_background->GetComponent<ScreenUITransformComponent>();
	auto hpTr = m_healthBar->GetComponent<ScreenUITransformComponent>();
	auto shTr = m_shieldBar->GetComponent<ScreenUITransformComponent>();
	auto arTr = m_armorBar->GetComponent<ScreenUITransformComponent>();
	auto ohTr = m_overHealthBar->GetComponent<ScreenUITransformComponent>();
	auto frameTr = m_frame->GetComponent<ScreenUITransformComponent>();

	if (!bgTr || !hpTr || !shTr || !arTr || !ohTr || !frameTr) {
		return;
	}

	m_healthTr = hpTr;
	m_shieldTr = shTr;
	m_armorTr = arTr;
	m_overHealthTr = ohTr;

	// 左端基準
	bgTr->SetPivot({ 0.0f, 0.5f });
	hpTr->SetPivot({ 0.0f, 0.5f });
	shTr->SetPivot({ 0.0f, 0.5f });
	arTr->SetPivot({ 0.0f, 0.5f });
	ohTr->SetPivot({ 0.0f, 0.5f });
	frameTr->SetPivot({ 0.0f, 0.5f });

	bgTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	hpTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	shTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	arTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	ohTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	frameTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

	bgTr->SetScale({ m_totalWidth, m_height, 1.0f });
	frameTr->SetScale({ m_totalWidth, m_height, 1.0f });

	auto rootTr = GetComponent<ScreenUITransformComponent>();
	if (rootTr) {
		rootTr->SetLocalPosition({ 50.0f, -300.0f, 0.0f });
	}

	HPBarValue initValue{};
	UpdateBars(initValue);
}

void PlayerHUDHPBarUI::Update()
{
	ScreenSpaceUIObject::Update();

	// ここは仮
	// 実際には m_hp から現在値/最大値を作る
	HPBarValue value;

	if (m_hp != nullptr) {
		// value.health = m_hp->GetHealth();
		// value.shield = m_hp->GetShield();
		// value.armor = m_hp->GetArmor();
		// value.overHealth = m_hp->GetOverHealth();
		// value.maxHealth = m_hp->GetMaxHealth();
		// value.maxShield = m_hp->GetMaxShield();
		// value.maxArmor = m_hp->GetMaxArmor();
		// value.maxOverHealth = m_hp->GetMaxOverHealth();
	}

	UpdateBars(value);
}

void PlayerHUDHPBarUI::UpdateBars(const HPBarValue& value)
{
	const float totalMax = value.GetTotalMax();
	if (totalMax <= 0.0f) {
		SetBarTransform(m_healthTr, 0.0f, 0.0f);
		SetBarTransform(m_shieldTr, 0.0f, 0.0f);
		SetBarTransform(m_armorTr, 0.0f, 0.0f);
		SetBarTransform(m_overHealthTr, 0.0f, 0.0f);
		return;
	}

	// 各バーの「現在の見た目幅」
	const float healthWidth =
		m_totalWidth * Clamp(value.health / totalMax);
	const float shieldWidth =
		m_totalWidth * Clamp(value.shield / totalMax);
	const float armorWidth =
		m_totalWidth * Clamp(value.armor / totalMax);
	const float overHealthWidth =
		m_totalWidth * Clamp(value.overHealth / totalMax);

	// 左から順に並べる
	float x = 0.0f;

	SetBarTransform(m_healthTr, x, healthWidth);
	x += healthWidth;

	SetBarTransform(m_shieldTr, x, shieldWidth);
	x += shieldWidth;

	SetBarTransform(m_armorTr, x, armorWidth);
	x += armorWidth;

	SetBarTransform(m_overHealthTr, x, overHealthWidth);
}

void EnemyHpBarUI::Init(DummyEnemy* enemy)
{
	m_enemy = enemy;

	WorldSpaceUIObject::Init(); // 親は見た目なし

	AddChildren<WorldSpaceBarUI>("hpBar");
	m_bar = static_cast<WorldSpaceBarUI*>(GetChildren("hpBar"));

	if (!m_bar) {
		return;
	}

	m_bar->Init(
		"Assets/ui/hp/hpbar_bg.DDS",
		"Assets/ui/hp/hpbar_fill.DDS",
		"Assets/ui/hp/hpbar_frame.DDS",
		80.0f,
		10.0f
	);
	m_bar->SetRate(1.0f);

	AddComponent<WorldUIFollowComponent>();
	GetComponent<WorldUIFollowComponent>()->Init(enemy, m_offset);

}

void EnemyHpBarUI::Update()
{
	//NOTE:エネミーがまだないのでコメントアウト

//if (!m_enemy) {
//	RequestDestroy();
//	return;
//}

//// 敵が死んだら消える
//if (m_enemy->IsDead()) {
//	RequestDestroy();
//	return;
//}


//if (!m_bar) {
//	return;
//}

//// HP割合更新
//float maxHp = static_cast<float>(m_enemy->GetMaxHp());
//float hp = static_cast<float>(m_enemy->GetHp());

//float rate = 0.0f;
//if (maxHp > 0.0f) {
//	rate = hp / maxHp;
//}
//m_bar->SetRate(rate);
}
