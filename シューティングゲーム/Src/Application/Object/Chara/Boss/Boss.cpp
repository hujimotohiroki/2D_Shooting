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
	Pos = { 800,0 };
	HP = 100;
	MaxHP = HP;
	Damage = 50;
	Size = 4.0f;	
	Radius = 64.0f;
	HitRadius = 16.0f;
	HitDiff = { 0,0 };
	Timer = 0;
	Flag = 0;
	wall = 0;
	wallFlag = false;
	Tex.Load("Texture/Player/player.png");
	m_hpBarFrameTex.Load("Texture/UI/hp bar/1.png");
	m_hpBarTex.Load("Texture/UI/hp bar/5.png");
	m_objType = ObjectType::Boss;

	mahouzinTex.Load("Texture/magic circle.png");
	mahouzinSize = 1.0f;
	mahouzinTimer = 0;
	mahouzinFlag = false;
	mahouzinPos = { 0,0 };
}

void C_Boss::Update()
{
	if (Flag == 1) {
		wall = m_owner->GetWall();
		if (Timer > 240 && wallFlag == false && mahouzinTimer > 90) {
			wall++;
			m_owner->SpawnWall(wall);
			wallFlag = true;
			mahouzinFlag = false;
			mahouzinTimer = 0;
		}
		if (Timer > 150 && wallFlag == false) {
			if(!mahouzinFlag)
			{
				mahouzinPos = { 0,0 };
				mahouzinSize = 1.0f;
				mahouzinTimer = 0;
				mahouzinFlag = true;
			}
			mahouzinSize *= 1.02f;
			if (mahouzinSize > 2.5f) mahouzinSize = 2.5f;
			mahouzinTimer++;
			mahouzinPos.x -= 3.0f;
			if (mahouzinPos.x < -200.0f)mahouzinPos.x = -200.0f;
		}
		m_owner->SetWall(wall);
		if(wall!=0){
			if (Timer - PrevEnemy1 >= 100 / wall) {
				m_owner->SummonEnemy(3, 1);
				PrevEnemy1 = Timer - (rand() % 3);
			}
			if (Timer - PrevEnemy2 >= 100 / wall) {
				m_owner->SummonEnemy(3, 2);
				PrevEnemy2 = Timer - (rand() % 3);
			}
			if (wall > 2) {
				if (Timer - PrevEnemy3 >= 3000) {
					m_owner->SummonEnemy(20, 3);
					PrevEnemy3 = Timer - (rand() % 3);
				}
			}
		}
		//Angle++;
		//if (Angle >= 360) Angle -= 360;
		Clean = 1.0f;
		Pos.x -= 2.0f;
		if (Pos.x < 500)Pos.x = 500;
		bool tmp=false;
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
			if (obj->GetObjType() == ObjectType::Wall) tmp = true;
		}
		if (!tmp) {
			wallFlag = false;
			if(Timer>150)mahouzinFlag = true;
		}
		Timer++;
	}
	if (Flag == -1) {
		Speed.y -= 1;
		Pos += Speed;
		if (Pos.y < -392)
		{
			Flag = 0;
			m_owner->SetBossFlag(false);
		}
	}
	Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x, (int)(Pos.y), 0);
	Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
	Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
	Mat = scale * rotate * trans;
	trans = Math::Matrix::CreateTranslation(Pos.x+mahouzinPos.x, (int)(Pos.y+mahouzinPos.y), 0);
	scale = Math::Matrix::CreateScale(mahouzinSize, mahouzinSize, 0);
	rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(Timer*3));
	mahouzinMat= scale * rotate * trans;
}

void C_Boss::Draw()
{
	if (mahouzinFlag) {
		SHADER.m_spriteShader.SetMatrix(mahouzinMat);
		SHADER.m_spriteShader.DrawTex(&mahouzinTex, Math::Rectangle{ 0, 0, 64, 64 }, Clean);
	}
	if(Flag){
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 0, 0, 32, 32 }, Clean);
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
	Flag = -1;
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