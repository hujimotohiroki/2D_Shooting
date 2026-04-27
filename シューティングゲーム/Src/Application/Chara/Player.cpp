#include"Player.h"
#include"../Scene/Game/GameScene.h"
#include"../Bullet/MyBullet.h"
#define rep(i,N) for(int i=0;i<N;i++)
C_Player::C_Player()
{}

C_Player::~C_Player()
{}

void C_Player::Init()
{
	X = 0;
	Y = -392;
	MoveSpeed = 10.0f;
	SpeedX = 0;
	SpeedY = 0;
	Flag = 1;
	Anim = 0;
	Size = 1.0f;
	Radius = 32.0f;
	HP = 100;
	Timer = 0;
	PrevShot = 0;
	Tex.Load("Texture/player.png");
}

void C_Player::Update()
{
	if(Flag!=0){
		MoveSpeed = 10.0f;
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
			MoveSpeed = 5.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			X += MoveSpeed;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			X -= MoveSpeed;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			Y += MoveSpeed;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			Y -= MoveSpeed;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			
			if (Timer - PrevShot >= 10) {
				int bu = 0;
				do {
					mybullet = m_owner->GetMyBullet(bu);
					if (!mybullet)break;
					bu++;
				} while (mybullet->GetFlag());
				if(mybullet)
				{
					mybullet->Shot(X, Y, Flag);
				}
				PrevShot = Timer;
			}
		}
		if (X > 608) X = 608;
		if (X < -608)X = -608;
		if (Y > 328)Y = 328;
		if (Y < -328)Y = -328;
	}
	if (HP <= 0) {
		Flag = 0;

	}
	Timer++;
	Math::Matrix trans = Math::Matrix::CreateTranslation(X, (int)(Y), 0);
	Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
	Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(270));
	Mat = scale * rotate * trans;
}

void C_Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(Mat);
	SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ (int)(Anim) * 64,0, 64, 64 }, 1.0f);
}

void C_Player::Reset()
{
	Flag = 1;
	X = 0;
	Y = -200;
}
