//=================================================================================
//
//    TitleScene cpp
//    Author : Lin He                                作成日 : 2018/09/15
//
//=================================================================================

#include "Scene.h"

#include "../main.h"
#include "../Base/Texture.h"
#include "../Base/input.h"
#include "../Base/sound.h"
#include "Background.h"
#include "Button.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
const float START_BUTTON_POS_X = 320.0f;
const float START_BUTTON_POS_Y = 400.0f;
const float START_BUTTON_WIDTH_HALF = 100.0f;
const float START_BUTTON_HEIGHT_HALF = 50.0f;

//=================================================================
// [ TitleScene初期化関数 ]
//=================================================================
void TitleScene::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	LPDIRECT3DTEXTURE9 texture;

	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/title.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"TITLE BACKGROUNDテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	background_ = new Background(texture);

	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/title_start.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"START BUTTONテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	start_button_ = new StartButton(texture, START_BUTTON_POS_X, START_BUTTON_POS_Y,
											 START_BUTTON_WIDTH_HALF, START_BUTTON_HEIGHT_HALF);

	PlaySound(SOUND_BGM_TITLE);
}

//=================================================================
// [ TitleScene終了処理関数 ]
//=================================================================
void TitleScene::Uninit()
{
	delete start_button_;
	delete background_;
}

//=================================================================
// [ TitleScene更新関数 ]
//=================================================================
void TitleScene::Update()
{
	start_button_->Update();

	// マウス取得
	CInputMouse* pInputMouse = GetMouse();

	if (pInputMouse-> GetLeftTrigger())
	{
		POINT* mousePos = pInputMouse->GetPosWorld();
		HWND window = GetWindow();
		ScreenToClient(window, mousePos);
		float posX = mousePos->x;
		float posY = mousePos->y;

		//ボタンをクリックしたらシーン遷移
		if (start_button_->PosIsInButton(posX, posY))
		{
			PlaySound(SOUND_SE_CLICK);
			SceneManager::ChangeScene(Scene::TUTORIAL);
		}
	}
}

//=================================================================
// [ TitleScene描画関数 ]
//=================================================================
void TitleScene::Draw()
{
	background_->Draw();
	start_button_->Draw();
}