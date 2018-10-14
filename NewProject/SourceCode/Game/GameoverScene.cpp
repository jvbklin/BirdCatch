//=================================================================================
//
//    GameoverScene cpp
//    Author : Lin He                                �쐬�� : 2018/10/08
//
//=================================================================================
#include "Scene.h"

#include "../Base/Texture.h"
#include "../Base/sound.h"

#include "Background.h"
#include "Button.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const float AGAIN_BUTTON_POS_X = 160.0f;
const float AGAIN_BUTTON_POS_Y = 400.0f;
const float AGAIN_BUTTON_WIDTH_HALF = 60.0f;
const float AGAIN_BUTTON_HEIGHT_HALF = 40.0f;

const float GO_TITLE_BUTTON_POS_X = 480.0f;
const float GO_TITLE_BUTTON_POS_Y = 400.0f;
const float GO_TITLE_BUTTON_WIDTH_HALF = 60.0f;
const float GO_TITLE_BUTTON_HEIGHT_HALF = 40.0f;

//=================================================================
// [ GameoverScene�������֐� ]
//=================================================================
void GameoverScene::Init()
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
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/game_over.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"GAMEOVER BACKGROUND�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	background_ = new Background(texture);


	//Again button
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/button_again.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"GAMEOVER BACKGROUND�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	again_button_ = new RectButton(texture, AGAIN_BUTTON_POS_X, AGAIN_BUTTON_POS_Y,
											AGAIN_BUTTON_WIDTH_HALF, AGAIN_BUTTON_HEIGHT_HALF);

	//Go title button
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/button_go_title.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"GAMEOVER BACKGROUND�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	go_title_button_ = new RectButton(texture, GO_TITLE_BUTTON_POS_X, GO_TITLE_BUTTON_POS_Y,
											   GO_TITLE_BUTTON_WIDTH_HALF, GO_TITLE_BUTTON_HEIGHT_HALF);

	PlaySound(SOUND_BGM_GAME_OVER);
}

//=================================================================
// [ GameoverScene�I�������֐� ]
//=================================================================
void GameoverScene::Uninit()
{
	StopSound();

	delete go_title_button_;
	delete again_button_;
	delete background_;
}

//=================================================================
// [ GameoverScene�X�V�֐� ]
//=================================================================
void GameoverScene::Update()
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
		if (again_button_->PosIsInButton(posX, posY))
		{
			PlaySound(SOUND_SE_CLICK);
			SceneManager::ChangeScene(Scene::GAME);
		}
		else if (go_title_button_->PosIsInButton(posX, posY))
		{
			PlaySound(SOUND_SE_CLICK);
			SceneManager::ChangeScene(Scene::TITLE);
		}
	}
}

//=================================================================
// [ GameoverScene�`��֐� ]
//=================================================================
void GameoverScene::Draw()
{
	//�w�i
	background_->Draw();

	//Again button
	again_button_->Draw();

	//Go title button
	go_title_button_->Draw();
}
