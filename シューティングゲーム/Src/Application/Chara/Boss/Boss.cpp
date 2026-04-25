#include "Boss.h"

void C_Boss::Release()
{}

C_Boss::C_Boss()
{}

C_Boss::~C_Boss()
{}

void C_Boss::Init()
{
	X = 0;
	Y = 456;
	HP = 100;
	Size = 3;	
	Radius = 96;
	Timer = 0;
	Flag = 1;
	Tex.Load("Texture/enemy.png");
}

void C_Boss::Update()
{
	if (Flag == 1) {
		//Angle++;
		//if (Angle >= 360) Angle -= 360;
		Y -= 0.5f;
		if (Y < 0)Y = 0;
		//rep(bu, mybulletnum) {
		//	if (mybulletFlag[bu] == 1) {
		//		if (IS_HIT(X, Y, mybulletX[bu], mybulletY[bu], Radius + mybulletRadius[bu])) {
		//			mybulletFlag[bu] = 0;
		//			Explosion(mybulletX[bu], mybulletY[bu]);
		//			HP--;
		//			if (HP <= 0) {
		//				Flag++;
		//				score += 10000;
		//			}
		//			mybulletY[bu] = 456;
		//		}
		//	}
		//}
	}
	Math::Matrix trans = Math::Matrix::CreateTranslation(X, (int)(Y), 0);
	Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
	Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
	Mat = scale * rotate * trans;
}

void C_Boss::Draw()
{
	SHADER.m_spriteShader.SetMatrix(Mat);
	SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 0,0, 64, 64 }, 1.0f);
}

void C_Boss::Reset()
{
	Flag = 0;
	X = 0;
	Y = 456;
	HP = 100;
}
