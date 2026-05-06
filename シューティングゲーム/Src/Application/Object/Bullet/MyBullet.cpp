#include "MyBullet.h"

void C_MyBullet::Release()
{}

C_MyBullet::C_MyBullet()
{}

C_MyBullet::~C_MyBullet()
{}

void C_MyBullet::Init()
{
	Pos = { 0,0 };
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
		Pos += Speed*MoveSpeed;
		Timer++;
		if (abs(Pos.x) > 700) Flag = 0;
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

void C_MyBullet::Shot(Math::Vector2 playerPos, int flag)
{
	Pos = playerPos;
	Flag = flag;
}

void C_MyBullet::Hit(int damage)
{
	HP -= damage;
	if (HP < 0)
	{
		Flag = 0;
	}
}


