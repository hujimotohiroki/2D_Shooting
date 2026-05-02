#pragma once
#include"../../ObjectBase.h"
class C_ObjectBase;
class C_Boss :public C_ObjectBase {
private:
	void Release()override;
public:

	C_Boss();
	~C_Boss()override;
	void Init()override;
	void Update()override;
	void Draw()override;
	void Reset()override;
};