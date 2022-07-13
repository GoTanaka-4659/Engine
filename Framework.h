#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Debugtext.h"
#include "Audio.h"

class Framework
{
protected: 
	bool endFlag = false;
	//ポインタ置き場
	WinApp *winApp = nullptr;
	Input *input = nullptr;
	DirectXCommon *dxCommon = nullptr;
	SpriteCommon *spriteCommon = nullptr;
	Audio *audio = nullptr;
	DebugText *debugText = nullptr;

	Model *model = nullptr;
	Object3d *object3d = nullptr;

public: 
	bool GetendFlag() { return endFlag; }
	//開始
	virtual void Initilize();
	//終了
	virtual void Finalize();
	//更新
	virtual void Update();
	//描画
	virtual void Draw() = 0;
	//
	void Run();
};

