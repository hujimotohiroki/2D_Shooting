#pragma once
#include "../../ObjectBase.h"
class C_ObjectBase;
class C_MyBullet;


class C_Player : public C_ObjectBase  {
private:
	std::shared_ptr<C_MyBullet> m_mybullet;
	void Release() override;
	int Mp;
	int MaxMP;
	int Lv;
	const int MaxLV=10;
	KdTexture m_hpBarFrameTex;
	KdTexture m_hpBarTex;
	KdTexture m_mpBarFrameTex;
	KdTexture m_mpBarTex;
public:

	C_Player();
	~C_Player()override;
	void Init()override;
	void Update()override;
	void Draw()override;
	void Reset()override;

	void Hit(int damage)override;
	void Dead();
	void AddMp() { if (Mp < MaxMP)Mp++; }

	void DrawHpBar();
	void DrawMpBar();
};