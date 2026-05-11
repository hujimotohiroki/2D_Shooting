#include"Player.h"
#include"../../../Scene/Game/GameScene.h"
#include"../../Bullet/MyBullet.h"
#include "../../Bullet/Mp.h"
#define rep(i,N) for(int i=0;i<N;i++)
void C_Player::Release()
{}
C_Player::C_Player()
{}

C_Player::~C_Player()
{}

void C_Player::Init()
{
	Pos = { -500,0 };
	MoveSpeed = 10.0f;
	Speed = { 0,0 };
	Flag = 1;
	Anim = 0;
	Size = 4.0f;
	Radius = 64.0f;
	HitRadius = 4.0f;
	HitDiff = { 24,-44 };
	HP = 50;
	MaxHP = HP;
	Mp = 0;
	MaxMP = 20;
	Lv = 1;
	Damage = 5;
	Timer = -180;
	PrevShot = 0;
	PrevXKey = 0;
	Clean = 1.0f;
	Tex.Load("Texture/player.png");
	m_hpBarFrameTex.Load("Texture/UI/hp bar/1.png");
	m_hpBarTex.Load("Texture/UI/hp bar/5.png");
	m_mpBarFrameTex.Load("Texture/UI/mp bar/1.png");
	m_mpBarTex.Load("Texture/UI/mp bar/5.png");
	skillTex1.Load("Texture/UI/Skill Icon/Bigshot.png");
	skillTex2.Load("Texture/UI/Skill Icon/heal.png");
	skillTex3.Load("Texture/UI/Skill Icon/Lv up.png");
	skillTex4.Load("Texture/UI/Skill Icon/Bomb.png");
	keyTex.Load("Texture/UI/icons-keyboard-16x16-1bit-ansdor.png");
	m_skillTex.Load("Texture/UI/mp bar/skill.png");
	m_objType = ObjectType::Player;
}

void C_Player::Update()
{
	Clean = 1.0f;
	if(Flag>0&&Timer>0){
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
		if (GetAsyncKeyState('Z') & 0x8000) {
			switch(Lv)
			{
			case 1:
				if (Timer - PrevShot >= 5) {
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,0);
					PrevShot = Timer;
				}
				break;
			case 2:
				if (Timer - PrevShot >= 5) {
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,-15);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,15);
					PrevShot = Timer;
				}
				break;
			case 3:
				if (Timer - PrevShot >= 4) {
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,-30);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,0);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,30);
					PrevShot = Timer;
				}
				break;
			case 4:
				if (Timer - PrevShot >= 4) {
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,-30);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,-10);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,10);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,30);
					PrevShot = Timer;
				}
				break;
			case 5:
				if (Timer - PrevShot >= 3) {
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,-30);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,-15);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,0);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,15);
					m_owner->PlayerShot(Pos, Flag, 8.0f, 1, 1.0f,30);
					PrevShot = Timer;
				}
				break;
			}
		}
		if (GetAsyncKeyState('X') & 0x8000) {
			if (Mp >= 10&&Timer-PrevXKey>=30) {
				if (Timer - PrevShot >= 5) {
					Mp -= 15;
					m_owner->PlayerShot(Pos, Flag, 32.0f, 100, 4.0f,0);
					PrevShot = Timer;
				}
				
			}
		}
		if (GetAsyncKeyState('C') & 0x8000) {
			if (Mp >= 30) {
				Mp -= 30;
				HP += MaxHP / 3.0f;
			}
		}
		if (GetAsyncKeyState('V') & 0x8000) {
			//LvUpのプログラム
			if (Mp == MaxMP) {
				Mp = 0;
				if (Lv != MaxLV) {
					Lv++;
					MaxMP *= 1.5f; 
					MaxHP *= 1.2f;
					HP *= 1.2f;
				}
				else {
					for (auto& obj : m_owner->GetObjList()) {
						ObjectType type = obj->GetObjType();
						if (type == ObjectType::Mp) {
							Math::Vector2 v;
							v = obj->GetPos() - Pos;
							if (v.Length() < 500) {
								m_owner->PlayerShot(obj->GetPos(), 2, 8.0f, 1, 1.0f,0);
								obj->Hit(Damage);
							}
						}
					}
				}
			}
		}
		if (Pos.x > 592 + HitDiff.x) Pos.x = 592 + HitDiff.x;
		if (Pos.x < -592 + HitDiff.x)Pos.x = -592 + HitDiff.x;
		if (Pos.y > 312 + HitDiff.y)Pos.y = 312 + HitDiff.y;
		if (Pos.y < -312 + HitDiff.y)Pos.y = -312 + HitDiff.y;
		for (auto& obj : m_owner->GetObjList()) {
			ObjectType type = obj->GetObjType();
			if (type == ObjectType::Enemy || type == ObjectType::Boss || type == ObjectType::EnemyBullet || type == ObjectType::Mp) {
				Math::Vector2 v;
				v = obj->GetPos() - Pos;
				if (v.Length() < HitRadius+obj->GetHitRadius()) {
					Hit(obj->GetObjDamage());
					obj->Hit(Damage);
					if (type == ObjectType::Mp) {
						AddMp();
					}
					else {
						Clean = 0.3f;
					}
				}
			}
		}
	}
	Timer++;
	if (Flag == -1) {
		Speed.y -= 1;
		Pos += Speed;
		if (Pos.y < -392)
		{
			Flag = 0;
			m_owner->SetPlayerFlag(false);
		}
	}
	Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x-HitDiff.x, (int)(Pos.y)-HitDiff.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
	Math::Matrix rotate = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	Mat = scale * rotate * trans;
	skillMat1 = Math::Matrix::CreateTranslation(360, -300, 0);
	skillMat2 = Math::Matrix::CreateTranslation(470, -300, 0);
	skillMat3 = Math::Matrix::CreateTranslation(580, -300, 0);
	keyMat1 = Math::Matrix::CreateTranslation(360, -255, 0);
	keyMat2 = Math::Matrix::CreateTranslation(470, -255, 0);
	keyMat3 = Math::Matrix::CreateTranslation(580, -255, 0);
}

void C_Player::Draw()
{
	if(Flag!=0){
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 0,0, 32, 32 }, Clean);
		DrawHpBar();
		DrawMpBar();
	}
	
	SHADER.m_spriteShader.SetMatrix(skillMat1);
	SHADER.m_spriteShader.DrawTex(&skillTex1, Math::Rectangle{ 0, 0, 96, 96 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(keyMat1);
	SHADER.m_spriteShader.DrawTex(&keyTex, Math::Rectangle{ 128, 16, 16, 16 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(skillMat2);
	SHADER.m_spriteShader.DrawTex(&skillTex2, Math::Rectangle{ 0, 0, 96, 96 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(keyMat2);
	SHADER.m_spriteShader.DrawTex(&keyTex, Math::Rectangle{ 144, 16, 16, 16 }, 1.0f);
	if(Lv!=MaxLV)
		{
			SHADER.m_spriteShader.SetMatrix(skillMat3);
			SHADER.m_spriteShader.DrawTex(&skillTex3, Math::Rectangle{ 0, 0, 96, 96 }, 1.0f);
		}
		else
		{
			SHADER.m_spriteShader.SetMatrix(skillMat3);
			SHADER.m_spriteShader.DrawTex(&skillTex4, Math::Rectangle{ 0, 0, 96, 96 }, 1.0f);
		}
	SHADER.m_spriteShader.SetMatrix(keyMat3);
	SHADER.m_spriteShader.DrawTex(&keyTex, Math::Rectangle{ 160, 16, 16, 16 }, 1.0f);
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
	Flag = -1;
}

void C_Player::DrawHpBar()
{
	float maxWidth = 520.0f;
	float height = 20.0f;

	float rate = float(HP) / float(MaxHP);
	if (rate < 0) rate = 0;
	if (rate > 1) rate = 1;

	float x = -300;
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

		Math::Matrix mat =  moveToRight  *scale* moveBack * moveToPos;
		SHADER.m_spriteShader.SetMatrix(mat);

		Math::Rectangle src{ 0,0,520,10 };
		SHADER.m_spriteShader.DrawTex(&m_hpBarTex, src, 1.0f);
	}
}

void C_Player::DrawMpBar()
{
	float maxWidth = 310.0f;
	float height = 20.0f;

	float rate = float(Mp) / float(MaxMP);
	if (rate < 0) rate = 0;
	if (rate > 1) rate = 1;

	float x = 470;
	float y = -240;

	// =============================
	// ① フレーム描画
	// =============================
	{
		Math::Matrix scale = Math::Matrix::CreateScale(1.0f, 2.0f, 0);
		Math::Matrix trans = Math::Matrix::CreateTranslation(x, y, 0);
		Math::Matrix mat = scale * trans;
		SHADER.m_spriteShader.SetMatrix(mat);

		Math::Rectangle frameRect{ 0,0,310,10 };
		SHADER.m_spriteShader.DrawTex(&m_mpBarFrameTex, frameRect, 1.0f);
	}
	//敵が大量に来るけど相手の弾をこっちの弾で相殺出来たりする
	//パワーで頑張る
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

		Math::Rectangle src{ 0,0,310,10 };
		SHADER.m_spriteShader.DrawTex(&m_mpBarTex, src, 1.0f);


		rate = 20.0f / float(MaxMP);
		halfW = maxWidth * 0.5f;

		// 左端にアンカーを移動（中心 → 左端）
		anchorOffset = maxWidth * 0.5f;   // 中心から左端への距離

		moveToRight = Math::Matrix::CreateTranslation(anchorOffset, 0, 0);
		scale = Math::Matrix::CreateScale(rate, 2.0f, 0);
		moveBack = Math::Matrix::CreateTranslation(-anchorOffset, 0, 0);

		moveToPos = Math::Matrix::CreateTranslation(x, y, 0);

		mat = moveToRight * scale * moveBack * moveToPos;
		SHADER.m_spriteShader.SetMatrix(mat);

		src={ 0,0,1,10 };
		SHADER.m_spriteShader.DrawTex(&m_skillTex, src, 1.0f);
		
		if(MaxMP>=30.0f){
			rate = 60.0f / float(MaxMP);
			halfW = maxWidth * 0.5f;

			// 左端にアンカーを移動（中心 → 左端）
			anchorOffset = maxWidth * 0.5f;   // 中心から左端への距離

			moveToRight = Math::Matrix::CreateTranslation(anchorOffset, 0, 0);
			scale = Math::Matrix::CreateScale(rate, 2.0f, 0);
			moveBack = Math::Matrix::CreateTranslation(-anchorOffset, 0, 0);

			moveToPos = Math::Matrix::CreateTranslation(x, y, 0);

			mat = moveToRight * scale * moveBack * moveToPos;
			SHADER.m_spriteShader.SetMatrix(mat);

			src = { 0,0,1,10 };
			SHADER.m_spriteShader.DrawTex(&m_skillTex, src, 1.0f);
		}
	}
}