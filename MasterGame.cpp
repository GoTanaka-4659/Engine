#include "MasterGame.h"

void MasterGame::Initilize()
{
	//基底クラスの初期化
	Framework::Initilize();

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
	//基底クラスの更新
	Framework::Update();

	// DirectX毎フレーム処理　ここから
	//3dオブジェクト更新
	//object3d->Update();
	for (auto &sprite : sprites) {
		sprite->Update();
	}

	// 座標操作
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{

	}


	
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
	//スプライト個別開放
	for (auto &sprite : sprites) {
		delete sprite;
	}
	sprites.clear();
	
	//3Dオブジェクト解放
	delete object3d;
	//3Dモデルを解放
	delete model;

	//基底クラスの終了処理
	Framework::Finalize();
}
