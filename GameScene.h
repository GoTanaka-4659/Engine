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
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private://静的メンバ変数

public://メンバ関数
	GameScene();

	void Initilize(DirectXCommon *dxCommon, Input *input, Audio *audio);

	void Update();
	void Draw();
private://メンバ変数
	DirectXCommon *dxCommmon = nullptr;
	Input *input = nullptr;
	Audio *audio = nullptr;
	DebugText *debugText=nullptr;
	SpriteCommon *spriteCommon = nullptr;


	
};

