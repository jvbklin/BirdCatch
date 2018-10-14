//=================================================================================
//
//    Pen cpp
//    Author : Lin He                                作成日 : 2018/09/18
//
//=================================================================================

#include "Pen.h"

#include "../main.h"
#include "../Base/Texture.h"
#include "../Base/input.h"
#include "../Base/sound.h"

#include "../Base/Vector2.h"

#include "GameManager.h"
#include "EnemyManager.h"

//*****************************************************************************
// ネームスペース宣言
//*****************************************************************************
using std::deque;
using std::vector;

//*****************************************************************************
// 定数定義
//*****************************************************************************
const int PEN_POINT_WIDTH = 8;
const int PEN_POINT_HEIGHT = 8;
const int PEN_POINT_WIDTH_HALF = PEN_POINT_WIDTH / 2;
const int PEN_POINT_HEIGHT_HALF = PEN_POINT_HEIGHT / 2;

const int PEN_LINE_WIDTH = 8;
const int PEN_LINE_WIDTH_HALF = PEN_LINE_WIDTH / 2;

const int PEN_POINT_TOUCH_COUNT_MAX = 0;

//=================================================================
// [ Pen初期化関数 ]
//=================================================================
void Pen::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	//PenPoint Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/blue_point.png", &pen_point_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"PenPointテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	//PenLine Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/pen_line.png", &pen_line_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"PenLineテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}

	//SoundManager::Load("rom:/data/se.wav");

	pen_point_touch_count_ = 0;

	posX_old_ = 0;
	posY_old_ = 0;
}

//=================================================================
// [ Pen終了処理s関数 ]
//=================================================================
void Pen::Uninit()
{
	pen_point_texture_->Release();
	pen_point_texture_ = NULL;

	pen_line_texture_->Release();
	pen_line_texture_ = NULL;
}

//=================================================================
// [ Pen更新関数 ]
//=================================================================
void Pen::Update()
{
	float posX, posY;

	// マウス取得
	CInputMouse* pInputMouse = GetMouse();

	//スクリーンにタッチしてる間にpen_point_countをカウンターアップ
	if (pInputMouse->GetLeftPress())
	{
		pen_point_touch_count_++;

		//pen_point_countがリミットに達したら点をチェックする
		if (pen_point_touch_count_ >= PEN_POINT_TOUCH_COUNT_MAX)
		{
			POINT* mousePos = pInputMouse->GetPosWorld();
			HWND window = GetWindow();
			ScreenToClient(window, mousePos);

			posX = mousePos->x;
			posY = mousePos->y;

			//画面の中にタッチしている
			if (posX > 0 && posX < SCREEN_WIDTH && posY > 0 && posY < SCREEN_HEIGHT)
			{
				//タッチする場所と前回の位置が違う場合だけペンポイントを生成する
				if (posX != posX_old_ || posY != posY_old_)
				{
					CreatePenPoint(posX, posY);
				}
			}
			//画面の外に出たら全ペンポイントを削除する
			else
			{
				PlaySound(SOUND_SE_BREAK);
				DestoryAllPenPoint();
			}

			posX_old_ = posX;
			posY_old_ = posY;

			pen_point_touch_count_ = 0;
		}
	}
	//スクリーンにタッチしてなかったら全部の点を消す
	else
	{
		pen_point_touch_count_ = 0;
		DestoryAllPenPoint();
	}

	//線の点の数が50以上になったら最初描いた点を消す
	if (pen_points_.size() > 50)
	{
		DestoryFirstPenPoint();
	}

	//線と敵がぶつかったかどうかを判定する
	for (unsigned int i = 1; i < pen_points_.size(); i++)
	{
		D3DXVECTOR2 pos_start = pen_points_[i - 1]->vpos;
		D3DXVECTOR2 pos_end = pen_points_[i]->vpos;

		//list<ENEMY*>::iterator itr = GetEnemyList().begin();
		for (list<Enemy*>::iterator itr = EnemyManager::GetEnemyList().begin(); itr != EnemyManager::GetEnemyList().end(); itr++)
		{
			//D3DXVECTOR2((*itr)->posX_, (*itr)->posY_);
			D3DXVECTOR2 enemy_pos = D3DXVECTOR2((*itr)->posX_, (*itr)->posY_);

			//敵とぶつかった
			if (CollisionSegmentAndCircle(pos_start, pos_end, enemy_pos, 32))
			{
				DestoryAllPenPoint();
				DestoryAllCollisionPoint();

				//GameManager::Instance().DamageLife(1);
				GameManager::Instance().AddScore(-50);
				PlaySound(SOUND_SE_BREAK);

				return;
			}
		}
	}

	//ペンポイントの数が4以上だったらポリゴンの円を構成する可能性がある
	if (pen_points_.size() > 4)
	{
		//線が交差したかどうかを判定するのは逆順で３つ目の点から２つ目の点に引いた線分
		D3DXVECTOR2 secnode_last_pos = pen_points_[pen_points_.size() - 3]->vpos;
		D3DXVECTOR2 last_pos = pen_points_[pen_points_.size() - 2]->vpos;

		bool isCollide = false;

		for (unsigned int i = 1; i < pen_points_.size() - 3; i++)
		{
			D3DXVECTOR2 pos_start = pen_points_[i - 1]->vpos;
			D3DXVECTOR2 pos_end = pen_points_[i]->vpos;

			D3DXVECTOR2 intersection_point;

			//////直前に描いた線分がその前に描いた任意の線分と交差したら、isCollideはTRUE
			//////また、交差点の値ををintersection_pointに与える
			isCollide = CollisionSegments(secnode_last_pos, last_pos, pos_start, pos_end, &intersection_point);

			//線が交差したら
			if (isCollide)
			{


				//////当たり判定をとる点を登録
				for (unsigned int j = i; j < pen_points_.size() - 2; j++)
				{
					CreateCollisionPoint(pen_points_[j]->vpos);
				}
				CreateCollisionPoint(intersection_point);

				//////敵と当たり判定をとる
				D3DXVECTOR2 enemyPos;
				bool isInArea;

				for (list<Enemy*>::iterator itr = EnemyManager::GetEnemyList().begin(); itr != EnemyManager::GetEnemyList().end();)
				{
					D3DXVECTOR2 enemy_pos = D3DXVECTOR2((*itr)->posX_, (*itr)->posY_);

					//この敵がコリジョンのポリゴンの中にいるかどうかをチェック
					isInArea = CheckPosIsInCollisionArea(enemy_pos);

					//この敵がコリジョンのポリゴンの中にいったら
					if (isInArea)
					{
						//スコアアップ
						GameManager::Instance().AddScore(500);
						PlaySound(SOUND_SE_GET);

						//この敵を削除する
						EnemyManager::DestoryEnemy(itr);
					}
					else {
						itr++;
					}
				}

				//////当たり判定を判定する点をクリア
				DestoryAllCollisionPoint();

				///////円形の線分を消す
				for (unsigned int j = i; j < pen_points_.size() - 1; j++)
				{
					delete pen_points_[j];
				}
				pen_points_.erase(pen_points_.begin() + i, pen_points_.end() - 1);

				///////交差点を最後第二の点として追加する
				PEN_POINT* intersection_pen_point = new PEN_POINT;
				intersection_pen_point->vpos = intersection_point;
				intersection_pen_point->count = 0;

				pen_points_.insert(pen_points_.end() - 1, intersection_pen_point);

				break;
			}
		}
	}
}

//=================================================================
// [ Pen描画関数 ]
//=================================================================
void Pen::Draw()
{
	//　点を描画する
	SetTexture(pen_point_texture_);
	for (unsigned int i = 0; i < pen_points_.size(); i++)
	{
		DrawSprite(pen_points_[i]->vpos.x, pen_points_[i]->vpos.y, 
					PEN_POINT_WIDTH_HALF, PEN_POINT_HEIGHT_HALF);
	}

	//線を描画する
	SetTexture(pen_line_texture_);
	for (unsigned int i = 1; i < pen_points_.size(); i++)
	{
		DrawPolygonLine(pen_points_[i - 1]->vpos, pen_points_[i]->vpos);
	}
}

//=================================================================
// [ ペンポイント生成関数 ]
//=================================================================
void Pen::CreatePenPoint(float x, float y)
{
	D3DXVECTOR2 end_point = D3DXVECTOR2(x, y);

	PEN_POINT* pen_point = new PEN_POINT;
	pen_point->vpos = end_point;
	pen_point->count = 0;

	pen_points_.push_back(pen_point);
}

//=================================================================
// [ 先頭ペンポイント削除関数 ]
//=================================================================
void Pen::DestoryFirstPenPoint()
{
	delete *(pen_points_.begin());
	pen_points_.pop_front();
}

//=================================================================
// [ 全ペンポイント削除関数 ]
//=================================================================
void Pen::DestoryAllPenPoint()
{
	for (unsigned int i = 0; i < pen_points_.size(); i++)
	{
		delete pen_points_[i];
	}
	pen_points_.clear();
}

//=================================================================
// [ コリジョンポイント生成関数 ]
//=================================================================
void Pen::CreateCollisionPoint(D3DXVECTOR2 pos)
{
	D3DXVECTOR2* collision_pos = new D3DXVECTOR2(pos.x, pos.y);
	collision_points_.push_back(collision_pos);
}

//=================================================================
// [ 全コリジョンポイント削除関数 ]
//=================================================================
void Pen::DestoryAllCollisionPoint()
{
	for (unsigned int i = 0; i < collision_points_.size(); i++)
	{
		delete collision_points_[i];
	}
	collision_points_.clear();
}

//=================================================================
// [ 線分の衝突判定関数 ]
//=================================================================
bool Pen::CollisionSegments(D3DXVECTOR2 vA_start, D3DXVECTOR2 vA_end, D3DXVECTOR2 vB_start, D3DXVECTOR2 vB_end, D3DXVECTOR2* output_intersection)
{
	if ((vA_start == vB_end) || (vA_end == vB_start))
		return false;

	D3DXVECTOR2 vA = vA_end - vA_start;
	D3DXVECTOR2 vB = vB_end - vB_start;

	D3DXVECTOR2 v = vB_start - vA_start;

	float cross_vA_vB = Vec2Cross(vA, vB);
	if (cross_vA_vB == 0.0f) {
		// 平行状態
		return false;
	}

	float cross_v_vA = Vec2Cross(v, vA);
	float cross_v_vB = Vec2Cross(v, vB);

	float t1 = cross_v_vB / cross_vA_vB;
	float t2 = cross_v_vA / cross_vA_vB;

	if (t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1)
	{
		// 交差していない
		return false;
	}

	if (output_intersection)
		*output_intersection = vA_start + vA * t1;

	return true;
}

//=================================================================
// [ 線分と円の衝突判定関数 ]
//
//		  pos_circle
//		      /|\
//		vA	 / | \ vB
//			/  |  \
//		   ---------
// v_start	   v     v_end
//=================================================================
bool Pen::CollisionSegmentAndCircle(D3DXVECTOR2 v_start, D3DXVECTOR2 v_end, D3DXVECTOR2 pos_circle, float r)
{
	D3DXVECTOR2 v = v_end - v_start;

	D3DXVECTOR2 vA = pos_circle - v_start;

	float v_magnitude = Vec2Magnitude(v);

	if (v_magnitude <= 0.5f)
		return false;

	float cross_v_vA_magnitude = Vec2Magnitude(Vec2Cross(v, vA));

	float distance = cross_v_vA_magnitude / v_magnitude;

	if (distance > r)
		return false;

	D3DXVECTOR2 vB = pos_circle - v_end;

	if (Vec2Dot(vA, v) * Vec2Dot(vB, v) <= 0)
		return true;

	float vA_magnitude = Vec2Magnitude(vA);
	if (vA_magnitude < r)
		return true;

	float vB_magnitude = Vec2Magnitude(vB);
	if (vB_magnitude < r)
		return true;

	return false;
}

//=================================================================
// [ 点がコリジョンポイントで構成されたポリゴン円にあるかをチェックする関数 ]
//=================================================================
bool Pen::CheckPosIsInCollisionArea(D3DXVECTOR2 check_pos)
{
	D3DXVECTOR2 outline_line;
	D3DXVECTOR2 to_enemy_line;

	bool outer_product_dir;

	bool isInArea = true;

	outline_line = *collision_points_.front() - *collision_points_.back();
	to_enemy_line = check_pos - *collision_points_.front();

	outer_product_dir = Vec2Cross(outline_line, to_enemy_line) > 0 ? true : false;

	for (unsigned int i = 0; i < collision_points_.size() - 1; i++)
	{
		outline_line = *collision_points_[i + 1] - *collision_points_[i];
		to_enemy_line = check_pos - *collision_points_[i + 1];

		bool dir = Vec2Cross(outline_line, to_enemy_line) > 0 ? true : false;

		if (outer_product_dir != dir)
		{
			isInArea = false;
			break;
		}
	}

	return isInArea;
}