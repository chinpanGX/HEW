// author 成



#include"main.h"
#include"mondai.h"
#include"texture.h"
#include "Controller.h"

//	マクロ定義
#define POLYGON_NUM 2
#define VERTEX_NUM 6

//	スタティック変数
LPDIRECT3DVERTEXBUFFER9 Mondai::g_pVtxBuffMondai = NULL;	//	頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9  Mondai::g_pIdxBuffMondai = NULL;
D3DXMATRIX				Mondai::g_mtxWorldMondai;			//	ワールドマトリックス
D3DXVECTOR3				Mondai::g_posMondai;				//	地面の位置
D3DXVECTOR3				Mondai::g_rotMondai;				//	地面の向き(回転)
D3DXVECTOR3				Mondai::g_sclMondai;				//	地面の大きさ	
LPDIRECT3DDEVICE9		Mondai::pDevice;					//	デバイス取得用変数


static bool flagMondai;
static int g_NumIndexMondai = 36;



//	フィールドの初期化
HRESULT Mondai::Init()
{
	pDevice = GetD3DDevice();
	// 頂点情報の作成
	MakeVertexMondai(pDevice);

	// 位置・回転・スケールの初期設定
	g_posMondai = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMondai = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclMondai = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	flagMondai = false;

	return S_OK;
}

//	フィールドの終了処理
void Mondai::Uninit()
{
	DEVICE_RELEASE(pDevice);
	DEVICE_RELEASE(g_pVtxBuffMondai);
}

//	フィールドの描画
void Mondai::Draw()
{

	if (flagMondai == false)

	{
		pDevice = GetD3DDevice();

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		//	ワールド変換（ワールドマトリクスの初期化）
		D3DXMatrixIdentity(&g_mtxWorldMondai);
		D3DXMatrixScaling(&mtxScl, g_sclMondai.x, g_sclMondai.y, g_sclMondai.z);
		D3DXMatrixMultiply(&g_mtxWorldMondai, &g_mtxWorldMondai, &mtxScl);						//　引数は2番目と3番目の計算結果を1番目に入れる
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMondai.x, g_rotMondai.y, g_rotMondai.z);
		D3DXMatrixMultiply(&g_mtxWorldMondai, &g_mtxWorldMondai, &mtxRot);
		D3DXMatrixTranslation(&mtxTranslate, g_posMondai.y, g_posMondai.x, g_posMondai.z);
		D3DXMatrixMultiply(&g_mtxWorldMondai, &g_mtxWorldMondai, &mtxTranslate);

		// ワールドマトリクスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMondai);

		//	頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxBuffMondai, 0, sizeof(VERTEX_3D));

		//	頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		//pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_MONDAI));


		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_NumIndexMondai, 0, 12);

		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, POLYGON_NUM);

	}

}


HRESULT Mondai::MakeVertexMondai(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMondai,
		NULL)))
	{
		return E_FAIL;
	}

	{
		VERTEX_3D *pVtx;

		g_pVtxBuffMondai->Lock(0, 0, (void**)&pVtx, 0);

		////頂点座標の設定
		//for (int z = 0; z < 2; z++)
		//{
		//	for (int x = 0; x < 4; x++)
		//	{
		//		pVtx[z * 4 + x].pos = D3DXVECTOR3(x*100.0f, 0.0f, z*-100.0f);
		//	}
		//}


		pVtx[0].pos = D3DXVECTOR3(-30.0f, 30.0f, -30.0f);
		pVtx[1].pos = D3DXVECTOR3(30.0f, 30.0f, -30.0f);
		pVtx[2].pos = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
		pVtx[3].pos = D3DXVECTOR3(30.0f, -30.0f, -30.0f);
		pVtx[4].pos = D3DXVECTOR3(30.0f, -30.0f, 30.0f);
		pVtx[5].pos = D3DXVECTOR3(-30.0f, -30.0f, 30.0f);
		/*pVtx[6].pos = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		pVtx[7].pos = D3DXVECTOR3(-10.0f, 10.0f, 10.0f);*/

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);                 
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		/*pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
*/
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		/*pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);*/

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(3.0f, 0.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(2.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(3.0f, 1.0f);

		g_pVtxBuffMondai->Unlock();
	}

	//if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * 8,
	//	D3DUSAGE_WRITEONLY,
	//	D3DFMT_INDEX16,
	//	D3DPOOL_MANAGED,
	//	&g_pIdxBuffMondai,
	//	NULL)))
	//{
	//	return E_FAIL;
	//}

	//{//インデックスバッファの中身を埋める
	//	WORD *pIdx;

	//	g_pIdxBuffMondai->Lock(0, 0, (void**)&pIdx, 0);

	//	pIdx[0] = 4;
	//	pIdx[1] = 0;
	//	pIdx[2] = 5;
	//	pIdx[3] = 1;
	//	pIdx[4] = 6;
	//	pIdx[5] = 2;
	//	pIdx[6] = 7;
	//	pIdx[7] = 3;
	//

		//頂点バッファをアンロック
		g_pVtxBuffMondai->Unlock();
	

	return S_OK;
}

void Mondai::Update()

{

	if (KeyBoard::IsPress(DIK_1) || KeyBoard::IsPress(DIK_2) || KeyBoard::IsPress(DIK_3) || KeyBoard::IsPress(DIK_4))

		flagMondai = true;

}