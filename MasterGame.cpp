#include "MasterGame.h"

void MasterGame::Initilize()
{
	//���N���X�̏�����
	Framework::Initilize();

	// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(0, L"Resources/Gorushi.png");
	spriteCommon->LoadTexture(1, L"Resources/Gorushi.png");

	// �X�v���C�g�̐���
	for (int i = 0; i < 1; i++)
	{
		int texNumber = rand() % 2;
		Sprite *sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

		// �X�v���C�g�̍��W�ύX
		sprite->SetPosition({ (float)(rand() % 1280),(float)(rand() % 720),0 });
		//sprite->SetRotation((float)(rand() % 360));
		sprite->SetSize({ (float)(rand() % 400) ,(float)(rand() % 100) });


		// ���_�o�b�t�@�ɔ��f
		sprite->TransferVertexBuffer();

		sprites.push_back(sprite);
		sprite->SetPosition({ 500,300,0 });
	}

	int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[
}

void MasterGame::Update()
{
	//���N���X�̍X�V
	Framework::Update();

	// DirectX���t���[�������@��������
	//3d�I�u�W�F�N�g�X�V
	//object3d->Update();
	for (auto &sprite : sprites) {
		sprite->Update();
	}

	// ���W����
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{

	}


	
	// DirectX���t���[�������@�����܂�

}

void MasterGame::Draw()
{
	dxCommon->PreDraw();

	//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	//3d�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCmdList());
	//3d�I�u�W�F�N�g�̕`��
	object3d->Draw();

	//3d�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	//�X�v���C�g���ʃR�}���h
	spriteCommon->PreDraw();
	//�X�v���C�g�`��
	for (auto &sprite : sprites) {
		sprite->Draw();
	}
	//�f�o�b�N�e�L�X�g
	debugText->DrawAll();

	// �`��R�}���h�����܂�
	dxCommon->PostDraw();
}

void MasterGame::Finalize()
{
	//�X�v���C�g�ʊJ��
	for (auto &sprite : sprites) {
		delete sprite;
	}
	sprites.clear();
	
	//3D�I�u�W�F�N�g���
	delete object3d;
	//3D���f�������
	delete model;

	//���N���X�̏I������
	Framework::Finalize();
}
