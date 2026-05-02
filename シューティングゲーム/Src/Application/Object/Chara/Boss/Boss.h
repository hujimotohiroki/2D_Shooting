#pragma once
#include"../../ObjectBase.h"
class C_ObjectBase;
class C_Boss :public C_ObjectBase {
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