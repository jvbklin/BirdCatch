//=================================================================================
//
//    Background cpp
//    Author : Lin He                                çÏê¨ì˙ : 2018/09/15
//
//=================================================================================

#include "Background.h"

#include "../main.h"
#include "../Base/Texture.h"

//=================================================================
// [ Background Constructor ]
//=================================================================
Background::Background(LPDIRECT3DTEXTURE9 texture, float width, float height)
{
	texture_ = texture;

	width_ = width;
	height_ = height;
}

//=================================================================
// [ Background Destructor ]
//=================================================================
Background::~Background()
{
	texture_->Release();
	texture_ = NULL;
}

//=================================================================
// [ Background ï`âÊä÷êî ]
//=================================================================
void Background::Draw()
{
	SetTexture(texture_);
	DrawTextureRect(0.0f, width_, 0.0f, height_);
}

//=================================================================
// [ HorizontalScrollBackground Constructor ]
//=================================================================
HorizontalScrollBackground::HorizontalScrollBackground(LPDIRECT3DTEXTURE9 texture, float width, float height)
	: Background(texture, width, height)
{
	posX = 0.0f;
}

//=================================================================
// [ HorizontalScrollBackground çXêVä÷êî ]
//=================================================================
void HorizontalScrollBackground::Update() 
{
	posX -= 1.0f;

	if (posX <= -SCREEN_WIDTH)
	{
		posX = 0.0f;
	}
}

//=================================================================
// [ HorizontalScrollBackground ï`âÊä÷êî ]
//=================================================================
void HorizontalScrollBackground::Draw()
{
	SetTexture(texture_);

	DrawTextureRect(posX		 , posX + width_,		   0.0f,  height_);
	DrawTextureRect(posX + width_, posX + width_ + width_, 0.0f,  height_);
}