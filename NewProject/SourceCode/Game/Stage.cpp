//=================================================================================
//
//    ステージ　クラス[Stage.cpp]
//    Author : Lin He                                作成日 : 2018/09/14
//
//=================================================================================

#include "Stage.h"

#include "../main.h"
#include "../Base/DirectX9.h"
#include "../Base/Texture.h"

#include "Scene.h"
#include "EnemyManager.h"
#include "Background.h"
#include "GameManager.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct SPAWN_POINT {
	int spawn_time;
	ENEMY_TYPE enemy_type;
	float posY;
};

//*****************************************************************************
// 定数定義
//*****************************************************************************

const int GAME_CLEAR_TIME = 180;

const int ENEMY_MAX = 100;

const SPAWN_POINT enemy_spawn_points[ENEMY_MAX] = {
	{ 4,ENEMY_01,120.0f },
	{ 6,ENEMY_01,120.0f },
	{ 8,ENEMY_01,60.0f },
	{ 10,ENEMY_01,190.0f },
	{ 12,ENEMY_01,60.0f },
	{ 14,ENEMY_04,140.0f },
	{ 16,ENEMY_01,180.0f },
	{ 18,ENEMY_04,100.0f },
	{ 20,ENEMY_01,120.0f },
	{ 23,ENEMY_04,60.0f },
	{ 25,ENEMY_01,140.0f },
	{ 27,ENEMY_03,80.0f },
	{ 30,ENEMY_01,180.0f },
	{ 32,ENEMY_02,120.0f },
	{ 35,ENEMY_03,140.0f },
	{ 37,ENEMY_03,120.0f },
	{ 40,ENEMY_02,160.0f },
	{ 42,ENEMY_02,120.0f },
	{ 44,ENEMY_01,60.0f },
	{ 44,ENEMY_01,180.0f },
	{ 47,ENEMY_01,100.0f },
	{ 50,ENEMY_01,180.0f },
	{ 53,ENEMY_01,140.0f },
	{ 56,ENEMY_03,120.0f },
	{ 59,ENEMY_01,120.0f },
	{ 61,ENEMY_03,120.0f },
	{ 64,ENEMY_03,120.0f },
	{ 67,ENEMY_03,60.0f },
	{ 67,ENEMY_01,160.0f },
	{ 70,ENEMY_01,100.0f },
	{ 70,ENEMY_01,180.0f },
	{ 73,ENEMY_04,120.0f },
	{ 75,ENEMY_04,140.0f },
	{ 78,ENEMY_04,100.0f },
	{ 81,ENEMY_01,120.0f },
	{ 81,ENEMY_01,180.0f },
	{ 84,ENEMY_01,100.0f },
	{ 84,ENEMY_01,180.0f },
	{ 87,ENEMY_02,130.0f },
	{ 90,ENEMY_04,100.0f },
	{ 90,ENEMY_01,140.0f },
	{ 93,ENEMY_02,120.0f },
	{ 94,ENEMY_01,120.0f },
	{ 95,ENEMY_02,120.0f },
	{ 96,ENEMY_04,120.0f },
	{ 97,ENEMY_01,120.0f },
	{ 97,ENEMY_01,180.0f },
	{ 99,ENEMY_04,120.0f },
	{ 100,ENEMY_01,80.0f },
	{ 100,ENEMY_01,150.0f },
	{ 101,ENEMY_02,120.0f },
	{ 103,ENEMY_04,100.0f },
	{ 103,ENEMY_01,120.0f },
	{ 105,ENEMY_03,160.0f },
	{ 106,ENEMY_04,100.0f },
	{ 107,ENEMY_01,160.0f },
	{ 109,ENEMY_04,140.0f },
	{ 109,ENEMY_04,80.0f },
	{ 109,ENEMY_01,120.0f },
	{ 112,ENEMY_03,120.0f },
	{ 114,ENEMY_02,80.0f },
	{ 115,ENEMY_01,100.0f },
	{ 117,ENEMY_04,170.0f },
	{ 118,ENEMY_01,80.0f },
	{ 120,ENEMY_02,120.0f },
	{ 122,ENEMY_01,80.0f },
	{ 124,ENEMY_01,120.0f },
	{ 126,ENEMY_03,150.0f },
	{ 128,ENEMY_01,180.0f },
	{ 130,ENEMY_03,100.0f },
	{ 132,ENEMY_03,140.0f },
	{ 135,ENEMY_04,160.0f },
	{ 137,ENEMY_03,80.0f },
	{ 139,ENEMY_01,120.0f },
	{ 141,ENEMY_04,100.0f },
	{ 143,ENEMY_01,80.0f },
	{ 145,ENEMY_03,120.0f },
	{ 147,ENEMY_01,160.0f },
	{ 149,ENEMY_04,80.0f },
	{ 151,ENEMY_01,180.0f },
	{ 153,ENEMY_03,80.0f },
	{ 155,ENEMY_01,120.0f },
	{ 156,ENEMY_01,160.0f },
	{ 158,ENEMY_02,140.0f },
	{ 160,ENEMY_01,180.0f },
	{ 162,ENEMY_01,60.0f },
	{ 162,ENEMY_01,180.0f },
	{ 164,ENEMY_01,120.0f },
	{ 164,ENEMY_04,60.0f },
	{ 166,ENEMY_03,160.0f },
	{ 166,ENEMY_04,60.0f },
	{ 168,ENEMY_04,160.0f },
	{ 168,ENEMY_01,60.0f },
	{ 170,ENEMY_01,80.0f },
	{ 170,ENEMY_01,160.0f },
	{ 172,ENEMY_03,120.0f },
	{ 172,ENEMY_03,100.0f },
	{ 174,ENEMY_02,140.0f },
	{ 175,ENEMY_02,80.0f },
	{ 176,ENEMY_02,120.0f }
};

//=================================================================
// [ Stage初期化関数 ]
//=================================================================
void Stage::Init() 
{
	count_frames_ = 0;
	count_seconds_ = 0;

	next_spawn_enemy_index_ = 0;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	LPDIRECT3DTEXTURE9 texture;

	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/bg.png", &texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"TITLE BACKGROUNDテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	background_ = new HorizontalScrollBackground(texture);

	EnemyManager::InitEnemy();
}

//=================================================================
// [ Stage終了処理関数 ]
//=================================================================
void Stage::Uninit()
{
	count_frames_ = 0;
	count_seconds_ = 0;

	next_spawn_enemy_index_ = 0;

	EnemyManager::UninitEnemy();

	delete background_;
}

//=================================================================
// [ Stage更新関数 ]
//=================================================================
void Stage::Update()
{
	//背景更新
	background_->Update();

	//時間経過
	count_frames_++;
	if (count_frames_ >= 59)
	{
		count_frames_ = 0;
		count_seconds_++;
	}

	if (count_seconds_ == GAME_CLEAR_TIME)
	{
		GameManager::Instance().AddScore(GameManager::Instance().GetPlayerLife() * 1000);
		SceneManager::ChangeScene(Scene::RESULT);
	}

	//ENEMYを追加する
	if (next_spawn_enemy_index_ > ENEMY_MAX)
		return;

	while (count_seconds_ == enemy_spawn_points[next_spawn_enemy_index_].spawn_time)
	{
		EnemyManager::CreateEnemy(SCREEN_WIDTH, enemy_spawn_points[next_spawn_enemy_index_].posY * 2, enemy_spawn_points[next_spawn_enemy_index_].enemy_type);

		next_spawn_enemy_index_++;
	}

	//ENEMYを更新する
	EnemyManager::UpdateAllEnemy();
}

//=================================================================
// [ Stage更新関数 ]
//=================================================================
void Stage::Draw()
{
	background_->Draw();

	EnemyManager::DrawAllEnemy();
}