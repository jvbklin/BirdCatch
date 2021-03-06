//=================================================================================
// 
//    DirectX9 Header
//    Author : Lin He                                作成日 : 2017/12/04
// 
//=================================================================================

#ifndef _DIRECTX9_H_
#define _DIRECTX9_H_

#include <d3d9.h>
#include <d3dx9.h>

#include "input.h"

//=================================================================
// [ 初期化関数 ]
//
// [ Return ]
// bool : 初期化成功したらtrueを返す
//
// [ Details ]
// DirextX9デバイス初期化と各種処理の初期化
//=================================================================
bool InitDirectX9(HINSTANCE hInstance, HWND hWnd, BOOL bWindow, int nWindowWidth, int nWindowHeight);

//=================================================================
// [ 終了処理関数 ]
//=================================================================
void UninitDirectX9();

//=================================================================
// [ 更新関数 ]
//=================================================================
void UpdateDirectX9();

//=================================================================
// [ 描画関数 ]
//=================================================================
void DrawDirectX9();

//=================================================================
// [ デバイス取得関数 ]
//
// [ Return ]
// LPDIRECT3DDEVICE9 : DirextX9デバイスを返す
//=================================================================
LPDIRECT3DDEVICE9 GetD3DDevice();

//=================================================================
// [ マウス取得関数 ]
//
// [ Return ]
// CInputMouse* : マウスポインタを返す
//=================================================================
CInputMouse* GetMouse();

#endif