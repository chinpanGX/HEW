/*===========================================================

	[Field.h]
	Author : 出合翔太

=============================================================*/

#pragma once
#include "Model.h"

//	マクロ定義
#define ACTOR_NUM 1	// 3Dモデルの数

//# Fieldクラス
/* ゲームの背景の描画をするクラス */
class Field
{
private:
	static Model *Actor[ACTOR_NUM];						//	Model型ポインタ配列
	static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffField;	// 頂点バッファへのポインタ
	static D3DXMATRIX				g_mtxWorldField;	// ワールドマトリックス
	LPDIRECT3DDEVICE9				pDevice;			// デバイス取得用変数
	//	3次元ベクトル
	static D3DXVECTOR3				g_posField;			// 地面の位置
	static D3DXVECTOR3				g_rotField;			// 地面の向き(回転)
	static D3DXVECTOR3				g_sclField;			// 地面の大きさ(スケール)
public:
	static HRESULT Init();										//	初期化処理
	static void Uninit();										//	終了処理
	static void ActorDraw();									//	3Dモデルの描画処理
	static void	PlaneDraw();									//	頂点指定の描画処理
	static HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);	//	頂点作成処理
};

