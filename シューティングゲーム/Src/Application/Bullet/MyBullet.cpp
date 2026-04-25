#include "MyBullet.h"

void C_MyBullet::Release()
{}

C_MyBullet::C_MyBullet()
{}

C_MyBullet::~C_MyBullet()
{}

void C_MyBullet::Init()
{
	X = 0;
	Y = 0;
	SpeedX = 0;
	SpeedY = 0;
	Size = 1.0f;
	Radius = 8.0f;
	Flag = 0;
	Timer = 0;
	Angle = 0;
	Tex.Load("Texture/bullet.png");
}

void C_MyBullet::Update()
{
	if(Flag){
		X += 15;
		Timer++;
		if (X > 700) Flag = 0;
		Math::Matrix trans = Math::Matrix::CreateTranslation(X, (int)(Y), 0);
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
	X = 0;
	Y = 0;
	SpeedX = 0;
	SpeedY = 0;
	Flag = 0;
	Timer = 0;
}

void C_MyBullet::SetFlag()
{
	Flag = 1;
}
