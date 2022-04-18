#include "MasterGame.h"

void MasterGame::Initilize()
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

	//Windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		//�Q�[���𔲂���
		endFlag = true;
		return;
	}

	// DirectX���t���[�������@��������
	//3d�I�u�W�F�N�g�X�V
	object3d->Update();
	for (auto &sprite : sprites) {
		sprite->Update();
	}

	input->Update();

	// ���W����
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		//if (input->PushKey(DIK_UP)) { object3d->SetPosition(1); }
		//else if (input->PushKey(DIK_DOWN)) { object3ds[0].position.y -= 1.0f; }
		//if (input->PushKey(DIK_RIGHT)) { object3ds[0].position.x += 1.0f; }
		//else if (input->PushKey(DIK_LEFT)) { object3ds[0].position.x -= 1.0f; }
	}


	//if (input->PushKey(DIK_D) || input->PushKey(DIK_A))
	//{
	//	if (input->PushKey(DIK_D)) { angle += XMConvertToRadians(1.0f); }
	//	else if (input->PushKey(DIK_A)) { angle -= XMConvertToRadians(1.0f); }

	//	// angle���W�A������Y���܂��ɉ�]�B���a��-100
	//	eye.x = -100 * sinf(angle);
	//	eye.z = -100 * cosf(angle);
	//	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
	//}


 //  // X���W,Y���W���w�肵�ĕ\��
	////debugText->Print("Hello,DirectX!!", 200, 100);
	//// X���W,Y���W,�k�ڂ��w�肵�ĕ\��
	//debugText->Print("debugText", 200, 200, 2.0f);

	//// GPU��̃o�b�t�@�ɑΉ��������z���������擾
	//Vertex *vertMap = nullptr;
	//result = vertBuff->Map(0, nullptr, (void **)&vertMap);
	//// �S���_�ɑ΂���
	//for (int i = 0; i < _countof(vertices); i++)
	//{
	//	vertMap[i] = vertices[i];   // ���W���R�s�[
	//}
	//// �}�b�v������
	//vertBuff->Unmap(0, nullptr);

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
	//3D�I�u�W�F�N�g���
	delete object3d;
	//3D���f�������
	delete model;
	//�f�o�b�O�e�L�X�g���
	debugText->Finalize();
	delete debugText;
	//�X�v���C�g�N���X���
	delete spriteCommon;
	for (auto &sprite : sprites) {
		delete sprite;
	}
	sprites.clear();
	//�I�[�f�B�I�N���X�J��
	audio->Finalize();
	delete audio;


	//WindowsAPI�̏I������
	winApp->Finalize();
	//DirectX���
	delete dxCommon;
	//WindowsAPI�̉��
	delete winApp;
	//���͉��
	delete input;
}
