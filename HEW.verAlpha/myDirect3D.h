
#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

// ゲームの初期化関数
// 戻り値:初期化に失敗したときfalse
bool D3D_Initialize(HWND hWnd);

// ゲームの終了処理
void D3D_Finalize(void);

//Direct3DDeviceのゲッター
LPDIRECT3DDEVICE9 GetD3DDevice();
