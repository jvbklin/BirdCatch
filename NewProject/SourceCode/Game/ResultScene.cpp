//=================================================================================
//
//    ResultScene cpp
//    Author : Lin He                                作成日 : 2018/09/15
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
// 定数定義
//*****************************************************************************
const float GO_TITLE_BUTTON_POS_X = 320.0f;
const float GO_TITLE_BUTTON_POS_Y = 380.0f;
const float GO_TITLE_BUTTON_WIDTH_HALF = 60.0f;
const float GO_TITLE_BUTTON_HEIGHT_HALF = 40.0f;

//=================================================================
// [ ResultScene初期化関数 ]
//=================================================================
void ResultScene::Init()
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
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/result.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"RESULT BACKGROUNDテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	background_ = new Background(texture);

	//Go title button
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/button_go_title.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Result go titleテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	go_title_button_ = new RectButton(texture, GO_TITLE_BUTTON_POS_X, GO_TITLE_BUTTON_POS_Y,
											   GO_TITLE_BUTTON_WIDTH_HALF, GO_TITLE_BUTTON_HEIGHT_HALF);

	//スコア文字
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/score.png", &score_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"score BACKGROUNDテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}

	//スコア数字表示
	number_manager_ = new NumberManager;

	PlaySound(SOUND_BGM_GAME_CLEAR);
}

//=================================================================
// [ ResultScene終了処理関数 ]
//=================================================================
void ResultScene::Uninit()
{
	StopSound();

	//スコア表示
	delete number_manager_;

	//背景
	delete background_;
}

//=================================================================
// [ ResultScene更新関数 ]
//=================================================================
void ResultScene::Update()
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
		if (go_title_button_->PosIsInButton(posX, posY))
		{
			PlaySound(SOUND_SE_CLICK);
			SceneManager::ChangeScene(Scene::TITLE);
		}
	}
}

//=================================================================
// [ ResultScene描画関数 ]
//=================================================================
void ResultScene::Draw()
{
	//背景
	background_->Draw();

	//go title button
	go_title_button_->Draw();

	//スコア文字
	SetTexture(score_texture_);
	DrawSprite(220.0f, 280.0f, 60, 16);

	//スコア表示
	number_manager_->DrawScore(GameManager::Instance().GetScore(), 420.0f, 265.0f);
}
