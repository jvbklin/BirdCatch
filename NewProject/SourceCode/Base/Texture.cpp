//=================================================================================
//
//    2Dテクスチャー描画[Texture.cpp]
//    Author : Lin He                                作成日 : 2017/06/05
//
//=================================================================================

#include "Texture.h"
#include "DirectX9.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D ( D3DFVF_XYZRHW| D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static D3DCOLOR gTextureColor;
static float gTextureScaleX;
static float gTextureScaleY;

//=================================================================
// [ テクスチャー描画初期化関数 ]
//=================================================================
bool InitTexture()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		return false;
	}

	HRESULT hr;

	hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,    /*0でも大丈夫*/
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファが作れなたっか", L"error", MB_OK);
		return false;
	}

	gTextureColor = 0xFFFFFFFF;

	gTextureScaleX = 1.0f;
	gTextureScaleY = 1.0f;

	return true;
}

//=================================================================
// [ テクスチャー描画終了処理関数 ]
//=================================================================
void UninitTexture(void)
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}

//=================================================================
// [ テクスチャー描画関数 ]
//=================================================================
void DrawTexture(float x, float y, int texture_width, int texture_height,
									int texture_cut_x, int texture_cut_y,
									int texture_cut_width, int texture_cut_height)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	CreateVertex(x, y, texture_width, texture_height, 
						texture_cut_x,texture_cut_y, 
						texture_cut_width, texture_cut_height);

	pDevice->SetStreamSource(
		0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_2D)
		);

	//FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//=================================================================
// [ テクスチャー描画の頂点情報登録関数 ]
//=================================================================
void CreateVertex(float x, float y, int texture_width, int texture_height,
	int texture_cut_x, int texture_cut_y,
	int texture_cut_width, int texture_cut_height)
{
	VERTEX_2D* pV;
	/*↓ 0でも大丈夫、０を入れると全部ロックします*/
	g_pVertexBuffer->Lock(0, sizeof(VERTEX_2D) * 4, (void**)&pV, D3DLOCK_DISCARD);

	pV[0].pos = D3DXVECTOR4(x - 0.5f, y - 0.5f, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(x + texture_cut_width * gTextureScaleX - 0.5f, y - 0.5f, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(x - 0.5f, y + texture_cut_height * gTextureScaleY - 0.5f, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(x + texture_cut_width * gTextureScaleX - 0.5f, y + texture_cut_height * gTextureScaleY - 0.5f, 1.0f, 1.0f);

	pV[0].color =
	pV[1].color =
	pV[2].color =
	pV[3].color = gTextureColor;

	float u0 = (float)texture_cut_x / texture_width;
	float v0 = (float)texture_cut_y / texture_height;
	float u1 = (float)(texture_cut_x + texture_cut_width) / texture_width;
	float v1 = (float)(texture_cut_y + texture_cut_height) / texture_height;

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();
}

//=================================================================
// [ 四角形テクスチャー描画関数 ]
//=================================================================
void DrawTextureRect(float left, float right, float up, float down)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	CreateVertexRect(left, right, up, down);

	pDevice->SetStreamSource(
		0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_2D)
	);

	//FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//=================================================================
// [ 四角形テクスチャー描画の頂点情報登録関数 ]
//=================================================================
void CreateVertexRect(float left, float right, float up, float down)
{
	VERTEX_2D* pV;
	/*↓ 0でも大丈夫、０を入れると全部ロックします*/
	g_pVertexBuffer->Lock(0, sizeof(VERTEX_2D) * 4, (void**)&pV, D3DLOCK_DISCARD);

	pV[0].pos = D3DXVECTOR4(left, up, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(right, up, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(left, down, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(right, down, 1.0f, 1.0f);

	pV[0].color =
	pV[1].color =
	pV[2].color =
	pV[3].color = gTextureColor;

	pV[0].texcoord = D3DXVECTOR2(0, 0);
	pV[1].texcoord = D3DXVECTOR2(1, 0);
	pV[2].texcoord = D3DXVECTOR2(0, 1);
	pV[3].texcoord = D3DXVECTOR2(1, 1);

	g_pVertexBuffer->Unlock();
}

//=================================================================
// [ テクスチャー設置関数 ]
//=================================================================
void SetTexture(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}
	pDevice->SetTexture(0, texture);
}

//=================================================================
// [ テクスチャーカラー設置関数 ]
//=================================================================
void SetTextureColor(D3DCOLOR color)
{
	gTextureColor = color;
}

//=================================================================
// [ テクスチャースケール設置関数 ]
//=================================================================
void SetTextureScale(float scaleX, float scaleY)
{
	gTextureScaleX = scaleX;
	gTextureScaleY = scaleY;
}

//=================================================================
// [ スプライト描画関数 ]
//=================================================================
void DrawSprite(float x, float y, int sprite_width_half, int sprite_height_half,
									float texcoord_left, float texcoord_up,
									float texcoord_right, float texcoord_down)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	CreateVertexSprite(x, y, sprite_width_half, sprite_height_half,
								texcoord_left, texcoord_up,
								texcoord_right, texcoord_down);

	pDevice->SetStreamSource(
		0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_2D)
	);

	//FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=================================================================
// [ スプライト描画の頂点情報登録関数 ]
//=================================================================
void CreateVertexSprite(float x, float y, int sprite_width_half, int sprite_height_half,
											float texcoord_left, float texcoord_up,
											float texcoord_right, float texcoord_down)
{
	VERTEX_2D* pV;
	/*↓ 0でも大丈夫、０を入れると全部ロックします*/
	g_pVertexBuffer->Lock(0, sizeof(VERTEX_2D) * 4, (void**)&pV, D3DLOCK_DISCARD);

	pV[0].pos = D3DXVECTOR4(x - sprite_width_half - 0.5f, y - sprite_height_half - 0.5f, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(x + sprite_width_half - 0.5f, y - sprite_height_half - 0.5f, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(x - sprite_width_half - 0.5f, y + sprite_height_half - 0.5f, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(x + sprite_width_half - 0.5f, y + sprite_height_half - 0.5f, 1.0f, 1.0f);

	pV[0].color =
	pV[1].color =
	pV[2].color =
	pV[3].color = gTextureColor;

	pV[0].texcoord = D3DXVECTOR2(texcoord_left, texcoord_up);
	pV[1].texcoord = D3DXVECTOR2(texcoord_right, texcoord_up);
	pV[2].texcoord = D3DXVECTOR2(texcoord_left, texcoord_down);
	pV[3].texcoord = D3DXVECTOR2(texcoord_right, texcoord_down);

	g_pVertexBuffer->Unlock();
}

//=================================================================
// [ 線分描画関数 ]
//=================================================================
void DrawPolygonLine(D3DXVECTOR2 pos_start, D3DXVECTOR2 pos_end)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	D3DXVECTOR2 vector_line = pos_end - pos_start;
	D3DXVECTOR2 vector_perpendicular(vector_line.y, -vector_line.x);

	//Normalize 
	float vector_length = sqrtf(vector_perpendicular.x * vector_perpendicular.x + vector_perpendicular.y * vector_perpendicular.y);
	D3DXVECTOR2 vector_normalized = { vector_perpendicular.x / vector_length, vector_perpendicular.y / vector_length };

												 //PEN_LINE_WIDTH_HALF
	D3DXVECTOR2 vector_delta = vector_normalized * 4;

	//DirectX
	D3DXVECTOR2 pos_0 = pos_start - vector_delta;
	D3DXVECTOR2 pos_1 = pos_start + vector_delta;
	D3DXVECTOR2 pos_2 = pos_end - vector_delta;
	D3DXVECTOR2 pos_3 = pos_end + vector_delta;

	//OpenGL
	//D3DXVECTOR2 pos_0 = pos_start + vector_delta;
	//D3DXVECTOR2 pos_1 = pos_start - vector_delta;
	//D3DXVECTOR2 pos_2 = pos_end + vector_delta;
	//D3DXVECTOR2 pos_3 = pos_end - vector_delta;

	CreateVertexPolygon(pos_0, pos_1, pos_2, pos_3);

	pDevice->SetStreamSource(
		0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_2D)
	);

	//FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//=================================================================
// [ ポリゴン頂点情報登録関数 ]
//=================================================================
void CreateVertexPolygon(D3DXVECTOR2 pos_0, D3DXVECTOR2 pos_1, D3DXVECTOR2 pos_2, D3DXVECTOR2 pos_3)
{
	VERTEX_2D* pV;
	/*↓ 0でも大丈夫、０を入れると全部ロックします*/
	g_pVertexBuffer->Lock(0, sizeof(VERTEX_2D) * 4, (void**)&pV, D3DLOCK_DISCARD);

	pV[0].pos = D3DXVECTOR4(pos_0.x - 0.5f, pos_0.y - 0.5f, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(pos_1.x - 0.5f, pos_1.y - 0.5f, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(pos_2.x - 0.5f, pos_2.y - 0.5f, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(pos_3.x - 0.5f, pos_3.y - 0.5f, 1.0f, 1.0f);

	pV[0].color =
	pV[1].color =
	pV[2].color =
	pV[3].color = gTextureColor;

	pV[0].texcoord = D3DXVECTOR2(0, 0);
	pV[1].texcoord = D3DXVECTOR2(1, 0);
	pV[2].texcoord = D3DXVECTOR2(0, 1);
	pV[3].texcoord = D3DXVECTOR2(1, 1);

	g_pVertexBuffer->Unlock();
}