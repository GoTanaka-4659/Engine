//#pragma once
//
//#include <DirectXMath.h>
//
/////�_����
//class PointLight
//{
//private: // �G�C���A�X
//// Microsoft::WRL::���ȗ�
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//	// DirectX::���ȗ�
//	using XMFLOAT2 = DirectX::XMFLOAT2;
//	using XMFLOAT3 = DirectX::XMFLOAT3;
//	using XMFLOAT4 = DirectX::XMFLOAT4;
//	using XMMATRIX = DirectX::XMMATRIX;
//public://�T�u�N���X
//	//�萔�o�b�t�@�p�f�[�^�\����
//	struct ConstBufferData
//	{
//		XMFLOAT3 lightpos;
//		float pad1;
//		XMFLOAT3 lightcolor;
//		float pad2;
//		XMFLOAT3 lightatten;
//		unsigned int active;
//	};
//public://�����o�֐�
//	inline void SetLightPos(const XMFLOAT3 &lightpos) { this->lightpos = lightpos; }
//	inline const XMFLOAT3 &SetLightPos() { return lightpos; }
//	inline void SetLightColor(const XMFLOAT3 &lightcolor) { this->lightpos = lightcolor; }
//	inline const XMFLOAT3 &SetLightColor() { return lightcolor; }
//	inline void SetLightAtten(const XMFLOAT3 &lightAtten) { this->lightAtten = lightAtten; }
//	inline const XMFLOAT3 &SetLightAtten() { return lightAtten; }
//	inline void SetActive(bool active) { this->active = active; }
//	inline bool IsActive() { return active; }
//
//private://�����o�ϐ�
//	//���C�g���W�i���[���h���W�j
//	XMFLOAT3 lightpos = { 0,0,0 };
//	//���C�g�F
//	XMFLOAT3 lightcolor = { 1,1,1 };
//	//���C�g���������W��
//	XMFLOAT3 lightAtten = { 1.0f,1.0f,1.0f };
//	//�L���t���O
//	bool active = false;
//};
//
