//=================================================================================
//
//    Pen header
//    Author : Lin He                                作成日 : 2018/09/18
//
//=================================================================================

#ifndef _PEN_H_
#define _PEN_H_

#include "../Base/DirectX9.h"
#include "../Base/sound.h"

#include <deque>
#include <vector>

//*****************************************************************************
// 構造体定義
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
		// [ ペンポイント生成関数 ]
		// [ Parameters ]
		// [ float ]	x, y    : 追加するペンポイントの座標
		//=================================================================
		void CreatePenPoint(float x, float y);

		//=================================================================
		// [ 先頭ペンポイント削除関数 ]
		//
		// [ Details ]
		// 現在リストの中、先頭のペンポイントを削除する
		//=================================================================
		void DestoryFirstPenPoint();

		//=================================================================
		// [ 全ペンポイント削除関数 ]
		//=================================================================
		void DestoryAllPenPoint();

		//=================================================================
		// [ コリジョンポイント生成関数 ]
		//
		// [Parameters]
		// [D3DXVECTOR2] pos : 作成するコリジョンポイントの座標
		//=================================================================
		void CreateCollisionPoint(D3DXVECTOR2 pos);

		//=================================================================
		// [ 全コリジョンポイント削除関数 ]
		//=================================================================
		void DestoryAllCollisionPoint();

		//=================================================================
		// [ 線分と線分の衝突判定関数 ]
		//
		// [ Parameters ]
		// [D3DXVECTOR2]	vA_start,vA_end	: 線分Aの起点、終点座標
		// [D3DXVECTOR2]	vB_start,vB_end	: 線分Bの起点、終点座標
		// [D3DXVECTOR2*]	output_intersection	: 交差点座標（アウトプット用）
		//
		// [ Return ]
		// bool : 線分Aと線分Bが交差したらtrueを返す
		//=================================================================
		bool CollisionSegments(D3DXVECTOR2 vA_start, D3DXVECTOR2 vA_end,
							D3DXVECTOR2 vB_start, D3DXVECTOR2 vB_end,
							D3DXVECTOR2* output_intersection = NULL);

		//=================================================================
		// [ 線分と円の衝突判定関数 ]
		//
		// [ Parameters ]
		// [D3DXVECTOR2]	v_start,v_end	: 線分の起点、終点座標
		// [D3DXVECTOR2]	pos_circle		: 円の中心座標
		// [float]			r				: 円の半径
		//
		// [ Return ]
		// bool : 線分と円が交差したらtrueを返す
		//=================================================================
		bool CollisionSegmentAndCircle(D3DXVECTOR2 v_start, D3DXVECTOR2 v_end,
										D3DXVECTOR2 pos_circle, float r);

		//=================================================================
		// [ 点がコリジョンポイントで構成されたポリゴン円にあるかをチェックする関数 ]
		//
		// [ Parameters ]
		// [D3DXVECTOR2]	pos	: チェックする座標
		//
		// [ Return ]
		// bool : posがコリジョンポイントで構成されたポリゴン円にあったらtrueを返す
		//=================================================================
		bool CheckPosIsInCollisionArea(D3DXVECTOR2 pos);
};
#endif