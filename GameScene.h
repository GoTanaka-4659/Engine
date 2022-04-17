#pragma once
#include "DirectXTex.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Debugtext.h"
#include "Audio.h"

class GameScene
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private://�ÓI�����o�ϐ�

public://�����o�֐�
	GameScene();

	void Initilize(DirectXCommon *dxCommon, Input *input, Audio *audio);

	void Update();
	void Draw();
private://�����o�ϐ�
	DirectXCommon *dxCommmon = nullptr;
	Input *input = nullptr;
	Audio *audio = nullptr;
	DebugText *debugText=nullptr;
	SpriteCommon *spriteCommon = nullptr;


	
};

