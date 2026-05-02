#include "Hit.h"
#include "../GameScene.h"
#include "../../../Object/Chara/Player/Player.h"
#include "../../../Object/Chara/Enemy/Enemy.h"
#include "../../../Object/Bullet/EnemyBullet.h"
#include "../../../Object/Bullet/MyBullet.h"
#include "../../../Object/Bullet/Mp.h"

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
			if(m_enemybullet->GetFlag()){
				if (CheckHit(pos, m_enemybullet->GetPos(), HitRadius + m_enemybullet->GetHitRadius())) {
					m_player->Hit(5);
					m_enemybullet->Hit();
				}
			}
			bu++;
		}
	}
	int en = 0;
	while (1) {
		m_enemy = m_owner->GetEnemy(en);
		if (!m_enemy)break;
		if (m_enemy->GetFlag()) {
			int bu=0;
			Math::Vector2 pos = m_enemy->GetPos();
			float HitRadius = m_enemy->GetHitRadius();
			while (1) {
				m_mybullet = m_owner->GetMyBullet(bu);
				if (!m_mybullet)break;
				if (m_mybullet->GetFlag()) {
					if (CheckHit(pos, m_mybullet->GetPos(), HitRadius + m_mybullet->GetHitRadius())) {
						m_enemy->Hit(5);
						m_mybullet->Hit();
					}
				}
				bu++;
			}
		}
		en++;
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
