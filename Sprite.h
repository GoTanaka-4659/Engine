#pragma once
#include <wrl.h>
#include <DirectXMath.h>
#include <d3d12.h>
#include "SpriteCommon.h"

class Sprite
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	// ���_�f�[�^
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT2 uv;  // uv���W
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {
		XMFLOAT4 color; // �F (RGBA)
		XMMATRIX mat;   // �R�c�ϊ��s��
	};

public:
	static Sprite*Create(SpriteCommon *spriteCommon, UINT texNum, XMFLOAT2 anchorpoint = { 0.5f,0.5f }, bool isFlipX = false, bool isFlipY = false);

	void Initialize(SpriteCommon *spritecommon, UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	///���_�o�b�t�@�̓]��
	void TransferVertexBuffer();
	//�`��
	void Draw();

	void Update();

	void SetPosition(const XMFLOAT3 &position) { position_ = position; }
	void SetRotation(float rotation) { rotation_ = rotation; }
	void SetSize(const DirectX::XMFLOAT2 &size) { size_ = size; }
	void SetTexLeftTop(const DirectX::XMFLOAT2 &texLeftTop) { texLeftTop_ = texLeftTop; }
	void SetTexSize(const DirectX::XMFLOAT2 &texSize) { texSize_ = texSize; }
private:
	//�X�v���C�g���ʕ���
	SpriteCommon *spritecommon_ = nullptr;
	//���_�o�b�t�@;
	ComPtr<ID3D12Resource> vertBuff_;
	//���_�o�b�t�@�r���[;
	D3D12_VERTEX_BUFFER_VIEW vbView_{};
	//�萔�o�b�t�@;
	ComPtr<ID3D12Resource> constBuff_;
	// Z�����̉�]�p
	float rotation_ = 0.0f;
	// ���W
	XMFLOAT3 position_ = { 0,0,0 };
	// ���[���h�s��
	XMMATRIX matWorld_;
	// �F(RGBA)
	XMFLOAT4 color_ = { 1, 1, 1, 1 };
	// �e�N�X�`���ԍ�
	UINT texNumber_ = 0;
	// �傫��
	XMFLOAT2 size_ = { 100, 100 };
	// �A���J�[�|�C���g
	XMFLOAT2 anchorpoint_ = { 0.5f, 0.5f };
	// ���E���]
	bool isFlipX_ = false;
	// �㉺���]
	bool isFlipY_ = false;
	// �e�N�X�`��������W
	XMFLOAT2 texLeftTop_ = { 0, 0 };
	// �e�N�X�`���؂�o���T�C�Y
	XMFLOAT2 texSize_ = { 100, 100 };
	// ��\��
	bool isInvisible_ = false;
};

