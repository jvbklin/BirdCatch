//=================================================================================
//
//    Background header
//    Author : Lin He                                �쐬�� : 2018/09/15
//
//=================================================================================

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "../Base/DirectX9.h"
#include "../main.h"

//*****************************************************************************
// Background Class
//*****************************************************************************
class Background {

	protected:
		LPDIRECT3DTEXTURE9 texture_;
		float width_;
		float height_;

	public:
		//=================================================================
		// [ Background Constructor ]
		//
		// [ Parameters ]
		// [LPDIRECT3DTEXTURE9]	texture			: �w�i�e�N�X�`���[�|�C���^
		// [float]				width, height   : �w�i�̕��A����
		//=================================================================
		Background(LPDIRECT3DTEXTURE9 texture, float width = SCREEN_WIDTH, float height = SCREEN_HEIGHT);
		
		virtual ~Background();

		virtual void Update() {};

		virtual void Draw();
};

//*****************************************************************************
// HorizontalScrollBackground Class
//
// [Details]
// ���ɂ��񂾂�ړ����A�E�ɓ����w�i��`�悷��A�V�[�����X�w�i�Ɏg��
//*****************************************************************************
class HorizontalScrollBackground : public Background {

	public:
		float posX;

	public:
		//=================================================================
		// [ HorizontalScrollBackground Constructor ]
		//
		// [ Parameters ]
		// [LPDIRECT3DTEXTURE9]	texture			: �w�i�e�N�X�`���[�|�C���^
		// [float]				width, height   : �w�i�̕��A����
		//=================================================================
		HorizontalScrollBackground(LPDIRECT3DTEXTURE9 texture, float width = SCREEN_WIDTH, float height = SCREEN_HEIGHT);
		
		void Update();

		void Draw();
};

#endif