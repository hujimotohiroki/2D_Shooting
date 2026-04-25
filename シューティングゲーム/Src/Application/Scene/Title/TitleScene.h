#pragma once

#include "../BaseScene.h"

class C_TitleScene :public C_BaseScene {
private:

public:
	C_TitleScene() { Init(); }
	~C_TitleScene();
	// 初期設定
	void Init() override;

	// 解放
	void Release()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;
};