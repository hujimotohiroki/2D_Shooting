#pragma once

#include "../BaseScene.h"

class C_TitleScene :public C_BaseScene {
private:
	KdTexture backTex1;
	KdTexture backTex2;
	KdTexture farTex1;
	KdTexture farTex2;
	KdTexture titleTex;
	Math::Matrix backMat1;
	float backX1;
	Math::Matrix backMat2;
	float backX2;
	Math::Matrix farMat1;
	float farX1;
	Math::Matrix farMat2;
	float farX2;
	Math::Matrix titleMat;
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