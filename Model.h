#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <wrl.h>
#include "DirectXCommon.h"

//3Dモデル
class Model
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
// 頂点データ構造体
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 normal; // 法線ベクトル
		XMFLOAT2 uv;  // uv座標
	};
	//マテリアル
	struct Material
	{
		std::string name;			//マテリアル名
		XMFLOAT3 ambient;			//アンビエント影響度
		XMFLOAT3 diffuse;			//ディフューズ影響度
		XMFLOAT3 specular;			//スペキュラー影響度
		float alpha;				//アルファ
		std::string textureFilename;//テクスチャファイル名
		//コンストラクタ
		Material()
		{
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};

	//定数バッファ用データ構造体B1
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient;	//アンビエント係数
		float pad1;			//パディング
		XMFLOAT3 diffuse;	//ディフューズ係数
		float pad2;			//パディング
		XMFLOAT3 specular;	//スペキュラー係数
		float alpha;		//アルファ
	};

public://静的メンバ関数
	//OBJファイルから3dモデルを読み込む
	static Model *LoadFromOBJ(ID3D12Device *device);

	static void StaticInitilize(ID3D12Device *device);

private://静的メンバ変数
	//デバイス
	static ID3D12Device *device;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	//マテリアル
	Material material ;
	DirectXCommon *dxcommon = nullptr;
public://
	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	/// <returns></returns>
	bool InitializeDescriptorHeap();

	/// <summary>
	/// マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string &directoryPath, const std::string &filename);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <returns>成否</returns>
	bool LoadTexture(const std::string &directoryPath, const std::string &filename);

	//各種バッファの生成
	void CreateBuffers();

	/// <summary>
	/// 描画
	/// </summary>
	///<param name="cmdList">描画コマンドリスト</param>
	///<param name="rootParamIndexMaterial">マテリアル用ルートパラメータ番号</param>
	void Draw(ID3D12GraphicsCommandList *cmdList, UINT rootParamIndexMaterial);

	//setter
	static void SetDevice(ID3D12Device *device) { Model::device = device; }
	//getter
	//tatic const ID3D12Resource &GetvertBuff() { return vertBuff; }
private://非公開のメンバ関数
	//OBJファイルから3Dモデルを読み込む（非公開）
	void LoadFromOBJInternal();

private:
	// 頂点インデックス配列
	std::vector<unsigned short> indices;
	// 頂点データ配列
	//VertexPosNormalUv vertices[vertexCount];
	std::vector<VertexPosNormalUv> vertices;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	// シェーダリソースビューのハンドル(CPU)
	 CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	 CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;

	 ComPtr<ID3D12Resource> constBuffB1;//定数バッファ
};

