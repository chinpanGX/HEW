/*==================================

	[main.h]
	Author : 出合翔太

==================================*/

#pragma once

//#	インクルードファイル
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>

//#	マクロ定義
#define SCREEN_WIDTH  (1920)	// スクリーン(クライアント領域)の幅
#define SCREEN_HEIGHT (1080)    // スクリーン(クライアント領域)の高さ

//!	リリース版はフルスクリーン（FALSE）にする	
#define WINMODE	TRUE			//ウィンドウモードの指定（TRUE：ウィンドウモード/FALSE:フルスクリーン）

//!	DirectXデバイス解放マクロ
#define DEVICE_RELEASE(p) do {if(p){(p)->Release(); (p) = NULL;} } while(0)

//$ #define	NUM_VERTEX		(4)				// 頂点数
//$ #define	NUM_POLYGON		(2)				// ポリゴン数


//# 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

//#	２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )		2Dポリゴンをスクリーン座標変換
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点バッファのFVF形式の指定

//# 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_3D;

// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*　シーンの状態管理変数　*/
enum SCENE_STATE
{
	SCENE_TITLE,		//	タイトルっシーン
	SCENE_MODESELECT,	//	モードセレクトシーン
	SCENE_TUTORIAL,		//	チュートリアルシーン
	SCENE_GAME,			//	ゲームシーン
	SCENE_RESULT,		//	リザルトシーン
	SCENE_DEBUG			//!	デバッグ用シーン…マスター版→消去　
};

//　プロトタイプ宣言
LPDIRECT3DDEVICE9 GetD3DDevice();	//Direct3DDeviceのゲッター
HWND GetHWND();						//ウィンドウハンドルのGetter
double frand();
