#include "Enemy.h"
#include"../../Scene/Game/GameScene.h"
#include"../../Bullet/EnemyBullet.h"

void C_Enemy::Release()
{}

C_Enemy::C_Enemy()
{}

C_Enemy::~C_Enemy()
{}

void C_Enemy::Init()
{
	Pos = { 608, (float)(rand() % 655 - 328) };
	Flag = 1;
	Speed = {-1, 0};
	Size = 1.0f;
	Radius = 32.0f;
	HitRadius = 32.0f;
	HitDiff = { 0,0 };
	//Flagによって変えたい
	HP = 5;
	Timer = 0;
	PrevShot = 0;
	Tex.Load("Texture/enemy.png");
}

void C_Enemy::Update()
{
	if (Flag == 1) {
		if (Timer < 60) {
			Pos += Speed;
			if (Pos.y < -392) Pos.y = 392;
			if (Pos.x > 608) Pos.x = -608;
			if (Pos.x < -608) Pos.x = 608;
		}
		if (Timer > 60 && Timer - PrevShot >= 10) {
			if (Timer - PrevShot >= 10) {
				int bu = 0;
				do {
					m_enemybullet = m_owner->GetEnemyBullet(bu);
					if (!m_enemybullet)break;
					bu++;
				} while (m_enemybullet->GetFlag());
				if (m_enemybullet)
				{
					m_enemybullet->Shot(Pos, Flag);
				}
				PrevShot = Timer;
			}
		}
		//自機狙いを打ちたい
	}
	if (Flag != 0) {
		if (HP <= 0) {
			Flag = 0;
			//score += 100;
			//Explosion(Pos.x, Pos.y);
		}
		else {
			Timer++;
		}
	}
	Mat = Math::Matrix::CreateTranslation(Pos.x, Pos.y, 0);
}

void C_Enemy::Draw()
{
	if (Flag == 1) {
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 0, 0, 64, 64 }, 1.0f);
	}
}

void C_Enemy::Reset()
{
	Pos = { 608, (float)(rand() % 655 - 328) };
	Flag = 1;
	Speed = { -1,0 };
	Size = 1.0f;
	Radius = 32.0f;
	Timer = 0;
	PrevShot = 0;
}

void C_Enemy::Hit(int damage)
{
	HP -= damage;
	if (HP <= 0) {
		Dead();
	}
}

void C_Enemy::Dead()
{
	Flag = 0;
	m_owner->AddScore(500);
	m_owner->DropMP(Pos);
}
