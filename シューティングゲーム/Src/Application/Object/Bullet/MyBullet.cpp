#include "MyBullet.h"
#include"../../Scene/Game/GameScene.h"
void C_MyBullet::Release()
{}

C_MyBullet::C_MyBullet()
{}

C_MyBullet::~C_MyBullet()
{}

void C_MyBullet::Init()
{
	Pos = { 1000,0 };
	Speed = { 1,0 };
	MoveSpeed = 20.0f;
	Size = 1.0f;
	Radius = 8.0f;
	HitRadius = 8.0f;
	HitDiff = { 0,0 };
	Flag = 0;
	HP = 1;
	Damage = 1;
	Timer = 0;
	Angle = 0;
	Tex.Load("Texture/bullet.png");
	m_objType = ObjectType::MyBullet;
}

void C_MyBullet::Update()
{
	if(Flag){
		if(Flag==1||Timer>30){
			Pos += Speed * MoveSpeed;
		}
		Timer++;
		for (auto& obj : m_owner->GetObjList()) {
			ObjectType type = obj->GetObjType();
			if (type == ObjectType::EnemyBullet) {
				Math::Vector2 v;
				v = obj->GetPos() - Pos;
				if (v.Length() < HitRadius + obj->GetHitRadius()) {
					Hit(obj->GetObjDamage());
					obj->Hit(Damage);
				}
			}
		}
		if (abs(Pos.x) > 708) Flag = 0;
		Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x, (int)(Pos.y), 0);
		Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
		Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(Angle));
		Mat = scale * rotate * trans;
	}
}

void C_MyBullet::Draw()
{
	if(Flag){
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 0, 0, 16, 16 }, 1.0f);
	}
}

void C_MyBullet::Reset()
{
	Pos = { 0,0 };
	Speed = { 0,0 };
	Flag = 0;
	Timer = 0;
}

void C_MyBullet::Shot(Math::Vector2 playerPos, int flag,float Radius,int hp)
{
	Pos = playerPos;
	Flag = flag;
	Radius = Radius;
	HP = hp;
}

void C_MyBullet::Hit(int damage)
{
	HP -= damage;
	if (HP < 0)
	{
		Flag = 0;
	}
}


