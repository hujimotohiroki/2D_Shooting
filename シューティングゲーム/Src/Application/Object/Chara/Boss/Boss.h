#pragma once
#include"../../ObjectBase.h"
class C_ObjectBase;
class C_Boss :public C_ObjectBase {
private:
	void Release()override;
	KdTexture m_hpBarFrameTex;
	KdTexture m_hpBarTex;
public:

	C_Boss();
	~C_Boss()override;
	void Init()override;
	void Update()override;
	void Draw()override;
	void Reset()override;

	void Hit(int damage)override;
	void Dead();

	void DrawHpBar();
};