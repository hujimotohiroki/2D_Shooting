#pragma once
#include "../ObjectBase.h"
class C_ObjectBase;
class C_GameScene;
class C_Mp :public C_ObjectBase {
private:
	C_GameScene* m_owner;
	void Release();
public:

	C_Mp();
	~C_Mp();
	void Init();
	void Update();
	void Draw();
	void Reset();

	void Hit();
	void Near(Math::Vector2 PlayerPos);
	void SetOwner(C_GameScene* owner) { m_owner = owner; }
};