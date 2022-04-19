#include <Windows.h>
#include "DirectXTex.h"

#include <vector>
#include <string>
#include <fstream>


#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Debugtext.h"

using namespace DirectX;
using namespace Microsoft::WRL;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#pragma region WindowsAPI初期化

	//MSG msg{};  // メッセージ
#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理


	HRESULT result;

	//ポインタ置き場
	WinApp *winApp = nullptr;
	Input *input = nullptr;
	DirectXCommon *dxCommon = nullptr;
	SpriteCommon *spriteCommon = nullptr;

	DebugText *debugText = nullptr;

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

	// DirectX初期化処理　ここまで
#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理


	// 頂点データ構造体
	struct Vertex
	{
		XMFLOAT3 pos;       // xyz座標
		XMFLOAT3 normal;    // 法線ベクトル
		XMFLOAT2 uv;        // uv座標
	};

	const float topHeight = 10.0f;   // 天井の高さ
	const float radius = 10.0f;
	const int DIV = 3;

	Vertex vertices[DIV + 1 + 1] = {};

	vertices[0].pos.x = radius * sinf(XM_2PI * 0 / DIV); vertices[0].pos.y = radius * cosf(XM_2PI * 0 / DIV); vertices[0].pos.z = 0.0f;
	vertices[1].pos.x = radius * sinf(XM_2PI * 1 / DIV); vertices[1].pos.y = radius * cosf(XM_2PI * 1 / DIV); vertices[1].pos.z = 0.0f;
	vertices[2].pos.x = radius * sinf(XM_2PI * 2 / DIV); vertices[2].pos.y = radius * cosf(XM_2PI * 2 / DIV); vertices[2].pos.z = 0.0f;
	vertices[3].pos = { 0,0,0 };
	vertices[4].pos = { 0,0,-topHeight };

	// インデックスデータ
	unsigned short indices[3 * DIV * 2];

	indices[0] = 1;
	indices[1] = 0;
	indices[2] = 3;

	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;

	indices[6] = 0;
	indices[7] = 2;
	indices[8] = 3;

	indices[9] = 0;
	indices[10] = 1;
	indices[11] = 4;

	indices[12] = 1;
	indices[13] = 2;
	indices[14] = 4;

	indices[15] = 2;
	indices[16] = 0;
	indices[17] = 4;

	for (int i = 0; i < _countof(indices) / 3; i++)
	{// 三角形１つごとに計算していく
		// 三角形のインデックスを取り出して、一時的な変数に入れる
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];
		// 三角形を構成する頂点座標をベクトルに代入
		XMVECTOR p0 = XMLoadFloat3(&vertices[index0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[index1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[index2].pos);
		// p0→p1ベクトル、p0→p2ベクトルを計算　（ベクトルの減算）
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);
		// 外積は両方から垂直なベクトル
		XMVECTOR normal = XMVector3Cross(v1, v2);
		// 正規化（長さを1にする)
		normal = XMVector3Normalize(normal);
		// 求めた法線を頂点データに代入
		XMStoreFloat3(&vertices[index0].normal, normal);
		XMStoreFloat3(&vertices[index1].normal, normal);
		XMStoreFloat3(&vertices[index2].normal, normal);
	}

	// 頂点バッファのサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * _countof(vertices));

	// 頂点バッファの生成
	ComPtr<ID3D12Resource> vertBuff;
	result = dxCommon->GetDev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),   // アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));

	// GPU上のバッファに対応した仮想メモリを取得
	Vertex *vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void **)&vertMap);
	// 全頂点に対して
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];   // 座標をコピー
	}
	// マップを解除
	vertBuff->Unmap(0, nullptr);

	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(Vertex);

	// インデックスデータ全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * _countof(indices));

	// インデックスバッファの生成
	ComPtr<ID3D12Resource> indexBuff;
	result = dxCommon->GetDev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),   // アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));

	// インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

	// GPU上のバッファに対応した仮想メモリを取得
	unsigned short *indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void **)&indexMap);

	// 全インデックスに対して
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];   // インデックスをコピー
	}
	// 繋がりを解除
	indexBuff->Unmap(0, nullptr);

	//// 射影変換行列(並行投影)
	//XMMATRIX matProjection = XMMatrixOrthographicOffCenterLH(
	//    0, window_width,
	//    window_height, 0,
	//    0, 1000.0f
	//);

	// 射影変換行列(透視投影)
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),              // 画角60度
		(float)WinApp::Window_width / WinApp::Window_height,    // アスペクト比（画面横幅/画面縦幅）
		0.1f, 1000.0f                           // 前端、奥端
	);

	// ビュー変換行列
	XMMATRIX matView;
	XMFLOAT3 eye(0, 0, -100);   // 視点座標
	XMFLOAT3 target(0, 0, 0);   // 注視点座標
	XMFLOAT3 up(0, 1, 0);       // 上方向ベクトル
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	float angle = 0.0f; // カメラの回転角    

	const int constantBufferNum = 128; // 定数バッファの最大数

	// 定数バッファ用デスクリプタヒープの生成
	ComPtr<ID3D12DescriptorHeap> basicDescHeap = nullptr;
	// 設定構造体
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // シェーダーから見える
	descHeapDesc.NumDescriptors = constantBufferNum + 1;
	// 生成
	result = dxCommon->GetDev()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&basicDescHeap));



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



	// スプライト共通テクスチャ読み込み
	spriteCommon->LoadTexture(0, L"Resources/Gorushi.png");
	spriteCommon->LoadTexture(1, L"Resources/Gorushi.png");

	std::vector<Sprite *>sprites;

	// スプライトの生成
	/*for (int i = 0; i < 1; i++)
	{*/
	int texNumber = rand() % 2;
	Sprite *sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

	// スプライトの座標変更
	sprite->SetPosition({ (float)(rand() % 1280),(float)(rand() % 720),0 });
	//sprite->SetRotation((float)(rand() % 360));
	sprite->SetSize({ (float)(rand() % 400) ,(float)(rand() % 100) });


	// 頂点バッファに反映
	sprite->TransferVertexBuffer();

	sprites.push_back(sprite);
	sprite->SetPosition({ 0,650,0 });
	//}




#pragma endregion 描画初期化処理

	int counter = 0; // アニメーションの経過時間カウンター

	//座標
	float x = 0, y = 650;
	//初速度
	float v0 = 0;
	float vy = 0;
	float vx = v0;
	//重力
	float g = 9.8f / 60;
	float t = 1;

	float time = 0.001;
	bool Flag = false;
	while (true)  // ゲームループ
	{
#pragma region ウィンドウメッセージ処理

		//Windowsのメッセージ処理
		if (winApp->ProcessMessage()) {
			//ゲームを抜ける
			break;
		}
		if (input->PushKey(DIK_ESCAPE)) {
			break;
		}
#pragma endregion ウィンドウメッセージ処理

#pragma region DirectX毎フレーム処理
		// DirectX毎フレーム処理　ここから
		//3dオブジェクト更新
		object3d->Update();
		for (auto &sprite : sprites) {
			sprite->Update();
		}

		input->Update();

		// 座標操作

		if (input->PushKey(DIK_R))
		{
			Flag = false;
			x = 000;
			y = 650;
			v0 = 5;
			vy = 0;
			vx = v0;
			t = 1;
		}

		if (input->PushKey(DIK_SPACE))
		{
			Flag = true;
		}

		if (Flag == true) {
			vy += g;
			//x += vx;
		}
		y -= vy;
		sprite->SetPosition({ x,y,0 });


		// X座標,Y座標を指定して表示
		 //debugText->Print("Hello,DirectX!!", 200, 100);
		 // X座標,Y座標,縮尺を指定して表示
		debugText->Print("Space = demo  R = Reset", 0, 0, 2.0f);

		// GPU上のバッファに対応した仮想メモリを取得
		Vertex *vertMap = nullptr;
		result = vertBuff->Map(0, nullptr, (void **)&vertMap);
		// 全頂点に対して
		for (int i = 0; i < _countof(vertices); i++)
		{
			vertMap[i] = vertices[i];   // 座標をコピー
		}
		// マップを解除
		vertBuff->Unmap(0, nullptr);

		// DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド
		dxCommon->PreDraw();

		//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

		//3dオブジェクト描画前処理
		Object3d::PreDraw(dxCommon->GetCmdList());
		//3dオブジェクトの描画
		//object3d->Draw();

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
#pragma region WindowsAPI後始末

	//WindowsAPIの終了処理
	winApp->Finalize();
	//DirectX解放
	delete dxCommon;
	//WindowsAPIの解放
	delete winApp;
	//入力解放
	delete input;

#pragma endregion WindowsAPI後始末


	return 0;
}