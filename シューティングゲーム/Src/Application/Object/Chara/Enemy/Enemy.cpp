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
	Pos = { 0,0 };
	Flag = 0;
	Speed = {-1, 0};
	MoveSpeed = 5.0f;
	Size = 2.0f;
	Radius = 32.0f;
	HitRadius = 32.0f;
	HitDiff = { 0,0 };
	//Flagによって変えたい
	HP = 5;
	Damage = 5;
	Timer = 0;
	PrevShot = 0;
	Clean = 1.0;
	enemyTex1.Load("Texture/enemy/Book_Small_Grey.png");
	enemyTex2.Load("Texture/enemy/Book_Small_LightRed.png");
	enemyTex3.Load("Texture/enemy/Book_Big_LightBlue.png");
	m_objType = ObjectType::Enemy;
}

void C_Enemy::Update()
{
	Clean = 1.0f;
	switch (Flag) {
	case 1:
		Pos += Speed * MoveSpeed;
		if (Timer > 30 && Timer - PrevShot >= 60/m_owner->GetWall()) {
			m_owner->EnemyShot(Pos, Flag,180);
			PrevShot = Timer;
		}
		if (Pos.x < -608) Flag=0;
		break;
	case 2:
		Pos += Speed * MoveSpeed;
		if (Timer > 30 && Timer - PrevShot >= 60 / m_owner->GetWall()) {
			for (auto& obj : m_owner->GetObjList()) {
				ObjectType type = obj->GetObjType();
				if (type == ObjectType::Player) {
					Math::Vector2 playerPos;
					playerPos = obj->GetPos();
					m_owner->EnemySnipeShot(Pos, playerPos, Flag);
				}
			}
			PrevShot = Timer;
		}
		break;
	case 3:
		if (Timer < 60) {
			Pos += Speed * MoveSpeed;
		}
		else if (Timer > 90 && Timer < 420 && Timer - PrevShot >= 10) {
			m_owner->EnemySpreadShot(Pos, Flag);
			PrevShot = Timer;
		}
		else if (Timer > 420) {
			Pos += Speed * MoveSpeed;
			if (Pos.x < -608) Flag = 0;
		}
		break;
	default:
		break;
	}
	if (Flag > 0) {
		//当たり判定
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
		if(m_owner)
		Timer++;
	}
	if (Flag == -1) {
		Speed.y -= 1;
		Pos += Speed;
		if (Pos.y < -392) Flag = 0;
	}
	Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x, (int)(Pos.y), 0);
	Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
	Math::Matrix rotate = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	Mat = scale * rotate * trans;
}

void C_Enemy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(Mat);
	switch (Flag) {
	case 1:
		SHADER.m_spriteShader.DrawTex(&enemyTex1, Math::Rectangle{ 0, 0, 32, 32 }, Clean);
		break;
	case 2:
		SHADER.m_spriteShader.DrawTex(&enemyTex2, Math::Rectangle{ 0, 0, 32, 32 }, Clean);
		break;
	case 3:
		SHADER.m_spriteShader.DrawTex(&enemyTex3, Math::Rectangle{ 0, 0, 64, 64 }, Clean);
		break;
	}
}

void C_Enemy::Reset()
{
	Pos = { 0,0 };
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
	Clean = 0.3;
	if (HP <= 0) {
		Dead();
	}
}

void C_Enemy::Dead()
{
	Flag = -1;
	if(Timer<100) m_owner->AddScore(100-Timer);
	int tmp = 3;
	m_owner->DropMP(Pos,tmp);
}
