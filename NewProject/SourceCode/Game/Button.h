//=================================================================================
//
//    Button header
//    Author : Lin He                                �쐬�� : 2018/10/13
//
//=================================================================================

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "../Base/DirectX9.h"

//*****************************************************************************
// RectButton Class
//*****************************************************************************
class RectButton{

	protected:
		LPDIRECT3DTEXTURE9 texture_;
		float posX_;
		float posY_;
		float width_half_;
		float height_half_;

	public:
		RectButton(LPDIRECT3DTEXTURE9 texture, float posX, float posY,
												float width_half_, float height_half_);
		virtual ~RectButton();

		//=================================================================
		// [ �`�F�b�N���W�����̃{�^���͈͓̔����ǂ��� ]
		//
		// [ Parameters ]
		// [ float ]		x, y	:	���W
		//
		// [ Return ]
		// [ bool ] �@���W���{�^���͈͓̔���������true��Ԃ�
		//=================================================================
		virtual bool PosIsInButton(float x, float y);

		virtual void Draw();
};
 
//*****************************************************************************
// StartButton Class
//*****************************************************************************
class StartButton : public RectButton{

	private:
		int animation_count_;
		int animation_index_;

	public:
		StartButton(LPDIRECT3DTEXTURE9 texture, float posX, float posY,
												float width_half_, float height_half_);
		void Update();
		void Draw();
};

#endif