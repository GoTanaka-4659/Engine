#pragma once
#include <DirectXMath.h>
#include "PipelineSet.h"


class SpriteCommon
{
public://�����o�֐�
	//������
	void Initilize(ID3D12Device *dev, ID3D12GraphicsCommandList *commandList,int window_width, int window_height);
	//�`��O����
	void PreDraw();

	//�e�N�X�`���ǂݍ���
	void LoadTexture(UINT texnumber, const wchar_t *filename);

	void SetGraphicsRootDescriptorTable(UINT rootParameterIndex,UINT texNumber);
public:
	//�e�N�X�`���̍ő喇��
	static const int spriteSRVCount = 512;

	//�e�N�X�`�����\�[�X
	ID3D12Resource *GetTexBuff(int texnum);

	ID3D12Device *GetDevice() { return device; }

	const DirectX::XMMATRIX &GetMatProjection() { return matProjection; }

	ID3D12GraphicsCommandList *GetCommandList() { return cmdList; }
private:
	// �p�C�v���C���Z�b�g
	PipelineSet pipelineSet;
	// �ˉe�s��
	DirectX::XMMATRIX matProjection{};
	// �e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	// �e�N�X�`�����\�[�X�i�e�N�X�`���o�b�t�@�j�̔z��
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
	//�f�o�C�X
	ID3D12Device *device = nullptr;
	//�R�}���h���X�g
	ID3D12GraphicsCommandList *cmdList = nullptr;
private:
	//�p�C�v���C������
	void CreateGraphicsPipeline();
};

