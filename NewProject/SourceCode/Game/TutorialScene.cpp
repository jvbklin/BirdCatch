//=================================================================================
//
//    TutorialScene cpp
//    Author : Lin He                                作成日 : 2018/10/08
//
//=================================================================================
#include "Scene.h"

#include "../Base/sound.h"
#include "../Base/Texture.h"

#include "Background.h"
#include "Button.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
const float GO_BUTTON_POS_X = 320.0f;
const float GO_BUTTON_POS_Y = 240.0f;
const float GO_BUTTON_WIDTH_HALF = 50.0f;
const float GO_BUTTON_HEIGHT_HALF = 30.0f;

//=================================================================
// [ TutorialScene初期化関数 ]
//=================================================================
void TutorialScene::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	LPDIRECT3DTEXTURE9 texture;

	//背景
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/tutorial.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"TUTORIAL BACKGROUNDテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	background_ = new Background(texture);


	//Go button
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/button_go.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Tutorial Go button テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	go_button_ = new RectButton(texture, GO_BUTTON_POS_X, GO_BUTTON_POS_Y,
										 GO_BUTTON_WIDTH_HALF, GO_BUTTON_HEIGHT_HALF);
}

//=================================================================
// [ TutorialScene終了処理関数 ]
//=================================================================
void TutorialScene::Uninit()
{
	delete go_button_;
	delete background_;

	StopSound();
}

//=================================================================
// [ TutorialScene更新関数 ]
//=================================================================
void TutorialScene::Update()
{
	// マウス取得
	CInputMouse* pInputMouse = GetMouse();

	if (pInputMouse->GetLeftTrigger())
	{
		POINT* mousePos = pInputMouse->GetPosWorld();
		HWND window = GetWindow();
		ScreenToClient(window, mousePos);
		float posX = mousePos->x;
		float posY = mousePos->y;

		//ボタンをクリックしたらシーン遷移
		if (go_button_->PosIsInButton(posX, posY))
		{
			PlaySound(SOUND_SE_CLICK);
			SceneManager::ChangeScene(Scene::GAME);
		}
	}
}

//=================================================================
// [ TutorialScene描画関数 ]
//=================================================================
void TutorialScene::Draw()
{
	background_->Draw();

	go_button_->Draw();
}
