#pragma once
#include <windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION	0x0800//DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include "WinApp.h"

class Input
{
public:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	//������
	void Initilize(WinApp* winapp);
	//�X�V
	void Update();

	bool PushKey(BYTE keyNo);	
	bool TriggerKey(BYTE keyNo);

private://�����o�ϐ�
	//DirectInput�̃C���X�^���X����
	ComPtr<IDirectInput8> dinput = nullptr;
	//�L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8>devkeyboard;
	//�S�L�[�̏��
	BYTE key[256] = {};
	//�O��̑S�L�[�̏��
	BYTE keyPre[256] = {};
	//WindowsAPI
	WinApp *winApp = nullptr;
};

