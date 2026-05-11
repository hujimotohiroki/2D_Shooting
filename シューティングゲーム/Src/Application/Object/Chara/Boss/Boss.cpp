#include "Boss.h"
#include "../../../Scene/Game/GameScene.h"

void C_Boss::Release()
{}

C_Boss::C_Boss()
{}

C_Boss::~C_Boss()
{}

void C_Boss::Init()
{
	Pos = { 800,100 };
	HP = 100;
	MaxHP = HP;
	Damage = 10;
	Size = 15;	
	Radius = 96;
	HitRadius = 96;
	HitDiff = { 0,0 };
	Timer = 0;
	Flag = 0;
	Tex.Load("Texture/wall.png");
	m_hpBarFrameTex.Load("Texture/UI/hp bar/1.png");
	m_hpBarTex.Load("Texture/UI/hp bar/5.png");
	m_objType = ObjectType::Boss;
}

void C_Boss::Update()
{
	if (Flag == 1) {
		//Angle++;
		//if (Angle >= 360) Angle -= 360;
		Clean = 1.0f;
		Pos.x -= 2.0f;
		if (Pos.x < 525)Pos.x = 525;
		for (auto& obj : m_owner->GetObjList()) {
			ObjectType type = obj->GetObjType();
			if (type == ObjectType::MyBullet) {
				Math::Vector2 v;
				v = obj->GetPos() - (Pos+HitDiff);
				if (v.Length() < HitRadius + obj->GetHitRadius()) {
					Hit(obj->GetObjDamage());
					obj->Hit(Damage);
				}
			}
		}
	}
	Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x, (int)(Pos.y), 0);
	Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
	Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
	Mat = scale * rotate * trans;
}

void C_Boss::Draw()
{
	if(Flag){
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 16, 24, 16, 40 }, Clean);
		Math::Color color = { 0,0.5f,0,0.1f };
		SHADER.m_spriteShader.DrawCircle(HitDiff.x, HitDiff.y, 6, &color, true);
		DrawHpBar();
	}
}

void C_Boss::Reset()
{
	Flag = 0;
	Pos.x = 0;
	Pos.y = 456;
	HP = 100;
}

void C_Boss::Hit(int damage)
{
	HP -= damage;
	Clean = 0.7;
	if (HP <= 0) {
		Dead();
	}
}

void C_Boss::Dead()
{
	Flag = 0;
	m_owner->AddScore(500);
	int tmp = 30;
	m_owner->DropMP(Pos, tmp);
	m_owner->SetBossFlag(false);
}

void C_Boss::DrawHpBar()
{
	float maxWidth = 520.0f;
	float height = 20.0f;

	float rate = float(HP) / float(MaxHP);
	if (rate < 0) rate = 0;
	if (rate > 1) rate = 1;

	float x = 300;
	float y = 320;

	// =============================
	// ① フレーム描画
	// =============================
	{
		Math::Matrix scale = Math::Matrix::CreateScale(1.0f, 2.0f, 0);
		Math::Matrix trans = Math::Matrix::CreateTranslation(x, y, 0);
		Math::Matrix mat = scale * trans;
		SHADER.m_spriteShader.SetMatrix(mat);

		Math::Rectangle frameRect{ 0,0,520,10 };
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

		Math::Matrix moveToPos = Math::Matrix::CreateTranslation(x, y, 0);

		Math::Matrix mat = moveToRight * scale * moveBack * moveToPos;
		SHADER.m_spriteShader.SetMatrix(mat);

		Math::Rectangle src{ 0,0,520,10 };
		SHADER.m_spriteShader.DrawTex(&m_hpBarTex, src, 1.0f);
	}
}