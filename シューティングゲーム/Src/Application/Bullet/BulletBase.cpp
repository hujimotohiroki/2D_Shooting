#include "BulletBase.h"

C_BulletBase::C_BulletBase()
{}

void C_BulletBase::Init()
{}

void C_BulletBase::Update()
{}

void C_BulletBase::Draw()
{}

void C_BulletBase::Shot(Math::Vector2 playerPos, int flag)
{
	Pos = playerPos;
	Flag = flag;
	Timer = 0;
}

void C_BulletBase::Release()
{}
