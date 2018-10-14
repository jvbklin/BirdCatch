//=================================================================================
//
//    Enemy Manager cpp
//    Author : Lin He                                �쐬�� : 2018/09/15
//
//=================================================================================

#include "EnemyManager.h"

#include <list>

#include "../Base/Texture.h"
#include "../Base/DirectX9.h"
#include "../Base/sound.h"

#include "GameManager.h"

//*****************************************************************************
// �l�[���X�y�[�X�錾
//*****************************************************************************
using std::list;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
list<Enemy*> EnemyManager::enemys_;

//=================================================================
// [ EnemyManager�������֐� ]
//
// [ Details ]
// �eEnemy�̃e�N�X�`���[�̓ǂݍ���
//=================================================================
void EnemyManager::InitEnemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	//EnemyStraight Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/green_bird.png", &EnemyStraight::texture_source_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ENEMY�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	//EnemyFast Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/brown_bird.png", &EnemyFast::texture_source_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ENEMY�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	//EnemyCurve Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/bat_bird.png", &EnemyCurve::texture_source_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ENEMY�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	//EnemyPolyline Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/blue_bird.png", &EnemyPolyline::texture_source_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ENEMY�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
}

//=================================================================
// [ EnemyManager�I�������֐� ]
//
// [ Details ]
// ���ׂĂ�Enemy��j�󂵁A
// �eEnemy�̃e�N�X�`���[���������
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
// [ �SEnemy�X�V�֐� ]
//=================================================================
void EnemyManager::UpdateAllEnemy()
{
	//list<ENEMY*>::iterator itr = gEnemys.begin();
	for (list<Enemy*>::iterator itr = enemys_.begin(); itr != enemys_.end();)
	{
		(*itr)->Update();

		//Check Collision
		//��ʂ̍��ɏo������ł���
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
// [ �SEnemy�`��֐� ]
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
// [ Enemy�����֐� ]
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
// [ Enemy���Ŋ֐� ]
//=================================================================
void EnemyManager::DestoryEnemy(list<Enemy*>::iterator& itr)
{
	delete *itr;
	itr = enemys_.erase(itr);
}

//=================================================================
// [ Enemy�S�����Ŋ֐� ]
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
// [ Enemy���X�g�擾�֐� ]
//=================================================================
list<Enemy*>& EnemyManager::GetEnemyList()
{
	return EnemyManager::enemys_;
}