#pragma once
#include"../../ObjectBase.h"
class C_ObjectBase;
class C_Wall :public C_ObjectBase {
private:
	void Release()override;
	Math::Matrix WallCoreMat;
	KdTexture m_hpBarFrameTex;
	KdTexture m_hpBarTex;
	KdTexture WallCoreTex;
public:

	C_Wall();
	~C_Wall()override;
	void Init()override;
	void Update()override;
	void Draw()override;
	void Reset()override;

	void Hit(int damage)override;
	void Dead();

	void DrawHpBar();
};