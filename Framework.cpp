#include "Framework.h"

void Framework::Initilize()
{

	//WinApp�̏�����
	winApp = new WinApp();
	winApp->Initilize();


	//DirectX�̏�����
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏�����
	input = new Input();
	input->Initilize(winApp);

	//�X�v���C�g
	spriteCommon = new SpriteCommon();
	spriteCommon->Initilize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->Window_width, winApp->Window_height);

	// �f�o�b�O�e�L�X�g
	debugText = new DebugText();
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	const int debugTextTexNumber = 2;
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// �f�o�b�O�e�L�X�g������
	debugText->Initialize(spriteCommon, debugTextTexNumber);

	//�I�[�f�B�I�̏�����
	audio = new Audio();
	audio->Initilize();
	// �����ǂݍ���
	audio->LoadWave("Resources/Alarm01.wav");
	// �����Đ�
	audio->PlayWave("Resources/Alarm01.wav");

	//OBJ���烂�f���f�[�^��ǂݍ���
	model = Model::LoadFromOBJ(dxCommon->GetDev());
	// 3D�I�u�W�F�N�g�̐�
	const int OBJECT_NUM = 2;
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::Window_width, WinApp::Window_height);
	//3D�I�u�W�F�N�g����
	object3d = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�Â�
	object3d->SetModel(model);
	object3d->SetPosition({ 100,-10,0 });
}

void Framework::Finalize()
{
	//�f�o�b�O�e�L�X�g���
	debugText->Finalize();
	delete debugText;
	//�X�v���C�g�N���X���
	delete spriteCommon;

	//�I�[�f�B�I�N���X�J��
	audio->Finalize();
	delete audio;
	//DirectX���
	delete dxCommon;
	//WindowsAPI�̏I������
	winApp->Finalize();
	//WindowsAPI�̉��
	delete winApp;
	//���͉��
	delete input;

}

void Framework::Update()
{
	//Windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		//�Q�[���𔲂���
		endFlag = true;
		return;
	}
	//���͍X�V
	input->Update();
	//3d�I�u�W�F�N�g�X�V
	object3d->Update();
}

void Framework::Run()
{
	Initilize();

	while (true)  // �Q�[�����[�v
	{
		Update();
		if (endFlag) {
			break;
		}
		Draw();
	}
	//�Q�[���̏I��
	Finalize();
}
