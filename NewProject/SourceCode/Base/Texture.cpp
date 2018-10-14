//=================================================================================
//
//    2D�e�N�X�`���[�`��[Texture.cpp]
//    Author : Lin He                                �쐬�� : 2017/06/05
//
//=================================================================================

#include "Texture.h"
#include "DirectX9.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D ( D3DFVF_XYZRHW| D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static D3DCOLOR gTextureColor;
static float gTextureScaleX;
static float gTextureScaleY;

//=================================================================
// [ �e�N�X�`���[�`�揉�����֐� ]
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
		FVF_VERTEX_2D,    /*0�ł����v*/
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"���_�o�b�t�@�����Ȃ�����", L"error", MB_OK);
		return false;
	}

	gTextureColor = 0xFFFFFFFF;

	gTextureScaleX = 1.0f;
	gTextureScaleY = 1.0f;

	return true;
}

//=================================================================
// [ �e�N�X�`���[�`��I�������֐� ]
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
// [ �e�N�X�`���[�`��֐� ]
//=================================================================
void DrawTexture(float x, float y, int texture_width, int texture_height,
									int texture_cut_x, int texture_cut_y,
									int texture_cut_width, int texture_cut_height)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
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

	//FVF(������g�p���钸�_���)�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//=================================================================
// [ �e�N�X�`���[�`��̒��_���o�^�֐� ]
//=================================================================
void CreateVertex(float x, float y, int texture_width, int texture_height,
	int texture_cut_x, int texture_cut_y,
	int texture_cut_width, int texture_cut_height)
{
	VERTEX_2D* pV;
	/*�� 0�ł����v�A�O������ƑS�����b�N���܂�*/
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
// [ �l�p�`�e�N�X�`���[�`��֐� ]
//=================================================================
void DrawTextureRect(float left, float right, float up, float down)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	CreateVertexRect(left, right, up, down);

	pDevice->SetStreamSource(
		0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_2D)
	);

	//FVF(������g�p���钸�_���)�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//=================================================================
// [ �l�p�`�e�N�X�`���[�`��̒��_���o�^�֐� ]
//=================================================================
void CreateVertexRect(float left, float right, float up, float down)
{
	VERTEX_2D* pV;
	/*�� 0�ł����v�A�O������ƑS�����b�N���܂�*/
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
// [ �e�N�X�`���[�ݒu�֐� ]
//=================================================================
void SetTexture(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}
	pDevice->SetTexture(0, texture);
}

//=================================================================
// [ �e�N�X�`���[�J���[�ݒu�֐� ]
//=================================================================
void SetTextureColor(D3DCOLOR color)
{
	gTextureColor = color;
}

//=================================================================
// [ �e�N�X�`���[�X�P�[���ݒu�֐� ]
//=================================================================
void SetTextureScale(float scaleX, float scaleY)
{
	gTextureScaleX = scaleX;
	gTextureScaleY = scaleY;
}

//=================================================================
// [ �X�v���C�g�`��֐� ]
//=================================================================
void DrawSprite(float x, float y, int sprite_width_half, int sprite_height_half,
									float texcoord_left, float texcoord_up,
									float texcoord_right, float texcoord_down)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
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

	//FVF(������g�p���钸�_���)�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=================================================================
// [ �X�v���C�g�`��̒��_���o�^�֐� ]
//=================================================================
void CreateVertexSprite(float x, float y, int sprite_width_half, int sprite_height_half,
											float texcoord_left, float texcoord_up,
											float texcoord_right, float texcoord_down)
{
	VERTEX_2D* pV;
	/*�� 0�ł����v�A�O������ƑS�����b�N���܂�*/
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
// [ �����`��֐� ]
//=================================================================
void DrawPolygonLine(D3DXVECTOR2 pos_start, D3DXVECTOR2 pos_end)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
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

	//FVF(������g�p���钸�_���)�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//=================================================================
// [ �|���S�����_���o�^�֐� ]
//=================================================================
void CreateVertexPolygon(D3DXVECTOR2 pos_0, D3DXVECTOR2 pos_1, D3DXVECTOR2 pos_2, D3DXVECTOR2 pos_3)
{
	VERTEX_2D* pV;
	/*�� 0�ł����v�A�O������ƑS�����b�N���܂�*/
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