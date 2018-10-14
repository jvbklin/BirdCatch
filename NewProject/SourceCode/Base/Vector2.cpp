//=================================================================================
//
//    Vector2 header
//    Author : Lin He                                作成日 : 2018/09/18
//
//=================================================================================

#include "Vector2.h"

//=================================================================
// [ 2D外積（抽象）関数 ]
//=================================================================
float Vec2Cross(const D3DXVECTOR2 v1, const D3DXVECTOR2 v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

//=================================================================
// [ 2D内積関数 ]
//=================================================================
float Vec2Dot(const D3DXVECTOR2 v1, const D3DXVECTOR2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

//=================================================================
// [ 2Dベクター大きさ関数 ]
//=================================================================
float Vec2Magnitude(const D3DXVECTOR2 v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

//=================================================================
// [ 2Dベクター大きさ関数 ]
//=================================================================
float Vec2Magnitude(const float v_one_way)
{
	if (v_one_way < 0)
		return -v_one_way;
	return v_one_way;
}

//=================================================================
// [ 点が四角形の中にあるかをチェックする関数 ]
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