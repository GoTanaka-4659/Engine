#pragma once

#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"

//DirectX���
class DirectXCommon
{
private:
	//�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device>dev;
	//DxGI�t�@�N�g���[
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory;
	//�R�}���h�A���P�[�^
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	//�R�}���h���X�g
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	//�R�}���h�L���[
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;
	//�X���b�v�`�F�[��
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain;
	//
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	//
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//�o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;
	//WindowsAPI
	WinApp *winApp ;

	// �t�F���X�̐���
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	UINT64 fenceVal = 0;
private:
	//�f�o�C�X�̏�����
	void InitilizeDevice();
	//�R�}���h�֘A�̏�����
	void InitializeCommand();
	//�X���b�v�`�F�[���̏�����
	void InitilizeSwapchain();
	//�����_�[�^�[�Q�b�g�r���[�̏�����
	void InitializeRenderTargetView();
	//�[�x�o�b�t�@�̏�����
	void InitilizeDepthBuffer();
	//�t�F���X�̏�����
	void InitilizeFence();

public://�����o�֐�
	//������
	void Initialize(WinApp *winApp);
	//�`�揈���O
	void PreDraw();
	//�`��㏈��
	void PostDraw();
	//�f�o�C�X�擾
	//Microsoft::WRL::ComPtr<ID3D12Device>GetDev() { return dev; }
	ID3D12Device *GetDev() { return dev.Get(); }
	//�R�}���h���X�g�擾
	ID3D12GraphicsCommandList *GetCmdList() { return cmdList.Get(); }
};

