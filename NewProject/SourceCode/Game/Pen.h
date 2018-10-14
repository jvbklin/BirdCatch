//=================================================================================
//
//    Pen header
//    Author : Lin He                                �쐬�� : 2018/09/18
//
//=================================================================================

#ifndef _PEN_H_
#define _PEN_H_

#include "../Base/DirectX9.h"
#include "../Base/sound.h"

#include <deque>
#include <vector>

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct {
	D3DXVECTOR2 vpos;
	bool bPenPoint;
	int count;
}PEN_POINT;

//*****************************************************************************
// Pen Class
//*****************************************************************************
class Pen {

	private:
		LPDIRECT3DTEXTURE9 pen_point_texture_;
		LPDIRECT3DTEXTURE9 pen_line_texture_;

		int pen_point_touch_count_;
		float posX_old_, posY_old_;

		std::deque<PEN_POINT*> pen_points_;
		std::vector<D3DXVECTOR2*> collision_points_;

	public:
		void Init();
		void Uninit();
		void Update();
		void Draw();

	private:
		//=================================================================
		// [ �y���|�C���g�����֐� ]
		// [ Parameters ]
		// [ float ]	x, y    : �ǉ�����y���|�C���g�̍��W
		//=================================================================
		void CreatePenPoint(float x, float y);

		//=================================================================
		// [ �擪�y���|�C���g�폜�֐� ]
		//
		// [ Details ]
		// ���݃��X�g�̒��A�擪�̃y���|�C���g���폜����
		//=================================================================
		void DestoryFirstPenPoint();

		//=================================================================
		// [ �S�y���|�C���g�폜�֐� ]
		//=================================================================
		void DestoryAllPenPoint();

		//=================================================================
		// [ �R���W�����|�C���g�����֐� ]
		//
		// [Parameters]
		// [D3DXVECTOR2] pos : �쐬����R���W�����|�C���g�̍��W
		//=================================================================
		void CreateCollisionPoint(D3DXVECTOR2 pos);

		//=================================================================
		// [ �S�R���W�����|�C���g�폜�֐� ]
		//=================================================================
		void DestoryAllCollisionPoint();

		//=================================================================
		// [ �����Ɛ����̏Փ˔���֐� ]
		//
		// [ Parameters ]
		// [D3DXVECTOR2]	vA_start,vA_end	: ����A�̋N�_�A�I�_���W
		// [D3DXVECTOR2]	vB_start,vB_end	: ����B�̋N�_�A�I�_���W
		// [D3DXVECTOR2*]	output_intersection	: �����_���W�i�A�E�g�v�b�g�p�j
		//
		// [ Return ]
		// bool : ����A�Ɛ���B������������true��Ԃ�
		//=================================================================
		bool CollisionSegments(D3DXVECTOR2 vA_start, D3DXVECTOR2 vA_end,
							D3DXVECTOR2 vB_start, D3DXVECTOR2 vB_end,
							D3DXVECTOR2* output_intersection = NULL);

		//=================================================================
		// [ �����Ɖ~�̏Փ˔���֐� ]
		//
		// [ Parameters ]
		// [D3DXVECTOR2]	v_start,v_end	: �����̋N�_�A�I�_���W
		// [D3DXVECTOR2]	pos_circle		: �~�̒��S���W
		// [float]			r				: �~�̔��a
		//
		// [ Return ]
		// bool : �����Ɖ~������������true��Ԃ�
		//=================================================================
		bool CollisionSegmentAndCircle(D3DXVECTOR2 v_start, D3DXVECTOR2 v_end,
										D3DXVECTOR2 pos_circle, float r);

		//=================================================================
		// [ �_���R���W�����|�C���g�ō\�����ꂽ�|���S���~�ɂ��邩���`�F�b�N����֐� ]
		//
		// [ Parameters ]
		// [D3DXVECTOR2]	pos	: �`�F�b�N������W
		//
		// [ Return ]
		// bool : pos���R���W�����|�C���g�ō\�����ꂽ�|���S���~�ɂ�������true��Ԃ�
		//=================================================================
		bool CheckPosIsInCollisionArea(D3DXVECTOR2 pos);
};
#endif