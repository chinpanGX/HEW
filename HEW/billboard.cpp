/*=========================================

	[BillBoard.cpp]


=========================================*/

#include "BillBoard.h"

// マクロ定義
#define	BILLBOARD_SIZE_X		(20.0f)		// ビルボードの幅
#define	BILLBOARD_SIZE_Y		(20.0f)		// ビルボードの高さ
#define	BILLBOARD_NUM_POLYGON			(2)			//	ポリゴン
#define	BILL_NUM_VERTEX			(4)			//	頂点

//	グローバル変数
static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffBillboard = NULL;	// 頂点バッファへのポインタ
static D3DXMATRIX				g_mtxWorldBillboard;		// ワールドマトリックス

HRESULT BillBoard_Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * BILL_NUM_VERTEX,	D3DUSAGE_WRITEONLY,FVF_VERTEX3D,D3DPOOL_MANAGED,&g_pVtxBuffBillboard,NULL)))							
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f); -

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		g_pVtxBuffBillboard->Unlock();
	}

	return S_OK;
}

void BillBoard_Uninit()
{
	SAFE_RELEASE(g_pVtxBuffBillboard);
}

void BillBoard_Draw(TextureIndex texture_index,D3DXVECTOR3 mtxPos, D3DXVECTOR3 mtxScl)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	D3DXMatrixIdentity(&g_mtxWorldBillboard);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	g_mtxWorldBillboard._11 = mtxView._11;
	g_mtxWorldBillboard._12 = mtxView._21;
	g_mtxWorldBillboard._13 = mtxView._31;
	g_mtxWorldBillboard._21 = mtxView._12;
	g_mtxWorldBillboard._22 = mtxView._22;
	g_mtxWorldBillboard._23 = mtxView._32;
	g_mtxWorldBillboard._31 = mtxView._13;
	g_mtxWorldBillboard._32 = mtxView._23;
	g_mtxWorldBillboard._33 = mtxView._33;

	D3DXMatrixScaling(&mtxScale, mtxScl.x, mtxScl.y, mtxScl.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxScale);
	D3DXMatrixTranslation(&mtxTranslate, mtxPos.x, mtxPos.y, mtxPos.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTranslate);
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);
	
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, BILLBOARD_NUM_POLYGON);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
