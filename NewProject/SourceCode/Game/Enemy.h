//=================================================================================
//
//    Enemy header
//    Author : Lin He                                作成日 : 2018/09/15
//
//=================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../Base/DirectX9.h"

//*****************************************************************************
// 列挙型宣言
//*****************************************************************************
typedef enum {
	ENEMY_01,	//EnemyStraight
	ENEMY_02,	//EnemyFast
	ENEMY_03,	//EnemyCurve
	ENEMY_04	//EnemyPolyline
}ENEMY_TYPE;

//*****************************************************************************
// Enemy Class (abstract class)
//*****************************************************************************
class Enemy
{
	public:
		float posX_;
		float posY_;

	protected:
		LPDIRECT3DTEXTURE9 texture_;
		int animation_count_;
		int animation_index_;

	public:
		//=================================================================
		// [ Enemy Constructor ]
		//
		// [ Parameters ]
		// [float]			posX, posY   :	Enemyの初期座標
		//=================================================================
		Enemy(float posX, float posY);

		virtual ~Enemy() {};

		virtual void Update() = 0;

		virtual void Draw();

		//=================================================================
		// [ Enemyが画面の左に過ぎたかどうかをチェックする関数 ]
		//
		// [ Return ]
		// bool :　画面の左にでたらtrueを返す
		//=================================================================
		virtual bool IsOutsideScreen();
};

//*****************************************************************************
// EnemyStraight Class
//
// [ Details ]
// 左に移動する敵
//*****************************************************************************
class EnemyStraight: public Enemy
{
	public:

		EnemyStraight(float posX, float posY);

		virtual ~EnemyStraight() {};

		virtual void Update();

//=========================================================================

	public:
		static LPDIRECT3DTEXTURE9 texture_source_;

	private:
		static const float speedX_;
};

//*****************************************************************************
// EnemyFast Class
//
// [ Details ]
// 速い速度で左に移動する敵
//*****************************************************************************
class EnemyFast: public EnemyStraight
{
	public:
		EnemyFast(float posX, float posY);

		void Update();

//=========================================================================

	public:
		static LPDIRECT3DTEXTURE9 texture_source_;

	private:
		static const float speedX_;
};

//*****************************************************************************
// EnemyCurve Class
//
// [ Details ]
// 曲線で左に移動する敵
//*****************************************************************************
class EnemyCurve : public Enemy
{
	private:
		float angle_; //　Y方向のスピードを変更する角度

	public:
		EnemyCurve(float posX, float posY);

		void Update();

//=========================================================================
	
	public:
		static LPDIRECT3DTEXTURE9 texture_source_;

	private:
		static const float speedX_;
};

//*****************************************************************************
// EnemyPolyline Class
//
// [ Details ]
// 左上方向に移動する敵、画面の端にぶつかったらY方向を変える
//*****************************************************************************
class EnemyPolyline : public Enemy
{
	private:
		float speedY_;

	public:
		EnemyPolyline(float posX, float posY);

		void Update();

//=========================================================================

	public:
		static LPDIRECT3DTEXTURE9 texture_source_;

	private:
		static const float speedX_;
};
#endif