#pragma once
#include"../CharaBase.h"
class C_CharaBase;

class C_Boss :public C_CharaBase {
private:
	void Release();
public:

	C_Boss();
	~C_Boss();
	void Init();
	void Update();
	void Draw();
	void Reset();
};