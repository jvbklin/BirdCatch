//=================================================================================
//
//    GameManager cpp
//    Author : Lin He                                �쐬�� : 2018/10/07
//
//=================================================================================
#include "GameManager.h"
#include "../Base/NumberManager.h"
#include "../Game/Scene.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const int SCORE_MIN = 1000;
//const int SCORE_MAX = 99999;
const int PLAYER_LIFE_MAX = 8;

//=================================================================
// [ GameManager Constructor ]
//=================================================================
GameManager::GameManager()
{
}

//=================================================================
// [ GameManager Destructor ]
//=================================================================
GameManager::~GameManager() 
{
}

//=================================================================
// [ GameManager�������֐� ]
//=================================================================
void GameManager::Init()
{
	score_ = SCORE_MIN;
	player_life_ = PLAYER_LIFE_MAX;
}

//=================================================================
// [ GameManager�I�������֐� ]
//=================================================================
void GameManager::Uninit()
{
}

////=================================================================
//// [ GameManager�X�V�֐� ]
////=================================================================
//void GameManager::Update()
//{
//
//}
//
////=================================================================
//// [ GameManager�`��֐� ]
////=================================================================
//void GameManager::Draw()
//{
//
//}

//=================================================================
// [ �X�R�A�����֐� ]
//=================================================================
void GameManager::AddScore(int num)
{
	score_ += num;

}

//=================================================================
// [ �X�R�A�擾�֐� ]
//=================================================================
int GameManager::GetScore()
{
	if (score_ <= SCORE_MIN)
		score_ = SCORE_MIN;

	return score_;
}

//=================================================================
// [ ���C�t�_���[�W�֐� ]
//=================================================================
void GameManager::DamageLife(int num)
{
	player_life_ -= num;
}

//=================================================================
// [ �v���C���[���C�t�擾�֐� ]
//=================================================================
int GameManager::GetPlayerLife()
{
	return player_life_;
}