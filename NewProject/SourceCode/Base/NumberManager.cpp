//=================================================================================
//
//    Number Manager cpp
//    Author : Lin He                                作成日 : 2018/09/15
//
//=================================================================================

#include "NumberManager.h"
#include "Texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_WIDTH  (24)
#define NUMBER_HEIGHT (32)

#define NUMBER_TEXTURE_PATH (L"Resource/Texture/numbers.png")

//=================================================================
// [ NumberManager Constructor ]
//
// [ Detail ]
// 数字テクスチャー読み込み
//=================================================================
NumberManager::NumberManager()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	hr = D3DXCreateTextureFromFile(pDevice, NUMBER_TEXTURE_PATH, &texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Numberテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
}

//=================================================================
// [ NumberManager Destructor ]
//
// [ Detail ]
// 数字テクスチャー解放
//=================================================================
NumberManager::~NumberManager()
{
	texture_->Release();
	texture_ = NULL;
}

//=================================================================
// [ 数字描画関数 ]
//=================================================================
void NumberManager::DrawNumber(int n, float x, float y)
{
	if (n < 0 || n > 9)
		return;

	SetTexture(texture_);
	DrawTexture(x, y, 245, 32, NUMBER_WIDTH * n, 0, NUMBER_WIDTH, NUMBER_HEIGHT);
}

//=================================================================
// [ スコア描画関数 ]
//=================================================================
void NumberManager::DrawScore(int score, float x, float y)
{
	int i = 0;
	while (score != 0)
	{
		int n = score % 10;
		DrawNumber(n, x - NUMBER_WIDTH * i, y);

		score /= 10;
		i++;
	}
}