#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Debugtext.h"
#include "Audio.h"

#include <vector>

class MasterGame
{
private:
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

	std::vector<Sprite *>sprites;
public:
	void Initilize();
	void Update();
	void Draw();
	void Finalize();
	bool GetendFlag() { return endFlag; }
};
