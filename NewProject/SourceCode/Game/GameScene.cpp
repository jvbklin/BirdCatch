//=================================================================================
//
//    GameScene cpp
//    Author : Lin He                                �쐬�� : 2018/09/14
//
//=================================================================================

#include "Scene.h"

#include "../Base/DirectX9.h"
#include "../Base/Texture.h"
#include "../Base/input.h"
#include "../Base/sound.h"

#include "GameManager.h"
#include "Stage.h"
#include "Pen.h"

//=================================================================
// [ GameScene�������֐� ]
//=================================================================
void GameScene::Init()
{
	//�Q�[���}�l�W���[
	GameManager::Instance().Init();

	//�X�e�[�W
	current_stage_ = new Stage;
	current_stage_->Init();

	//�y��
	player_pen_ = new Pen;
	player_pen_->Init();

	//UI
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/heart.png", &ui_heart_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"heart BACKGROUND�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}

	PlaySound(SOUND_BGM_GAME);
}

//=================================================================
// [ GameScene�I�������֐� ]
//=================================================================
void GameScene::Uninit()
{
	StopSound();

	//UI
	ui_heart_->Release();
	ui_heart_ = NULL;

	//�y��
	current_stage_->Uninit();
	delete current_stage_;

	//�X�e�[�W
	player_pen_->Uninit();
	delete player_pen_;

	//�Q�[���}�l�W���[
	GameManager::Instance().Uninit();
}

//=================================================================
// [ GameScene�X�V�֐� ]
//=================================================================
void GameScene::Update()
{
	//�X�e�[�W
	current_stage_->Update();

	//�y��
	player_pen_->Update();

	//�Q�[���}�l�W���[
	//GameManager::Instance().Update();
	if (GameManager::Instance().GetPlayerLife() <= 0)
	{
		SceneManager::ChangeScene(Scene::GAMEOVER);
	}
}

//=================================================================
// [ GameScene�`��֐� ]
//=================================================================
void GameScene::Draw()
{
	//�X�e�[�W
	current_stage_->Draw();

	//�y��
	player_pen_->Draw();

	//UI
	SetTexture(ui_heart_);
	for (int i = 0, max = GameManager::Instance().GetPlayerLife(); i < max; i++)
	{
		DrawSprite(20.0f + i * 20.0f, 20.0f, 8, 8);
	}

	//GameManager::Instance().Draw();
}
