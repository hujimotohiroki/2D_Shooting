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
	X = 608;
	Y = rand() % 655 - 328;
	Flag = 1;
	SpeedX = -1;
	SpeedY = 0;
	Size = 1.0f;
	Radius = 32.0f;
	//Flagによって変えたい
	HP = 3;
	Timer = 0;
	PrevShot = 0;
	Tex.Load("Texture/enemy.png");
}

void C_Enemy::Update()
{
	if (Flag == 1) {
		if (Timer < 60) {
			Y -= SpeedY;
			X += SpeedX;
			if (Y < -392) Y = 392;
			if (X > 608) X = -608;
			if (X < -608) X = 608;
		}
		if (Timer > 60 && Timer - PrevShot >= 10) {
			if (Timer - PrevShot >= 10) {
				int bu = 0;
				do {
					enemybullet = m_owner->GetEnemyBullet(bu);
					if (!enemybullet)break;
					bu++;
				} while (enemybullet->GetFlag());
				if (enemybullet)
				{
					enemybullet->Shot(X, Y, Flag);
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
			//Explosion(X, Y);
		}
		else {
			Timer++;
		}
	}
	Mat = Math::Matrix::CreateTranslation(X, Y, 0);
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
	X = 608;
	Y = rand() % 655 - 328;
	Flag = 1;
	SpeedX = -1;
	SpeedY = 0;
	Size = 1.0f;
	Radius = 32.0f;
	Timer = 0;
}
