#pragma once
#include "CharaBase.h"
class C_CharaBase;

class C_Player : public C_CharaBase  {
private:
	void Release();
public:

	C_Player();
	~C_Player();
	void Init();
	void Update();
	void Draw();
	void Reset();
};