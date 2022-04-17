#pragma once
#include <windows.h>

class WinApp
{
public://�ÓI�����o�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public://�萔
	//�E�B���h�E����
	static const int Window_width = 1280;
	//�E�B���h�E�c��
	static const int Window_height = 720;

public://�����o�֐�
	//������
	void Initilize();
	//�X�V
	void Update();
	//�I��
	void Finalize();
	//���b�Z�[�W�̏���
	bool ProcessMessage();
public:
	//getter
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHinstance() { return w.hInstance; }
private:
	//�E�B���h�E�n���h��
	HWND hwnd = nullptr;
	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};
};

