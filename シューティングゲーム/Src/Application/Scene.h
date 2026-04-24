#pragma once

//#include "SceneChange.h"

enum SceneType {
	Title,Game,Result,Pause,None
};
class Scene
{
private:

	static const int ScrWidth = 1280;
	static const int ScrHeight = 720;
	SceneType scene;

public:

	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

	// GUIˆ—
	void ImGuiUpdate();


private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
