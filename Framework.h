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
	//�|�C���^�u����
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
	//�J�n
	virtual void Initilize();
	//�I��
	virtual void Finalize();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw() = 0;
	//
	void Run();
};

