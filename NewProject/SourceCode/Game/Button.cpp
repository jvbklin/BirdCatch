//=================================================================================
//
//    Button cpp
//    Author : Lin He                                作成日 : 2018/10/13
//
//=================================================================================
#include "Button.h"

#include "../Base/Texture.h"

//=================================================================
// [ RectButton Constructor ]
//=================================================================
RectButton::RectButton(LPDIRECT3DTEXTURE9 texture, float posX, float posY,
													float width_half, float height_half)
{
	texture_ = texture;

	posX_ = posX;
	posY_ = posY;
	width_half_ = width_half;
	height_half_ = height_half;
}

//=================================================================
// [ RectButton Destructor ]
//=================================================================
RectButton::~RectButton()
{
	texture_->Release();
	texture_ = NULL;
}

//=================================================================
// [ チェック座標がこのボタンの範囲内かどうか ]
//=================================================================
bool RectButton::PosIsInButton(float x, float y)
{
	if (x < posX_ - width_half_ || x > posX_ + width_half_)
		return false;
	if (y < posY_ - height_half_ || y > posY_ + height_half_)
		return false;
	return true;
}

//=================================================================
// [ RectButton 描画関数 ]
//=================================================================
void RectButton::Draw()
{
	SetTexture(texture_);
	//DrawTextureRect(left_pos_, right_pos_, up_pos_, down_pos_);
	DrawSprite(posX_, posY_, width_half_, height_half_);
}

//=================================================================
// [ StartButton Constructor ]
//=================================================================
StartButton::StartButton(LPDIRECT3DTEXTURE9 texture, float posX, float posY, float width_half, float height_half)
	:RectButton(texture, posX, posY, width_half, height_half)
{
	animation_count_ = 0;
	animation_index_ = 0;
}

//=================================================================
// [ StartButton 更新関数 ]
//=================================================================
void StartButton::Update()
{
	animation_count_++;
	if (animation_count_ > 10)
	{
		animation_count_ = 0;

		animation_index_++;
		if (animation_index_ > 1)
			animation_index_ = 0;
	}
}

//=================================================================
// [ StartButton 描画関数 ]
//=================================================================
void StartButton::Draw()
{
	SetTexture(texture_);

	DrawSprite(posX_, posY_, width_half_, height_half_,
				0.0f, 0.5f * animation_index_,
				1.0f, 0.5f * animation_index_ + 0.5f);
}