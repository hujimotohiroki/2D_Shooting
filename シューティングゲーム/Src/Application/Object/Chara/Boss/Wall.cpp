#include "Wall.h"
#include "../../../Scene/Game/GameScene.h"

void C_Wall::Release()
{}

C_Wall::C_Wall()
{}

C_Wall::~C_Wall()
{}

void C_Wall::Init()
{
	Pos = { 300,-1000 };
	HP = 100;
	Speed = { 0,-1 };
	MoveSpeed = -100.0f;
	MaxHP = HP;
	Damage = 50;
	Size = 20;
	Radius = 96;
	HitRadius = 96;
	HitDiff = { -75,0 };
	Timer = 0;
	Flag = 0;
	Tex.Load("Texture/Wall/wall.png");
	WallCoreTex.Load("Texture/Wall/wallcore.png");
	m_hpBarFrameTex.Load("Texture/UI/hp bar/1.png");
	m_hpBarTex.Load("Texture/UI/hp bar/5.png");
	m_objType = ObjectType::Wall;
}

void C_Wall::Update()
{
	if (Flag == 1) {
		//Angle++;
		//if (Angle >= 360) Angle -= 360;
		Clean = 1.0f;
		Pos += Speed * MoveSpeed;
		
		if (Pos.y > 0)Pos.y = 0;
		for (auto& obj : m_owner->GetObjList()) {
			ObjectType type = obj->GetObjType();
			if (type == ObjectType::MyBullet) {
				Math::Vector2 v,bulletPos;
				bulletPos = obj->GetPos();
				v = bulletPos - (Pos + HitDiff);
				if (v.Length() < HitRadius + obj->GetHitRadius()) {
					Hit(obj->GetObjDamage());
					obj->Hit(Damage);
				}
				else if (bulletPos.x > Pos.x + HitDiff.x) {
					obj->Hit(Damage);
				}
			}
		}
	}
	Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x, (int)(Pos.y), 0);
	Math::Matrix scale = Math::Matrix::CreateScale(Size/2, Size, 0);
	Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
	Mat = scale * rotate * trans;
	trans = Math::Matrix::CreateTranslation(Pos.x + HitDiff.x, (int)(Pos.y), 0);
	scale = Math::Matrix::CreateScale(2, 2, 0);
	rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
	WallCoreMat = scale * rotate * trans;
}

void C_Wall::Draw()
{
	if (Flag) {
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 16, 24, 16, 40 }, 1);
		SHADER.m_spriteShader.SetMatrix(WallCoreMat);
		SHADER.m_spriteShader.DrawTex(&WallCoreTex, Math::Rectangle{ 0, 0, 24, 96 }, Clean);
		DrawHpBar();
	}
}

void C_Wall::Reset()
{
	Flag = 0;
	Pos.x = 0;
	Pos.y = 456;
	HP = 100;
}

void C_Wall::Hit(int damage)
{
	HP -= damage;
	Clean = 0.7;
	if (HP <= 0) {
		Dead();
	}
}

void C_Wall::Dead()
{
	Flag = 0;
	m_owner->AddScore(500);
	int tmp = 30;
	m_owner->DropMP(Pos, tmp);
}

void C_Wall::DrawHpBar()
{
	float maxWidth = 100.0f;
	float height = 20.0f;

	float rate = float(HP) / float(MaxHP);
	if (rate < 0) rate = 0;
	if (rate > 1) rate = 1;

	float x = 0;
	float y = 100;

	// =============================
	// ① フレーム描画
	// =============================
	{
		Math::Matrix scale = Math::Matrix::CreateScale(1.0f, 2.0f, 0);
		Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x+HitDiff.x+x, Pos.y+HitDiff.y+y, 0);
		Math::Matrix mat = scale * trans;
		SHADER.m_spriteShader.SetMatrix(mat);

		Math::Rectangle frameRect{ 0,0,100,10 };
		SHADER.m_spriteShader.DrawTex(&m_hpBarFrameTex, frameRect, 1.0f);
	}

	// =============================
	// ② 中身描画（左端固定スケール）
	// =============================
	{
		float halfW = maxWidth * 0.5f;

		// 左端にアンカーを移動（中心 → 左端）
		float anchorOffset = maxWidth * 0.5f;   // 中心から左端への距離

		Math::Matrix moveToRight = Math::Matrix::CreateTranslation(anchorOffset, 0, 0);
		Math::Matrix scale = Math::Matrix::CreateScale(rate, 2.0f, 0);
		Math::Matrix moveBack = Math::Matrix::CreateTranslation(-anchorOffset, 0, 0);

		Math::Matrix moveToPos = Math::Matrix::CreateTranslation(Pos.x + HitDiff.x + x, Pos.y + HitDiff.y + y, 0);

		Math::Matrix mat = moveToRight * scale * moveBack * moveToPos;
		SHADER.m_spriteShader.SetMatrix(mat);

		Math::Rectangle src{ 0,0,100,10 };
		SHADER.m_spriteShader.DrawTex(&m_hpBarTex, src, 1.0f);
	}
}