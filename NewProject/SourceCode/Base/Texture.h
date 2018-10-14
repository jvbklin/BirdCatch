//=================================================================================
//
//    2Dテクスチャー描画 ヘッダ[Texture.h]
//    Author : Lin He                                作成日 : 2017/06/05
//
//=================================================================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "DirectX9.h"

//=================================================================
// [ テクスチャー描画初期化関数 ]
//
// [ Return ]
// bool : 初期化成功したらtrueを返す
//=================================================================
bool InitTexture(void);

//=================================================================
// [ テクスチャー描画終了処理関数 ]
//=================================================================
void UninitTexture(void);

//=================================================================
// [ テクスチャー描画関数 ]
//
// [ Parameters ]
// [float]	x, y									: 描画する四角形の左上座標
// [int]	texture_width, texture_height			: ソーステクスチャー幅と高さ
// [int]	texture_cut_x, texture_cut_y			: ソーステクスチャーの切り口座標
// [int]	texture_cut_width, texture_cut_width	: 描画するテクスチャーの幅と高さ
//
// [ Details ]
// 座標(x, y)を四角形の左上座標にして
// 幅がtexture_width、高さがtexture_heightのソーステクスチャーから
// テクスチャー座標(texture_cut_x,texture_cut_y)を切り口にして
// 幅がtexture_cut_width、高さがtexture_cut_heightの四角形テクスチャーを切って
// 四角形ポリゴンに描画する
//=================================================================
void DrawTexture(float x, float y, int texture_width, int texture_height, 
									int texture_cut_x, int texture_cut_y,
									int texture_cut_width, int texture_cut_height);

//=================================================================
// [ テクスチャー描画の頂点情報登録関数 ]
//
// [ Parameters ]
// [float]	x, y									: 描画する四角形の左上座標
// [int]	texture_width, texture_height			: ソーステクスチャー幅と高さ
// [int]	texture_cut_x, texture_cut_y			: ソーステクスチャーの切り口座標
// [int]	texture_cut_width, texture_cut_width	: 描画するテクスチャーの幅と高さ
//
// [ Details ]
// 描画する四角形ポリゴンの座標とテクスチャー座標を登録する
//=================================================================
void CreateVertex(float x, float y, int texture_width, int texture_height,
									int texture_cut_x, int texture_cut_y,
									int texture_cut_width, int texture_cut_height);

//=================================================================
// [ 四角形テクスチャー描画関数 ]
//
// [ Parameters ]
// [float]	left	: 描画する四角形の左座標
// [float]	right	: 描画する四角形の右座標
// [float]	up		: 描画する四角形の上座標
// [float]	down	: 描画する四角形の下座標
//
// [ Details ]
// 四角形ポリゴンにソーステクスチャーをそのまま描画する、多くは背景描画に使われる
//=================================================================
void DrawTextureRect(float left, float right, float up, float down);

//=================================================================
// [ 四角形テクスチャー描画の頂点情報登録関数 ]
//
// [ Parameters ]
// [float]	left	: 描画する四角形の左座標
// [float]	right	: 描画する四角形の右座標
// [float]	up		: 描画する四角形の上座標
// [float]	down	: 描画する四角形の下座標
//
// [ Details ]
// 描画する四角形ポリゴンとテクスチャー座標を登録する
//=================================================================
void CreateVertexRect(float left, float right, float up, float down);

//=================================================================
// [ テクスチャー設置関数 ]
//
// [ Parameters ]
// [LPDIRECT3DTEXTURE9]	texture	: テクスチャーポインタ
//
// [ Details ]
// 今後描画するテクスチャーを設定する
//=================================================================
void SetTexture(LPDIRECT3DTEXTURE9 texture);

//=================================================================
// [ テクスチャーカラー設置関数 ]
//
// [ Parameters ]
// [D3DCOLOR]	color	: 色
//
// [ Details ]
// 今後描画するテクスチャーカラーを設定する
//=================================================================
void SetTextureColor(D3DCOLOR color);

//=================================================================
// [ テクスチャースケール設置関数 ]
//
// [ Parameters ]
// [float]	scaleX	: 幅サイズ
// [float]	scaleY	: 高さサイズ
//
// [ Details ]
// 今後描画するテクスチャースケールを設定する(DrawTextureだけ影響する)
//=================================================================
void SetTextureScale(float scaleX, float scaleY);

//=================================================================
// [ スプライト描画関数 ]
//
// [ Parameters ]
// [float]	x,y 				: 描画するスプライト座標
// [int]	sprite_width_half	: 描画するスプライトの幅の半分
// [int]	sprite_height_half	: 描画するスプライトの高さの半分
// [float]	texcoord_left		: 描画するスプライトの左UV座標
// [float]	texcoord_up			: 描画するスプライトの上UV座標
// [float]	texcoord_right		: 描画するスプライトの右UV座標
// [float]	texcoord_down		: 描画するスプライトの下UV座標
//
// [ Details ]
// 座標(x,y)を中心にして、
// 幅がsprite_width_halfの2倍、高さがsprite_height_halfの2倍の四角形ポリゴンに
// UV座標に従ってテクスチャーを描画する
//=================================================================
void DrawSprite(float x, float y, int sprite_width_half, int sprite_height_half,
								  float texcoord_left  = 0.0f, float texcoord_up = 0.0f,
								  float texcoord_right = 1.0f, float texcoord_down = 1.0f);

//=================================================================
// [ スプライト描画の頂点情報登録関数 ]
//
// [ Parameters ]
// [float]	x,y 				: 描画するスプライト座標
// [int]	sprite_width_half	: 描画するスプライトの幅の半分
// [int]	sprite_height_half	: 描画するスプライトの高さの半分
// [float]	texcoord_left		: 描画するスプライトの左UV座標
// [float]	texcoord_up			: 描画するスプライトの上UV座標
// [float]	texcoord_right		: 描画するスプライトの右UV座標
// [float]	texcoord_down		: 描画するスプライトの下UV座標
//
// [ Details ]
// 描画するスプライトのポリゴン座標とテクスチャー座標を登録する
//=================================================================
void CreateVertexSprite(float x, float y, int sprite_width_half, int sprite_height_half,
     									  float texcoord_left, float texcoord_up,
										  float texcoord_right, float texcoord_down);

//=================================================================
// [ 線分描画関数 ]
//
// [ Parameters ]
// [D3DXVECTOR2]	pos_start 	: 起点座標
// [D3DXVECTOR2]	pos_end		: 終点座標
//
// [ Details ]
// 起点と終点の間に線分（ポリゴン）を描画する
//=================================================================
void DrawPolygonLine(D3DXVECTOR2 pos_start, D3DXVECTOR2 pos_end);

//=================================================================
// [ ポリゴン頂点情報登録関数 ]
//
// [ Parameters ]
// [D3DXVECTOR2]	pos_0 	: ポリゴン座標0
// [D3DXVECTOR2]	pos_1	: ポリゴン座標1
// [D3DXVECTOR2]	pos_2 	: ポリゴン座標2
// [D3DXVECTOR2]	pos_3	: ポリゴン座標3
//
// [ Details ]
// ポリゴン座標を登録する
//=================================================================
void CreateVertexPolygon(D3DXVECTOR2 pos_0, D3DXVECTOR2 pos_1, D3DXVECTOR2 pos_2, D3DXVECTOR2 pos_3);

#endif