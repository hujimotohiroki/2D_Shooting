#pragma once
class C_BaseScene {
public:
	C_BaseScene() { Init(); }//授業ではInit呼び出す
	virtual ~C_BaseScene() {}

	//virtual 上書き前提関数
	//virtual void Init() = 0 絶対に上書きする
	virtual void Init();
	virtual void Update();
	virtual void Draw2D();
	virtual void Release();
private:

};