#include "Hit.h"
#include "../GameScene.h"
#include "../../../Chara/Player.h"
#include "../../../Bullet/EnemyBullet.h"

C_Hit::C_Hit()
{}

C_Hit::~C_Hit()
{}

void C_Hit::Init()
{}

void C_Hit::Update()
{
	m_player = m_owner->GetPlayer();
	if (m_player && m_player->GetFlag()) {
		int bu = 0;
		Math::Vector2 pos = m_player->GetPos();
		float HitRadius = m_player->GetHitRadius();
		while (1) {
			m_enemybullet = m_owner->GetEnemyBullet(bu);
			if (!m_enemybullet) break;
			if (CheckHit(pos, m_enemybullet->GetPos(), HitRadius + m_enemybullet->GetHitRadius())) {
				m_player->Hit(5);
				m_enemybullet->Hit();
			}
			bu++;
		}
	}
}

void C_Hit::Draw()
{}

bool C_Hit::CheckHit(Math::Vector2 A, Math::Vector2 B, float distance)
{
	float x = A.x - B.x;
	float y = A.y - B.y;
	if (sqrt(x * x + y * y) < distance)return true;
	return false;
}
