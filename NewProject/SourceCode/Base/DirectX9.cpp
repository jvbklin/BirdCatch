//=================================================================================
//
//    DirectX9 cpp
//    Author : Lin He                                作成日 : 2017/12/04
//
//=================================================================================

#include "DirectX9.h"

#include <windows.h>

#include "input.h"
#include "sound.h"
#include "Texture.h"
#include "../Game/Scene.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define SAFE_RELEASE(p) {if(p){ (p)->Release(); (p) = NULL; }}

//*****************************************************************************
// グローバル変数
//*****************************************************************************

static LPDIRECT3D9	g_pD3D = NULL;				// ダイレクト3Dインタフェース
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	// ダイレクト3Dデバイス

static CInputMouse* g_pInputMouse = NULL;		// マウスへのポインタ

//=================================================================
// [ DirextX9初期化関数 ]
//=================================================================
bool InitDirectX9(HINSTANCE hInstance, HWND hWnd, BOOL bWindow, int nWindowWidth, int nWindowHeight)
{
	// ダイレクト3Dインタフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return false;
	}

	// 現在のディスプレイモードを取得
	D3DDISPLAYMODE d3ddm;
	HRESULT hr = g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,	// ディスプレイ・アダプタを指定する( 今回の指定は初期のディスプレイ・アダプタ )
		&d3ddm);				// 現在のディスプレイ・アダプタの情報を受け取る変数の先頭アドレス

	if (FAILED(hr))
	{
		return false;
	}

	// デバイスのプレゼンテーションパラメータ(デバイスを作成するためのデータ)
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));							//　中のものを全てを初期化する(初期化する先頭アドレス, 初期化するサイズ)
	d3dpp.BackBufferWidth = nWindowWidth;				//　裏画面(バックバッファ)の幅
	d3dpp.BackBufferHeight = nWindowHeight;				//	裏画面(バックバッファ)の高さ
	d3dpp.BackBufferFormat = d3ddm.Format;				//	色数( バックバッファのフォーマット )
	d3dpp.BackBufferCount = 1;							//	バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//	映像信号の同期(DISCARDは垂直同期を気にする)
	d3dpp.EnableAutoDepthStencil = TRUE;						//	TRUEで良い
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//	今はこれで良い上のフォーマット
	d3dpp.Windowed = bWindow;						//	TRUEでウィンドウモード,FALSEでフルスクリーンモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//	フルスクリーンモードの時のリフレッシュレートのHz数を変更
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//	モニターのHz数に合わせて描画される(IMMEDIATEだと垂直同期を待たずに描画する)( D3DPRESENT_INTERVAL_ONE　にするとヘルツで動く )


	// デバイスオブジェクトの生成( ｢描画｣と｢頂点処理｣をハードウェアで行う
	hr = g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,						// ディスプレイ・アダプタを指定する( 今回の指定は初期のディスプレイ・アダプタ )
		D3DDEVTYPE_HAL,							// デバイスタイプ( 今回の指定はハードウェアによる処理を行う )
		hWnd,									// このデバイスでフォーカスを設定するウィンドウハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイスの作成を制御するフラグの組み合わせ( 今回の指定はハードウェアによる頂点処理を指定 )
		&d3dpp,									// デバイスの設定を指定した変数の先頭アドレス
		&g_pD3DDevice);							// 作成したデバイスを受け取る変数の先頭アドレス

	if (FAILED(hr))
	{
		// エラー処理
		MessageBox(hWnd, L"ダイレクト3Dデバイスの\n作成に失敗しました!!", L"エラー", MB_OK);
		return false;
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//ファイタリング
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	
	// マウス処理初期化
	g_pInputMouse = new CInputMouse;
	g_pInputMouse->Init(hInstance, hWnd);

	//描画関数初期化
	InitTexture();

	//サウンド
	InitSound(hWnd);

	//シーンマネジャーの初期化
	SceneManager::Init();

	return true;
}

//=================================================================
// [ DirextX9終了処理関数 ]
//=================================================================
void UninitDirectX9()
{
	//シーンマネジャーの終了処理
	SceneManager::Uninit();

	//サウンド
	UninitSound();

	//描画関数の終了処理
	UninitTexture();

	// マウスの解放処理
	if (g_pInputMouse)
	{
		g_pInputMouse->Uninit();
		delete g_pInputMouse;
		g_pInputMouse = NULL;
	}

	// キーボード入力の終了処理

	// デバイスの解放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの解放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=================================================================
// [ DirextX9更新関数 ]
//=================================================================
void UpdateDirectX9()
{
	// マウスの更新処理
	if (g_pInputMouse)
	{
		g_pInputMouse->Update();
	}

	SceneManager::UpdateScene();

}

//=================================================================
// [ DirextX9描画関数 ]
//=================================================================
void DrawDirectX9()
{
	// 画面バッファをクリアする
	g_pD3DDevice->Clear(0,						// RECT構造体配列の矩形の数
		NULL,									// RECT構造体の先頭アドレス(画面全体はNULL)
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	// TARGETは色のクリア、ZBUFFERはZバッファのクリア
		D3DCOLOR_RGBA(32, 64, 192, 255),		// クリアカラ―(TARGETがあるとき)
		1.0f,									// Zバッファのクリア値
		0);										// ステンシル値のクリア値

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		SceneManager::DrawScene();

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// 上で描画したものを実際にウィンドウに反映させる
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=================================================================
// [ DirextX9デバイス取得関数 ]
//=================================================================
LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}

//=================================================================
// [ DirextX9マウス取得関数 ]
//=================================================================
CInputMouse* GetMouse()
{
	return g_pInputMouse;
}