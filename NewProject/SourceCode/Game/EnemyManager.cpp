//=================================================================================
//
//    Enemy Manager cpp
//    Author : Lin He                                作成日 : 2018/09/15
//
//=================================================================================

#include "EnemyManager.h"

#include <list>

#include "../Base/Texture.h"
#include "../Base/DirectX9.h"
#include "../Base/sound.h"

#include "GameManager.h"

//*****************************************************************************
// ネームスペース宣言
//*****************************************************************************
using std::list;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
list<Enemy*> EnemyManager::enemys_;

//=================================================================
// [ EnemyManager初期化関数 ]
//
// [ Details ]
// 各Enemyのテクスチャーの読み込み
//=================================================================
void EnemyManager::InitEnemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	//EnemyStraight Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/green_bird.png", &EnemyStraight::texture_source_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ENEMYテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	//EnemyFast Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/brown_bird.png", &EnemyFast::texture_source_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ENEMYテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	//EnemyCurve Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/bat_bird.png", &EnemyCurve::texture_source_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ENEMYテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	//EnemyPolyline Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/blue_bird.png", &EnemyPolyline::texture_source_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ENEMYテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
}

//=================================================================
// [ EnemyManager終了処理関数 ]
//
// [ Details ]
// すべてのEnemyを破壊し、
// 各Enemyのテクスチャーを解放する
//=================================================================
void EnemyManager::UninitEnemy()
{
	DestoryAllEnemy();

	EnemyPolyline::texture_source_->Release();
	EnemyPolyline::texture_source_ = NULL;

	EnemyCurve::texture_source_->Release();
	EnemyCurve::texture_source_ = NULL;

	EnemyFast::texture_source_->Release();
	EnemyFast::texture_source_ = NULL;

	EnemyStraight::texture_source_->Release();
	EnemyStraight::texture_source_ = NULL;
}

//=================================================================
// [ 全Enemy更新関数 ]
//=================================================================
void EnemyManager::UpdateAllEnemy()
{
	//list<ENEMY*>::iterator itr = gEnemys.begin();
	for (list<Enemy*>::iterator itr = enemys_.begin(); itr != enemys_.end();)
	{
		(*itr)->Update();

		//Check Collision
		//画面の左に出たら消滅する
		if ((*itr)->IsOutsideScreen())
		{
			PlaySound(SOUND_SE_FAILURE);

			DestoryEnemy(itr);
			GameManager::Instance().DamageLife(1);
			GameManager::Instance().AddScore(-200);
		}
		else
		{
			itr++;
		}
	}
}

//=================================================================
// [ 全Enemy描画関数 ]
//=================================================================
void EnemyManager::DrawAllEnemy()
{
	list<Enemy*>::iterator itr = enemys_.begin();
	for (itr = enemys_.begin(); itr != enemys_.end(); itr++)
	{
		(*itr)->Draw();
	}
}

//=================================================================
// [ Enemy生成関数 ]
//=================================================================
void EnemyManager::CreateEnemy(float posX, float posY, ENEMY_TYPE type)
{
	Enemy* enemy;

	switch (type)
	{
	case ENEMY_01: {
		enemy = new EnemyStraight(posX, posY);
		break;
	}
	case ENEMY_02: {
		enemy = new EnemyFast(posX, posY);
		break;
	}
	case ENEMY_03: {
		enemy = new EnemyCurve(posX, posY);
		break;
	}
	case ENEMY_04: {
		enemy = new EnemyPolyline(posX, posY);
		break;
	}
	default:
		break;
	}
	enemys_.push_back(enemy);
}

//=================================================================
// [ Enemy消滅関数 ]
//=================================================================
void EnemyManager::DestoryEnemy(list<Enemy*>::iterator& itr)
{
	delete *itr;
	itr = enemys_.erase(itr);
}

//=================================================================
// [ Enemy全部消滅関数 ]
//=================================================================
void EnemyManager::DestoryAllEnemy()
{
	list<Enemy*>::iterator itr = enemys_.begin();
	for (itr = enemys_.begin(); itr != enemys_.end(); itr++)
	{
		delete (*itr);
	}
	
	enemys_.clear();
}

//=================================================================
// [ Enemyリスト取得関数 ]
//=================================================================
list<Enemy*>& EnemyManager::GetEnemyList()
{
	return EnemyManager::enemys_;
}