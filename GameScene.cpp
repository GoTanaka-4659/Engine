#include "GameScene.h"

GameScene::GameScene()
{
}

void GameScene::Initilize(DirectXCommon *dxCommon, Input *input, Audio *audio)
{
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommmon = dxCommon;
	this->input = input;
	this->audio = audio;

	// �f�o�b�O�e�L�X�g
	
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	const int debugTextTexNumber = 2;
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// �f�o�b�O�e�L�X�g������
	debugText->Initialize(spriteCommon, debugTextTexNumber);

	// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(0, L"Resources/texture.png");
	spriteCommon->LoadTexture(1, L"Resources/house.png");
	//OBJ���烂�f���f�[�^��ǂݍ���
	Model *model = Model::LoadFromOBJ(dxCommon->GetDev());
	// 3D�I�u�W�F�N�g�̐�
	const int OBJECT_NUM = 2;
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::Window_width, WinApp::Window_height);
	//3D�I�u�W�F�N�g����
	Object3d *object3d = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�Â�
	object3d->SetModel(model);
	object3d->SetPosition({ 100,-10,0 });

}

void GameScene::Update()
{
}

void GameScene::Draw()
{
}
