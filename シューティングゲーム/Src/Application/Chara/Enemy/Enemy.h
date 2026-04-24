#pragma once
#include"../CharaBase.h"
class C_CharaBase;

class C_Enemy :public C_CharaBase {
private:
	void Release();
public:

	C_Enemy();
	~C_Enemy();
	void Init();
	void Update();
	void Draw();
	void Reset();
};