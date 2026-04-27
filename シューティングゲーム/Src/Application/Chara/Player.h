#pragma once
#include "CharaBase.h"
class C_CharaBase;
class C_MyBullet;


class C_Player : public C_CharaBase  {
private:
	std::shared_ptr<C_MyBullet> mybullet;
	void Release();
	float mp;
	
public:

	C_Player();
	~C_Player();
	void Init();
	void Update();
	void Draw();
	void Reset();

	
};