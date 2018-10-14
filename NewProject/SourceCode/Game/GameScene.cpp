//=================================================================================
//
//    GameScene cpp
//    Author : Lin He                                作成日 : 2018/09/14
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
// [ GameScene初期化関数 ]
//=================================================================
void GameScene::Init()
{
	//ゲームマネジャー
	GameManager::Instance().Init();

	//ステージ
	current_stage_ = new Stage;
	current_stage_->Init();

	//ペン
	player_pen_ = new Pen;
	player_pen_->Init();

	//UI
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/heart.png", &ui_heart_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"heart BACKGROUNDテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}

	PlaySound(SOUND_BGM_GAME);
}

//=================================================================
// [ GameScene終了処理関数 ]
//=================================================================
void GameScene::Uninit()
{
	StopSound();

	//UI
	ui_heart_->Release();
	ui_heart_ = NULL;

	//ペン
	current_stage_->Uninit();
	delete current_stage_;

	//ステージ
	player_pen_->Uninit();
	delete player_pen_;

	//ゲームマネジャー
	GameManager::Instance().Uninit();
}

//=================================================================
// [ GameScene更新関数 ]
//=================================================================
void GameScene::Update()
{
	//ステージ
	current_stage_->Update();

	//ペン
	player_pen_->Update();

	//ゲームマネジャー
	//GameManager::Instance().Update();
	if (GameManager::Instance().GetPlayerLife() <= 0)
	{
		SceneManager::ChangeScene(Scene::GAMEOVER);
	}
}

//=================================================================
// [ GameScene描画関数 ]
//=================================================================
void GameScene::Draw()
{
	//ステージ
	current_stage_->Draw();

	//ペン
	player_pen_->Draw();

	//UI
	SetTexture(ui_heart_);
	for (int i = 0, max = GameManager::Instance().GetPlayerLife(); i < max; i++)
	{
		DrawSprite(20.0f + i * 20.0f, 20.0f, 8, 8);
	}

	//GameManager::Instance().Draw();
}
