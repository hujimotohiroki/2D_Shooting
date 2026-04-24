#include "main.h"
#include "Scene.h"
#include "time.h"
#include "シーンについて/GameScene.h"
#define rep(i,N) for(int i=0;i<N;i++)
//プログラムを打つときは半角英数字で
//コメントを打つ時は行の頭にスラッシュ２つ
//1秒間に60回実行される(60FPSの場合)
void Scene::Draw2D()
{
	m_NowScene->Draw2D();
}
//1秒間に60回実行される(60FPSの場合)
void Scene::Update()
{
	m_NowScene->Update();
}
//ゲーム開始時のみ実行される
void Scene::Init()
{
	m_NowScene = std::make_shared<C_GameScene>();
	m_NowScene->Init();
	scene = Title;
}
//ゲーム終了時のみ実行される
void Scene::Release()
{
	
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
