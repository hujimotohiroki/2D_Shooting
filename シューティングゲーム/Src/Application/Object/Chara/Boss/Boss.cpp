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
	Pos.x = 0;
	Pos.y = 456;
	HP = 100;
	MaxHP = HP;
	Damage = 10;
	Size = 3;	
	Radius = 96;
	Timer = 0;
	Flag = 1;
	Tex.Load("Texture/enemy.png");
	m_objType = ObjectType::Boss;
}

void C_Boss::Update()
{
	if (Flag == 1) {
		//Angle++;
		//if (Angle >= 360) Angle -= 360;
		Pos.y -= 0.5f;
		if (Pos.y < 0)Pos.y = 0;
		//rep(bu, mybulletnum) {
		//	if (mybulletFlag[bu] == 1) {
		//		if (IS_HIT(Pos.x, Pos.y, mybulletPos.x[bu], mybulletPos.y[bu], Radius + mybulletRadius[bu])) {
		//			mybulletFlag[bu] = 0;
		//			Explosion(mybulletPos.x[bu], mybulletPos.y[bu]);
		//			HP--;
		//			if (HP <= 0) {
		//				Flag++;
		//				score += 10000;
		//			}
		//			mybulletPos.y[bu] = 456;
		//		}
		//	}
		//}
		for (auto& obj : m_owner->GetObjList()) {
			ObjectType type = obj->GetObjType();
			if (type == ObjectType::MyBullet) {
				Math::Vector2 v;
				v = obj->GetPos() - Pos;
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
	SHADER.m_spriteShader.SetMatrix(Mat);
	SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 0,0, 64, 64 }, 1.0f);
}

void C_Boss::Reset()
{
	Flag = 0;
	Pos.x = 0;
	Pos.y = 456;
	HP = 100;
}
