#include "Enemy.h"
#include"../../../Scene/Game/GameScene.h"
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
	Flag = 3;
	Speed = {-1, 0};
	MoveSpeed = 3.0f;
	Size = 1.0f;
	Radius = 32.0f;
	HitRadius = 32.0f;
	HitDiff = { 0,0 };
	//Flagによって変えたい
	HP = 5;
	Damage = 5;
	Timer = 0;
	PrevShot = 0;
	Tex.Load("Texture/enemy.png");
	m_objType = ObjectType::Enemy;
}

void C_Enemy::Update()
{
	if (Flag != 0) {
		if (Timer < 60) {
			Pos += Speed*MoveSpeed;
			if (Pos.y < -392) Pos.y = 392;
			if (Pos.x > 608) Pos.x = -608;
			if (Pos.x < -608) Pos.x = 608;
		}
		if (Timer > 60 && Timer - PrevShot >= 10) {
			if(Flag==1){
				if (Timer - PrevShot >= 10) {
					m_owner->EnemyShot(Pos, Flag);
				}
			}
			if (Flag == 2) {
				if (Timer - PrevShot >= 10) {
					for (auto& obj : m_owner->GetObjList()) {
						ObjectType type = obj->GetObjType();
						if (type == ObjectType::Player) {
							Math::Vector2 playerPos;
							playerPos = obj->GetPos();
							m_owner->EnemySnipeShot(Pos, playerPos, Flag);
						}
					}
				}
			}
			if (Flag == 3) {
				if (Timer - PrevShot >= 10) {
					m_owner->EnemySpreadShot(Pos, Flag);
				}
			}
			PrevShot = Timer;
		}
		if (Timer > 180) {
			Pos += Speed*MoveSpeed;
			if (Pos.y < -392) Pos.y = 392;
			if (Pos.x > 608) Pos.x = -608;
			if (Pos.x < -608) Pos.x = 608;
		}
		//自機狙いを打ちたい
		for (auto& obj : m_owner->GetObjList()) {
			ObjectType type = obj->GetObjType();
			if (type == ObjectType::MyBullet) {
				Math::Vector2 v;
				v = obj->GetPos() - Pos;
				if (v.Length() < HitRadius + obj->GetHitRadius()) {
					Hit(obj->GetObjDamage());
					obj->Hit(Damage);
				}
			}
		}
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
	if (Flag != 0) {
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
	int tmp = 1;
	m_owner->DropMP(Pos,tmp);
}
