//=================================================================================
//
//    Vector2 header
//    Author : Lin He                                �쐬�� : 2018/09/18
//
//=================================================================================

#include "Vector2.h"

//=================================================================
// [ 2D�O�ρi���ہj�֐� ]
//=================================================================
float Vec2Cross(const D3DXVECTOR2 v1, const D3DXVECTOR2 v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

//=================================================================
// [ 2D���ϊ֐� ]
//=================================================================
float Vec2Dot(const D3DXVECTOR2 v1, const D3DXVECTOR2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

//=================================================================
// [ 2D�x�N�^�[�傫���֐� ]
//=================================================================
float Vec2Magnitude(const D3DXVECTOR2 v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

//=================================================================
// [ 2D�x�N�^�[�傫���֐� ]
//=================================================================
float Vec2Magnitude(const float v_one_way)
{
	if (v_one_way < 0)
		return -v_one_way;
	return v_one_way;
}

//=================================================================
// [ �_���l�p�`�̒��ɂ��邩���`�F�b�N����֐� ]
//=================================================================
bool IsInRectangle(const D3DXVECTOR2 pos, const float left, const float right, const float up, const float down)
{
	// Collision x-axis
	bool collisionX = (pos.x < right) && (pos.x > left);
	// Collision y-axis
	bool collisionY = (pos.y < down) && (pos.y > up);
	// Collision only if on both axes
	return collisionX && collisionY;
}