//=================================================================================
//
//    ResultScene cpp
//    Author : Lin He                                �쐬�� : 2018/09/15
//
//=================================================================================

#include "Scene.h"

#include "../Base/Texture.h"
#include "../Base/NumberManager.h"
#include "../Base/sound.h"

#include "Background.h"
#include "Button.h"
#include "GameManager.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const float GO_TITLE_BUTTON_POS_X = 320.0f;
const float GO_TITLE_BUTTON_POS_Y = 380.0f;
const float GO_TITLE_BUTTON_WIDTH_HALF = 60.0f;
const float GO_TITLE_BUTTON_HEIGHT_HALF = 40.0f;

//=================================================================
// [ ResultScene�������֐� ]
//=================================================================
void ResultScene::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	LPDIRECT3DTEXTURE9 texture;

	//�w�i
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/result.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"RESULT BACKGROUND�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	background_ = new Background(texture);

	//Go title button
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/button_go_title.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Result go title�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	go_title_button_ = new RectButton(texture, GO_TITLE_BUTTON_POS_X, GO_TITLE_BUTTON_POS_Y,
											   GO_TITLE_BUTTON_WIDTH_HALF, GO_TITLE_BUTTON_HEIGHT_HALF);

	//�X�R�A����
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/score.png", &score_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"score BACKGROUND�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}

	//�X�R�A�����\��
	number_manager_ = new NumberManager;

	PlaySound(SOUND_BGM_GAME_CLEAR);
}

//=================================================================
// [ ResultScene�I�������֐� ]
//=================================================================
void ResultScene::Uninit()
{
	StopSound();

	//�X�R�A�\��
	delete number_manager_;

	//�w�i
	delete background_;
}

//=================================================================
// [ ResultScene�X�V�֐� ]
//=================================================================
void ResultScene::Update()
{
	// �}�E�X�擾
	CInputMouse* pInputMouse = GetMouse();

	if (pInputMouse->GetLeftTrigger())
	{
		POINT* mousePos = pInputMouse->GetPosWorld();
		HWND window = GetWindow();
		ScreenToClient(window, mousePos);
		float posX = mousePos->x;
		float posY = mousePos->y;

		//�{�^�����N���b�N������V�[���J��
		if (go_title_button_->PosIsInButton(posX, posY))
		{
			PlaySound(SOUND_SE_CLICK);
			SceneManager::ChangeScene(Scene::TITLE);
		}
	}
}

//=================================================================
// [ ResultScene�`��֐� ]
//=================================================================
void ResultScene::Draw()
{
	//�w�i
	background_->Draw();

	//go title button
	go_title_button_->Draw();

	//�X�R�A����
	SetTexture(score_texture_);
	DrawSprite(220.0f, 280.0f, 60, 16);

	//�X�R�A�\��
	number_manager_->DrawScore(GameManager::Instance().GetScore(), 420.0f, 265.0f);
}
