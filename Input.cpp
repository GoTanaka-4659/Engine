#include "Input.h"
#include <cassert>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib,"dxguid.lib")

void Input::Initilize(WinApp* winApp)
{
	HRESULT result;
	//NULL���o
	assert(winApp);
	//WinApp�̃C���X�^���X���L�^
	this->winApp = winApp;
	
	result = DirectInput8Create(winApp->GetHinstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&dinput, nullptr);
	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	//�r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

}

void Input::Update()
{
	HRESULT result;


	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();
	//�O��̃L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));
	
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNo)
{
	//�w��L�[�������Ă����true
	if (key[keyNo]) {
		return true;
	}
	//����ȊOfalse
	return false;
}

bool Input::TriggerKey(BYTE keyNo)
{
	if (keyPre[keyNo] == false && key[keyNo]) {
		return true;
	}
	return false;
}


