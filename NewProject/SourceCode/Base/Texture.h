//=================================================================================
//
//    2D�e�N�X�`���[�`�� �w�b�_[Texture.h]
//    Author : Lin He                                �쐬�� : 2017/06/05
//
//=================================================================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "DirectX9.h"

//=================================================================
// [ �e�N�X�`���[�`�揉�����֐� ]
//
// [ Return ]
// bool : ����������������true��Ԃ�
//=================================================================
bool InitTexture(void);

//=================================================================
// [ �e�N�X�`���[�`��I�������֐� ]
//=================================================================
void UninitTexture(void);

//=================================================================
// [ �e�N�X�`���[�`��֐� ]
//
// [ Parameters ]
// [float]	x, y									: �`�悷��l�p�`�̍�����W
// [int]	texture_width, texture_height			: �\�[�X�e�N�X�`���[���ƍ���
// [int]	texture_cut_x, texture_cut_y			: �\�[�X�e�N�X�`���[�̐؂�����W
// [int]	texture_cut_width, texture_cut_width	: �`�悷��e�N�X�`���[�̕��ƍ���
//
// [ Details ]
// ���W(x, y)���l�p�`�̍�����W�ɂ���
// ����texture_width�A������texture_height�̃\�[�X�e�N�X�`���[����
// �e�N�X�`���[���W(texture_cut_x,texture_cut_y)��؂���ɂ���
// ����texture_cut_width�A������texture_cut_height�̎l�p�`�e�N�X�`���[��؂���
// �l�p�`�|���S���ɕ`�悷��
//=================================================================
void DrawTexture(float x, float y, int texture_width, int texture_height, 
									int texture_cut_x, int texture_cut_y,
									int texture_cut_width, int texture_cut_height);

//=================================================================
// [ �e�N�X�`���[�`��̒��_���o�^�֐� ]
//
// [ Parameters ]
// [float]	x, y									: �`�悷��l�p�`�̍�����W
// [int]	texture_width, texture_height			: �\�[�X�e�N�X�`���[���ƍ���
// [int]	texture_cut_x, texture_cut_y			: �\�[�X�e�N�X�`���[�̐؂�����W
// [int]	texture_cut_width, texture_cut_width	: �`�悷��e�N�X�`���[�̕��ƍ���
//
// [ Details ]
// �`�悷��l�p�`�|���S���̍��W�ƃe�N�X�`���[���W��o�^����
//=================================================================
void CreateVertex(float x, float y, int texture_width, int texture_height,
									int texture_cut_x, int texture_cut_y,
									int texture_cut_width, int texture_cut_height);

//=================================================================
// [ �l�p�`�e�N�X�`���[�`��֐� ]
//
// [ Parameters ]
// [float]	left	: �`�悷��l�p�`�̍����W
// [float]	right	: �`�悷��l�p�`�̉E���W
// [float]	up		: �`�悷��l�p�`�̏���W
// [float]	down	: �`�悷��l�p�`�̉����W
//
// [ Details ]
// �l�p�`�|���S���Ƀ\�[�X�e�N�X�`���[�����̂܂ܕ`�悷��A�����͔w�i�`��Ɏg����
//=================================================================
void DrawTextureRect(float left, float right, float up, float down);

//=================================================================
// [ �l�p�`�e�N�X�`���[�`��̒��_���o�^�֐� ]
//
// [ Parameters ]
// [float]	left	: �`�悷��l�p�`�̍����W
// [float]	right	: �`�悷��l�p�`�̉E���W
// [float]	up		: �`�悷��l�p�`�̏���W
// [float]	down	: �`�悷��l�p�`�̉����W
//
// [ Details ]
// �`�悷��l�p�`�|���S���ƃe�N�X�`���[���W��o�^����
//=================================================================
void CreateVertexRect(float left, float right, float up, float down);

//=================================================================
// [ �e�N�X�`���[�ݒu�֐� ]
//
// [ Parameters ]
// [LPDIRECT3DTEXTURE9]	texture	: �e�N�X�`���[�|�C���^
//
// [ Details ]
// ����`�悷��e�N�X�`���[��ݒ肷��
//=================================================================
void SetTexture(LPDIRECT3DTEXTURE9 texture);

//=================================================================
// [ �e�N�X�`���[�J���[�ݒu�֐� ]
//
// [ Parameters ]
// [D3DCOLOR]	color	: �F
//
// [ Details ]
// ����`�悷��e�N�X�`���[�J���[��ݒ肷��
//=================================================================
void SetTextureColor(D3DCOLOR color);

//=================================================================
// [ �e�N�X�`���[�X�P�[���ݒu�֐� ]
//
// [ Parameters ]
// [float]	scaleX	: ���T�C�Y
// [float]	scaleY	: �����T�C�Y
//
// [ Details ]
// ����`�悷��e�N�X�`���[�X�P�[����ݒ肷��(DrawTexture�����e������)
//=================================================================
void SetTextureScale(float scaleX, float scaleY);

//=================================================================
// [ �X�v���C�g�`��֐� ]
//
// [ Parameters ]
// [float]	x,y 				: �`�悷��X�v���C�g���W
// [int]	sprite_width_half	: �`�悷��X�v���C�g�̕��̔���
// [int]	sprite_height_half	: �`�悷��X�v���C�g�̍����̔���
// [float]	texcoord_left		: �`�悷��X�v���C�g�̍�UV���W
// [float]	texcoord_up			: �`�悷��X�v���C�g�̏�UV���W
// [float]	texcoord_right		: �`�悷��X�v���C�g�̉EUV���W
// [float]	texcoord_down		: �`�悷��X�v���C�g�̉�UV���W
//
// [ Details ]
// ���W(x,y)�𒆐S�ɂ��āA
// ����sprite_width_half��2�{�A������sprite_height_half��2�{�̎l�p�`�|���S����
// UV���W�ɏ]���ăe�N�X�`���[��`�悷��
//=================================================================
void DrawSprite(float x, float y, int sprite_width_half, int sprite_height_half,
								  float texcoord_left  = 0.0f, float texcoord_up = 0.0f,
								  float texcoord_right = 1.0f, float texcoord_down = 1.0f);

//=================================================================
// [ �X�v���C�g�`��̒��_���o�^�֐� ]
//
// [ Parameters ]
// [float]	x,y 				: �`�悷��X�v���C�g���W
// [int]	sprite_width_half	: �`�悷��X�v���C�g�̕��̔���
// [int]	sprite_height_half	: �`�悷��X�v���C�g�̍����̔���
// [float]	texcoord_left		: �`�悷��X�v���C�g�̍�UV���W
// [float]	texcoord_up			: �`�悷��X�v���C�g�̏�UV���W
// [float]	texcoord_right		: �`�悷��X�v���C�g�̉EUV���W
// [float]	texcoord_down		: �`�悷��X�v���C�g�̉�UV���W
//
// [ Details ]
// �`�悷��X�v���C�g�̃|���S�����W�ƃe�N�X�`���[���W��o�^����
//=================================================================
void CreateVertexSprite(float x, float y, int sprite_width_half, int sprite_height_half,
     									  float texcoord_left, float texcoord_up,
										  float texcoord_right, float texcoord_down);

//=================================================================
// [ �����`��֐� ]
//
// [ Parameters ]
// [D3DXVECTOR2]	pos_start 	: �N�_���W
// [D3DXVECTOR2]	pos_end		: �I�_���W
//
// [ Details ]
// �N�_�ƏI�_�̊Ԃɐ����i�|���S���j��`�悷��
//=================================================================
void DrawPolygonLine(D3DXVECTOR2 pos_start, D3DXVECTOR2 pos_end);

//=================================================================
// [ �|���S�����_���o�^�֐� ]
//
// [ Parameters ]
// [D3DXVECTOR2]	pos_0 	: �|���S�����W0
// [D3DXVECTOR2]	pos_1	: �|���S�����W1
// [D3DXVECTOR2]	pos_2 	: �|���S�����W2
// [D3DXVECTOR2]	pos_3	: �|���S�����W3
//
// [ Details ]
// �|���S�����W��o�^����
//=================================================================
void CreateVertexPolygon(D3DXVECTOR2 pos_0, D3DXVECTOR2 pos_1, D3DXVECTOR2 pos_2, D3DXVECTOR2 pos_3);

#endif