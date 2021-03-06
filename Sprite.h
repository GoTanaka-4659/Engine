#pragma once
#include <wrl.h>
#include <DirectXMath.h>
#include <d3d12.h>
#include "SpriteCommon.h"

class Sprite
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	// 頂点データ
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData {
		XMFLOAT4 color; // 色 (RGBA)
		XMMATRIX mat;   // ３Ｄ変換行列
	};

public:
	static Sprite*Create(SpriteCommon *spriteCommon, UINT texNum, XMFLOAT2 anchorpoint = { 0.5f,0.5f }, bool isFlipX = false, bool isFlipY = false);

	void Initialize(SpriteCommon *spritecommon, UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	///頂点バッファの転送
	void TransferVertexBuffer();
	//描画
	void Draw();

	void Update();

	void SetPosition(const XMFLOAT3 &position) { position_ = position; }
	void SetRotation(float rotation) { rotation_ = rotation; }
	void SetSize(const DirectX::XMFLOAT2 &size) { size_ = size; }
	void SetTexLeftTop(const DirectX::XMFLOAT2 &texLeftTop) { texLeftTop_ = texLeftTop; }
	void SetTexSize(const DirectX::XMFLOAT2 &texSize) { texSize_ = texSize; }
private:
	//スプライト共通部分
	SpriteCommon *spritecommon_ = nullptr;
	//頂点バッファ;
	ComPtr<ID3D12Resource> vertBuff_;
	//頂点バッファビュー;
	D3D12_VERTEX_BUFFER_VIEW vbView_{};
	//定数バッファ;
	ComPtr<ID3D12Resource> constBuff_;
	// Z軸回りの回転角
	float rotation_ = 0.0f;
	// 座標
	XMFLOAT3 position_ = { 0,0,0 };
	// ワールド行列
	XMMATRIX matWorld_;
	// 色(RGBA)
	XMFLOAT4 color_ = { 1, 1, 1, 1 };
	// テクスチャ番号
	UINT texNumber_ = 0;
	// 大きさ
	XMFLOAT2 size_ = { 100, 100 };
	// アンカーポイント
	XMFLOAT2 anchorpoint_ = { 0.5f, 0.5f };
	// 左右反転
	bool isFlipX_ = false;
	// 上下反転
	bool isFlipY_ = false;
	// テクスチャ左上座標
	XMFLOAT2 texLeftTop_ = { 0, 0 };
	// テクスチャ切り出しサイズ
	XMFLOAT2 texSize_ = { 100, 100 };
	// 非表示
	bool isInvisible_ = false;
};

