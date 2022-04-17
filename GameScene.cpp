#include "GameScene.h"

GameScene::GameScene()
{
}

void GameScene::Initilize(DirectXCommon *dxCommon, Input *input, Audio *audio)
{
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommmon = dxCommon;
	this->input = input;
	this->audio = audio;

	// デバッグテキスト
	
	// デバッグテキスト用のテクスチャ番号を指定
	const int debugTextTexNumber = 2;
	// デバッグテキスト用のテクスチャ読み込み
	spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText->Initialize(spriteCommon, debugTextTexNumber);

	// スプライト共通テクスチャ読み込み
	spriteCommon->LoadTexture(0, L"Resources/texture.png");
	spriteCommon->LoadTexture(1, L"Resources/house.png");
	//OBJからモデルデータを読み込む
	Model *model = Model::LoadFromOBJ(dxCommon->GetDev());
	// 3Dオブジェクトの数
	const int OBJECT_NUM = 2;
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::Window_width, WinApp::Window_height);
	//3Dオブジェクト生成
	Object3d *object3d = Object3d::Create();
	//オブジェクトにモデルを紐づけ
	object3d->SetModel(model);
	object3d->SetPosition({ 100,-10,0 });

}

void GameScene::Update()
{
}

void GameScene::Draw()
{
}
