#include "MasterGame.h"

void MasterGame::Initilize()
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



	// スプライト共通テクスチャ読み込み
	spriteCommon->LoadTexture(0, L"Resources/Gorushi.png");
	spriteCommon->LoadTexture(1, L"Resources/Gorushi.png");



	// スプライトの生成
	for (int i = 0; i < 1; i++)
	{
		int texNumber = rand() % 2;
		Sprite *sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

		// スプライトの座標変更
		sprite->SetPosition({ (float)(rand() % 1280),(float)(rand() % 720),0 });
		//sprite->SetRotation((float)(rand() % 360));
		sprite->SetSize({ (float)(rand() % 400) ,(float)(rand() % 100) });


		// 頂点バッファに反映
		sprite->TransferVertexBuffer();

		sprites.push_back(sprite);
		sprite->SetPosition({ 500,300,0 });
	}



	int counter = 0; // アニメーションの経過時間カウンター

}

void MasterGame::Update()
{

	//Windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		//ゲームを抜ける
		endFlag = true;
		return;
	}

	// DirectX毎フレーム処理　ここから
	//3dオブジェクト更新
	object3d->Update();
	for (auto &sprite : sprites) {
		sprite->Update();
	}

	input->Update();

	// 座標操作
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		//if (input->PushKey(DIK_UP)) { object3d->SetPosition(1); }
		//else if (input->PushKey(DIK_DOWN)) { object3ds[0].position.y -= 1.0f; }
		//if (input->PushKey(DIK_RIGHT)) { object3ds[0].position.x += 1.0f; }
		//else if (input->PushKey(DIK_LEFT)) { object3ds[0].position.x -= 1.0f; }
	}


	//if (input->PushKey(DIK_D) || input->PushKey(DIK_A))
	//{
	//	if (input->PushKey(DIK_D)) { angle += XMConvertToRadians(1.0f); }
	//	else if (input->PushKey(DIK_A)) { angle -= XMConvertToRadians(1.0f); }

	//	// angleラジアンだけY軸まわりに回転。半径は-100
	//	eye.x = -100 * sinf(angle);
	//	eye.z = -100 * cosf(angle);
	//	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
	//}


 //  // X座標,Y座標を指定して表示
	////debugText->Print("Hello,DirectX!!", 200, 100);
	//// X座標,Y座標,縮尺を指定して表示
	//debugText->Print("debugText", 200, 200, 2.0f);

	//// GPU上のバッファに対応した仮想メモリを取得
	//Vertex *vertMap = nullptr;
	//result = vertBuff->Map(0, nullptr, (void **)&vertMap);
	//// 全頂点に対して
	//for (int i = 0; i < _countof(vertices); i++)
	//{
	//	vertMap[i] = vertices[i];   // 座標をコピー
	//}
	//// マップを解除
	//vertBuff->Unmap(0, nullptr);

	// DirectX毎フレーム処理　ここまで

}

void MasterGame::Draw()
{
	dxCommon->PreDraw();

	//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	//3dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCmdList());
	//3dオブジェクトの描画
	object3d->Draw();

	//3dオブジェクト描画後処理
	Object3d::PostDraw();

	//スプライト共通コマンド
	spriteCommon->PreDraw();
	//スプライト描画
	for (auto &sprite : sprites) {
		sprite->Draw();
	}
	//デバックテキスト
	debugText->DrawAll();

	// 描画コマンドここまで
	dxCommon->PostDraw();
}

void MasterGame::Finalize()
{
	//3Dオブジェクト解放
	delete object3d;
	//3Dモデルを解放
	delete model;
	//デバッグテキスト解放
	debugText->Finalize();
	delete debugText;
	//スプライトクラス解放
	delete spriteCommon;
	for (auto &sprite : sprites) {
		delete sprite;
	}
	sprites.clear();
	//オーディオクラス開放
	audio->Finalize();
	delete audio;


	//WindowsAPIの終了処理
	winApp->Finalize();
	//DirectX解放
	delete dxCommon;
	//WindowsAPIの解放
	delete winApp;
	//入力解放
	delete input;
}
