/*==========================================================

	[Field.cpp]
	Author : 出合翔太

===========================================================*/

#include "main.h"
#include "Field.h"

//	マクロ定義
#define POLYGON_NUM 2
#define VERTEX_NUM 6

//	グローバル変数
LPDIRECT3DVERTEXBUFFER9 Field::g_pVtxBuffField = NULL;	//	頂点バッファへのポインタ
D3DXMATRIX				Field::g_mtxWorldField;			//	ワールドマトリックス
D3DXVECTOR3				Field::g_posField;				//	地面の位置
D3DXVECTOR3				Field::g_rotField;				//	地面の向き(回転)
D3DXVECTOR3				Field::g_sclField;				//	地面の大きさ	
LPDIRECT3DDEVICE9		Field::pDevice;				// デバイス取得用変数

//	フィールドの初期化
HRESULT Field::Init()
{
	pDevice = GetD3DDevice();
	// 頂点情報の作成
	MakeVertexField(pDevice);

	// 位置・回転・スケールの初期設定
	g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

//	フィールドの終了処理
void Field::Uninit()
{
	DEVICE_RELEASE(pDevice);
	DEVICE_RELEASE(g_pVtxBuffField);
}

//	フィールドの描画
void Field::Draw()
{
	pDevice = GetD3DDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	
	//	ワールド変換（ワールドマトリクスの初期化）
	D3DXMatrixIdentity(&g_mtxWorldField);
	D3DXMatrixScaling(&mtxScl, g_sclField.x, g_sclField.y, g_sclField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);	//　引数は2番目と3番目の計算結果を1番目に入れる
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.x, g_rotField.y, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);
	D3DXMatrixTranslation(&mtxTranslate, g_posField.y, g_posField.x, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);
	
	// ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

	//	頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//	頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	//pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD03));

	//	自分で作った頂点バッファを描画（メモリの確保、解放をしなければならない→遅くなる）
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, POLYGON_NUM);

}


//	頂点作成関数
HRESULT Field::MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	//オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL)))
	{
		return E_FAIL;
	}

	{
		//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		//頂点バッファの範囲のロックし、頂点バッファへのポインタをもらう
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-100, -100, 100);
		pVtx[1].pos = D3DXVECTOR3(100, -100, 100);
		pVtx[2].pos = D3DXVECTOR3(-100,-100, -100);
		pVtx[3].pos = D3DXVECTOR3(100, -100, 100);
		pVtx[4].pos = D3DXVECTOR3(100, -100, -100);
		pVtx[5].pos = D3DXVECTOR3(-100, -100, -100);
		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffField->Unlock();
	}

	return S_OK;
}

