//=================================================================================
//
//    Enemy header
//    Author : Lin He                                �쐬�� : 2018/09/15
//
//=================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../Base/DirectX9.h"

//*****************************************************************************
// �񋓌^�錾
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
		// [float]			posX, posY   :	Enemy�̏������W
		//=================================================================
		Enemy(float posX, float posY);

		virtual ~Enemy() {};

		virtual void Update() = 0;

		virtual void Draw();

		//=================================================================
		// [ Enemy����ʂ̍��ɉ߂������ǂ������`�F�b�N����֐� ]
		//
		// [ Return ]
		// bool :�@��ʂ̍��ɂł���true��Ԃ�
		//=================================================================
		virtual bool IsOutsideScreen();
};

//*****************************************************************************
// EnemyStraight Class
//
// [ Details ]
// ���Ɉړ�����G
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
// �������x�ō��Ɉړ�����G
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
// �Ȑ��ō��Ɉړ�����G
//*****************************************************************************
class EnemyCurve : public Enemy
{
	private:
		float angle_; //�@Y�����̃X�s�[�h��ύX����p�x

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
// ��������Ɉړ�����G�A��ʂ̒[�ɂԂ�������Y������ς���
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