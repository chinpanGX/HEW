
//成

#if 0


#pragma once
#include "Model.h"

//	マクロ定義
#define ACTOR_NUM 1	// 3Dモデルの数



class Mondai
{
private:
	static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffMondai;	// 頂点バッファへのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMondai;
	static D3DXMATRIX				g_mtxWorldMondai;	// ワールドマトリックス
	static LPDIRECT3DDEVICE9		pDevice;			// デバイス取得用変数
	//	3次元ベクトル
	static D3DXVECTOR3				g_posMondai;			// 地面の位置
	static D3DXVECTOR3				g_rotMondai;			// 地面の向き(回転)
	static D3DXVECTOR3				g_sclMondai;			// 地面の大きさ(スケール)
public:
	static HRESULT Init();										//	初期化処理
	static void Uninit();										//	終了処理
	static void Draw();										//	描画
	static void Update();
	//static void HitMondai();
	//static HRESULT MakeVertexMondai(LPDIRECT3DDEVICE9 pDevice);	//	頂点作成
};

#endif