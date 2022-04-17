//#pragma once
//#include <DirectXMath.h>
//
//class Camera
//{
//private: // エイリアス
//// Microsoft::WRL::を省略
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//	// DirectX::を省略
//	using XMFLOAT2 = DirectX::XMFLOAT2;
//	using XMFLOAT3 = DirectX::XMFLOAT3;
//	using XMFLOAT4 = DirectX::XMFLOAT4;
//	using XMMATRIX = DirectX::XMMATRIX;
//public:
//	Camera();
//
//	virtual void Update();
//
//	void UpdateViewMatrix();
//
//	void UpdateProjectionMatrix();
//
//private://メンバ変数
//	//視点
//	XMFLOAT3 eye = { 0,0,-20 };
//	//注視点
//	XMFLOAT3 target = { 0,0,0 };
//	//上方向ベクトル
//	XMFLOAT3 up = { 0,1,0 };
//
//};
//
