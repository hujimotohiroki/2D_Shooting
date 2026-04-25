#include "TitleScene.h"
#include "../SceneManager.h"
C_TitleScene::~C_TitleScene()
{}

void C_TitleScene::Init()
{}

void C_TitleScene::Release()
{}

void C_TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
}

void C_TitleScene::Draw2D()
{
	
}
