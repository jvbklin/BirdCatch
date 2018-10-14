//=================================================================================
//
//    Vector2 header
//    Author : Lin He                                �쐬�� : 2018/09/18
//
//=================================================================================

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "DirectX9.h"

//=================================================================
// [ 2D�O�ρi���ہj�֐� ]
//
// [ Parameters ]
// [const D3DXVECTOR2]	v1 	: 2d�x�N�^�[1
// [const D3DXVECTOR2]	v2	: 2d�x�N�^�[2
//
// [ Rerurn ]
// float : �x�N�^�[1�ƃx�N�^�[2�̊O��
//=================================================================
float Vec2Cross(const D3DXVECTOR2 v1, const D3DXVECTOR2 v2);

//=================================================================
// [ 2D���ϊ֐� ]
//
// [ Parameters ]
// [const D3DXVECTOR2]	v1 	: 2d�x�N�^�[1
// [const D3DXVECTOR2]	v2	: 2d�x�N�^�[2
//
// [ Rerurn ]
// float : 2d�x�N�^�[1��2d�x�N�^�[2�̓���
//=================================================================
float Vec2Dot(const D3DXVECTOR2 v1, const D3DXVECTOR2 v2);

//=================================================================
// [ 2D�x�N�^�[�傫���֐� ]
//
// [ Parameters ]
// [const D3DXVECTOR2]	v 	: 2d�x�N�^�[
//
// [ Rerurn ]
// float : 2d�x�N�^�[�̑傫��
//=================================================================
float Vec2Magnitude(const D3DXVECTOR2 v);

//=================================================================
// [ 2D�x�N�^�[�傫���֐� ]
//
// [ Parameters ]
// [const float]	v_one_way 	: 2d�P�����x�N�^�[
//
// [ Rerurn ]
// float : ����v_one_way���}�C�i�X�������炻�̔�����Ԃ�
//=================================================================
float Vec2Magnitude(const float v_one_way);

//=================================================================
// [ �_���l�p�`�̒��ɂ��邩���`�F�b�N����֐� ]
//=================================================================
bool IsInRectangle(const D3DXVECTOR2 pos, const float left, const float right, const float up, const float down);
#endif