//=================================================================================
//
//    Background header
//    Author : Lin He                                作成日 : 2018/09/15
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
		// [LPDIRECT3DTEXTURE9]	texture			: 背景テクスチャーポインタ
		// [float]				width, height   : 背景の幅、高さ
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
// 左にだんだん移動し、右に同じ背景を描画する、シームレス背景に使う
//*****************************************************************************
class HorizontalScrollBackground : public Background {

	public:
		float posX;

	public:
		//=================================================================
		// [ HorizontalScrollBackground Constructor ]
		//
		// [ Parameters ]
		// [LPDIRECT3DTEXTURE9]	texture			: 背景テクスチャーポインタ
		// [float]				width, height   : 背景の幅、高さ
		//=================================================================
		HorizontalScrollBackground(LPDIRECT3DTEXTURE9 texture, float width = SCREEN_WIDTH, float height = SCREEN_HEIGHT);
		
		void Update();

		void Draw();
};

#endif