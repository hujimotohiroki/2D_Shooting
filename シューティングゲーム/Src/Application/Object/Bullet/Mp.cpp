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
	MoveSpeed = 3.0f;
	Size = 1.0f;
	Radius = 8.0f;
	HitRadius = 8.0f;
	HitDiff = { 0,0 };
	Flag = 1;
	HP = 1;
	Damage = 0;
	Timer = 0;
	Angle = 0;
	Tex.Load("Texture/bullet/Bullet 24x24 Free Part 4B.png");
	m_objType = ObjectType::Mp;
}

void C_Mp::Update()
{
	if (Flag) {
		Pos+=Speed*MoveSpeed;
		Timer++;
		if (abs(Pos.x) > 708) Flag = 0;
		for (auto& obj : m_owner->GetObjList()) {
			if (obj->GetObjType() == ObjectType::Player) {
				Math::Vector2 v;
				v = obj->GetPos() - Pos;
				if (v.Length() > HitRadius + obj->GetHitRadius() && v.Length() < HitRadius + obj->GetRadius()*5) {
					Near(obj->GetPos(),v.Length());
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
		Anim = Timer % 8;
		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&Tex, Math::Rectangle{ 24*Anim, 0, 24, 24 }, 1.0f);
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

void C_Mp::Near(Math::Vector2 PlayerPos,int length)
{
	Math::Vector2 mpMove = PlayerPos - Pos;
	//enemyMove.Length();
	mpMove.Normalize();
	Pos += mpMove * (200/length);
}
