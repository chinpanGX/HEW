/*==================================

	[main.h]
	Author : 出合翔太

==================================*/

#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>

//	マクロ定義
#define SCREEN_WIDTH  (1920)												// スクリーン(クライアント領域)の幅
#define SCREEN_HEIGHT (1080)												// スクリーン(クライアント領域)の高さ
#define SAFE_RELEASE(p) do {if(p){(p)->Release(); (p) = NULL;} } while(0)	//	DirectXデバイス解放マクロ
//!	リリース版はフルスクリーン（FALSE）にする	
#define WINMODE	TRUE														//ウィンドウモードの指定（TRUE：ウィンドウモード/FALSE:フルスクリーン）
//!	2Dポリゴン頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )	2Dポリゴンをスクリーン座標変換
#define	FVF_VERTEX2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点バッファのFVF形式の指定
//! 3Dポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 2Dポリゴン頂点フォーマットに合わせた構造体を定義
struct VERTEX_2D
{
	D3DXVECTOR4 pos;	// 頂点座標
	D3DCOLOR	col;	// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
};

// 3Dポリゴン頂点フォーマットに合わせた構造体を定義
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	    // 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR	col;		// 頂点カラー
	D3DXVECTOR2 tex;	    // テクスチャ座標
};

//　シーンの状態管理変数　
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
