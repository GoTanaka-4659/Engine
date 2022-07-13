#include "Framework.h"

void Framework::Initilize()
{

	//WinAppの初期化
	winApp = new WinApp();
	winApp->Initilize();


	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化
	input = new Input();
	input->Initilize(winApp);

	//スプライト
	spriteCommon = new SpriteCommon();
	spriteCommon->Initilize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->Window_width, winApp->Window_height);

	// デバッグテキスト
	debugText = new DebugText();
	// デバッグテキスト用のテクスチャ番号を指定
	const int debugTextTexNumber = 2;
	// デバッグテキスト用のテクスチャ読み込み
	spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText->Initialize(spriteCommon, debugTextTexNumber);

	//オーディオの初期化
	audio = new Audio();
	audio->Initilize();
	// 音声読み込み
	audio->LoadWave("Resources/Alarm01.wav");
	// 音声再生
	audio->PlayWave("Resources/Alarm01.wav");

	//OBJからモデルデータを読み込む
	model = Model::LoadFromOBJ(dxCommon->GetDev());
	// 3Dオブジェクトの数
	const int OBJECT_NUM = 2;
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::Window_width, WinApp::Window_height);
	//3Dオブジェクト生成
	object3d = Object3d::Create();
	//オブジェクトにモデルを紐づけ
	object3d->SetModel(model);
	object3d->SetPosition({ 100,-10,0 });
}

void Framework::Finalize()
{
	//デバッグテキスト解放
	debugText->Finalize();
	delete debugText;
	//スプライトクラス解放
	delete spriteCommon;

	//オーディオクラス開放
	audio->Finalize();
	delete audio;
	//DirectX解放
	delete dxCommon;
	//WindowsAPIの終了処理
	winApp->Finalize();
	//WindowsAPIの解放
	delete winApp;
	//入力解放
	delete input;

}

void Framework::Update()
{
	//Windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		//ゲームを抜ける
		endFlag = true;
		return;
	}
	//入力更新
	input->Update();
	//3dオブジェクト更新
	object3d->Update();
}

void Framework::Run()
{
	Initilize();

	while (true)  // ゲームループ
	{
		Update();
		if (endFlag) {
			break;
		}
		Draw();
	}
	//ゲームの終了
	Finalize();
}
