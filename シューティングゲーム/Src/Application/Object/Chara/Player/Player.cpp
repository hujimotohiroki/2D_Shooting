#include"Player.h"
#include"../../../Scene/Game/GameScene.h"
#include"../../Bullet/MyBullet.h"
#define rep(i,N) for(int i=0;i<N;i++)
C_Player::C_Player()
{}

C_Player::~C_Player()
{}

void C_Player::Init()
{
	Pos = { 0,-392 };
	MoveSpeed = 10.0f;
	Speed = { 0,0 };
	Flag = 1;
	Anim = 0;
	Size = 1.0f;
	Radius = 32.0f;
	HitRadius = 5.0f;
	HitDiff = { 0,0 };
	HP = 10;
	Timer = 0;
	PrevShot = 0;
	Tex.Load("Texture/player.png");
}

void C_Player::Update()
{
	if(Flag){
		MoveSpeed = 10.0f;
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
			MoveSpeed = 5.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			Pos.x += MoveSpeed;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			Pos.x -= MoveSpeed;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			Pos.y += MoveSpeed;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			Pos.y -= MoveSpeed;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			
			if (Timer - PrevShot >= 10) {
				int bu = 0;
				do {
					m_mybullet = m_owner->GetMyBullet(bu);
					if (!m_mybullet)break;
					bu++;
				} while (m_mybullet->GetFlag());
				if(m_mybullet)
				{
					m_mybullet->Shot(Pos, Flag);
				}
				PrevShot = Timer;
			}
		}
		if (Pos.x > 608) Pos.x = 608;
		if (Pos.x < -608)Pos.x = -608;
		if (Pos.y > 328)Pos.y = 328;
		if (Pos.y < -328)Pos.y = -328;
	}
	Timer++;
	Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x, (int)(Pos.y), 0);
	Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
	Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(270));
	Mat = scale * rotate * trans;
}

void C_Player::Draw()
{
	if(Flag){
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ (int)(Anim) * 64,0, 64, 64 }, 1.0f);
	}
}

void C_Player::Reset()
{
	Flag = 1;
	Pos = {0, -200};
	PrevShot = 0;
}

void C_Player::Hit(int damage)
{
	HP -= damage;
	if (HP <= 0) {
		Dead();
	}
}

void C_Player::Dead()
{
	Flag = 0;
}
