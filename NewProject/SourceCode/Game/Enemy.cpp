//=================================================================================
//
//    Enemy cpp
//    Author : Lin He                                作成日 : 2018/09/15
//
//=================================================================================

#include "Enemy.h"
#include "EnemyManager.h"
#include "../main.h"
#include "../Base/Texture.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
const int ENEMY_WIDTH = 64;
const int ENEMY_HEIGHT = 64;
const int ENEMY_WIDTH_HALF = ENEMY_WIDTH / 2;
const int ENEMY_HEIGHT_HALF = ENEMY_HEIGHT / 2;

const float EnemyStraight::speedX_ = 1.2f * 2;
const float EnemyFast::speedX_ = 3.0f * 2;
const float EnemyCurve::speedX_ = 2.0f * 2;
const float EnemyPolyline::speedX_ = 1.2f * 2;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 EnemyStraight::texture_source_;
LPDIRECT3DTEXTURE9 EnemyFast::texture_source_;
LPDIRECT3DTEXTURE9 EnemyCurve::texture_source_;
LPDIRECT3DTEXTURE9 EnemyPolyline::texture_source_;

//=================================================================
// [ Enemy Constructor ]
//=================================================================
Enemy::Enemy(float posX, float posY) : posX_(posX), posY_(posY)
{
	animation_count_ = 0;
	animation_index_ = 0;
}

//=================================================================
// [ Enemy 描画関数 ]
//=================================================================
void Enemy::Draw() 
{
	SetTexture(texture_);

	animation_count_++;
	if (animation_count_ > 20)
	{
		animation_count_ = 0;

		animation_index_++;
		if (animation_index_ > 7)
			animation_index_ = 0;
	}

	float texcoord_left = animation_index_ % 4 * 0.25f;
	float texcoord_up = animation_index_ / 4 * 0.5f;

	float texcoord_right = texcoord_left + 0.25f;
	float texcoord_down = texcoord_up + 0.5f;

	DrawSprite(posX_, posY_, ENEMY_WIDTH_HALF, ENEMY_HEIGHT_HALF,
								texcoord_left, texcoord_up,
								texcoord_right, texcoord_down);


	//DrawTexture(posX_ - ENEMY_WIDTH_HALF, posY_ - ENEMY_HEIGHT_HALF, 
	//			256, 128, 
	//			ENEMY_WIDTH * (animation_index_ % 4), ENEMY_HEIGHT * (animation_index_ / 4),
	//			ENEMY_WIDTH, ENEMY_HEIGHT);
}

//=================================================================
// [ Enemyが画面の左に過ぎたかどうかをチェックする関数 ]
//=================================================================
bool Enemy::IsOutsideScreen()
{
	return (posX_ + ENEMY_WIDTH_HALF < 0);
}

//=================================================================
// [ EnemyStraight Constructor ]
//=================================================================
EnemyStraight::EnemyStraight(float posX, float posY) : Enemy(posX, posY)
{
	texture_ = EnemyStraight::texture_source_;
}

//=================================================================
// [ EnemyStraight 更新関数 ]
//=================================================================
void EnemyStraight::Update()
{
	posX_ -= EnemyStraight::speedX_;
}

//=================================================================
// [ EnemyFast Constructor ]
//=================================================================
EnemyFast::EnemyFast(float posX, float posY) : EnemyStraight(posX, posY)
{
	texture_ = EnemyFast::texture_source_;
}

//=================================================================
// [ EnemyFast 更新関数 ]
//=================================================================
void EnemyFast::Update()
{
	posX_ -= EnemyFast::speedX_;
}

//=================================================================
// [ EnemyCurve Constructor ]
//=================================================================
EnemyCurve::EnemyCurve(float posX, float posY) : Enemy(posX, posY)
{
	texture_ = EnemyCurve::texture_source_;
}

//=================================================================
// [ EnemyCurve 更新関数 ]
//=================================================================
void EnemyCurve::Update()
{
	posX_ -= EnemyCurve::speedX_;
	angle_ += 0.1f;
	posY_ += 6 * sinf(angle_);
}

//=================================================================
// [ EnemyPolyline Constructor ]
//=================================================================
EnemyPolyline::EnemyPolyline(float posX, float posY) : Enemy(posX, posY)
{
	texture_ = EnemyPolyline::texture_source_;
	speedY_ = 3.0f;
}

//=================================================================
// [ EnemyPolyline 更新関数 ]
//=================================================================
void EnemyPolyline::Update()
{
	posX_ -= EnemyPolyline::speedX_;
	posY_ += speedY_;

	if (posY_ - ENEMY_HEIGHT_HALF < 0 || posY_ + ENEMY_HEIGHT_HALF> SCREEN_HEIGHT)
	{
		speedY_ = -speedY_;
	}
}