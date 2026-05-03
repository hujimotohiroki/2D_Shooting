#include "Mp.h"
#include "../../Scene/Game/GameScene.h"

void C_Mp::Release()
{}

C_Mp::C_Mp()
{}

C_Mp::~C_Mp()
{}

void C_Mp::Init()
{
	Pos = { 0,0 };
	Speed = { 0,0 };
	Size = 1.0f;
	Radius = 8.0f;
	HitRadius = 8.0f;
	HitDiff = { 0,0 };
	Flag = 1;
	HP = 1;
	Damage = 0;
	Timer = 0;
	Angle = 0;
	Tex.Load("Texture/bullet.png");
	m_objType = ObjectType::Mp;
}

void C_Mp::Update()
{
	if (Flag) {
		Pos.x -= 5;
		Timer++;
		if (abs(Pos.x) > 700) Flag = 0;
		for (auto& obj : m_owner->GetObjList()) {
			if (obj->GetObjType() == ObjectType::Player) {
				Math::Vector2 v;
				v = obj->GetPos() - Pos;
				if (v.Length() > HitRadius + obj->GetHitRadius() && v.Length() < HitRadius + obj->GetRadius()) {
					Near(obj->GetPos());
				}
			}
		}
		Math::Matrix trans = Math::Matrix::CreateTranslation(Pos.x, (int)(Pos.y), 0);
		Math::Matrix scale = Math::Matrix::CreateScale(Size, Size, 0);
		Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(Angle));
		Mat = scale * rotate * trans;
	}
}

void C_Mp::Draw()
{
	if (Flag) {
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 0, 0, 16, 16 }, 1.0f);
	}
}

void C_Mp::Reset()
{}

void C_Mp::Hit(int damage)
{
	HP -= damage;
	if(HP<0)
	{
		
		Flag = 0;
	}
}

void C_Mp::Near(Math::Vector2 PlayerPos)
{
	Math::Vector2 mpMove = PlayerPos - Pos;
	//enemyMove.Length();
	mpMove.Normalize();
	Pos += mpMove * 3;
}
