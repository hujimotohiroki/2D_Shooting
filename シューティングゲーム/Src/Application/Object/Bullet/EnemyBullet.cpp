#include "EnemyBullet.h"

void C_EnemyBullet::Release()
{}

C_EnemyBullet::C_EnemyBullet()
{}

C_EnemyBullet::~C_EnemyBullet()
{}

void C_EnemyBullet::Init()
{
	Pos = { 1000,0 };
	Speed = { 0,0 };
	MoveSpeed = 5.0f;
	Size = 1.0f;
	Radius = 12.0f;
	HitRadius = 12.0f;
	HitDiff = { 0,0 };
	Flag = 0;
	HP = 1;
	Damage = 1;
	Timer = 0;
	Angle = 0;
	Tex.Load("Texture/bullet/Bullet 24x24 Part 5B Free.png");
	m_objType = ObjectType::EnemyBullet;
}

void C_EnemyBullet::Update()
{
	if (Flag) {
		Pos+=Speed*MoveSpeed;
		Timer++;
		if (abs(Pos.x) > 708) Flag = 0;
		if (abs(Pos.y) > 400) Flag = 0;
		Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x, (int)(Pos.y), 0);
		Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
		Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(Angle));
		Mat = scale * rotate * trans;
	}
}

void C_EnemyBullet::Draw()
{
	if (Flag) {
		Anim = Timer % 8;
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 24*Anim, 0, 24, 24 }, 1.0f);
	}
}

void C_EnemyBullet::Reset()
{
	Pos = { 0,0 };
	Speed.x = 0;
	Speed.y = 0;
	Flag = 0;
	Timer = 0;
}

void C_EnemyBullet::Shot(Math::Vector2 enemyPos, int flag)
{
	Pos = enemyPos;
	Flag = flag;
}

void C_EnemyBullet::Hit(int damage)
{
	HP -= damage;
	if(HP<0)
	{
		Flag = 0;
	}
}
