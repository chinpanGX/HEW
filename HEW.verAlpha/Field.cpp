/*==========================================================

	[Field.cpp]
	Author : 出合翔太

===========================================================*/

#include <map>
#include "main.h"
#include "Field.h"
#include "Model.h"
#include "XFile.h"

//	マクロ定義
#define FILELIST 1	//	読み込むファイルの数

//	グローバル変数
Model *Field::Object[OBJECT_NUM];
extern std::map<std::string, XFile *>g_pXFileList;

//	マップの初期化
void  Field::Init()
{
	//!	XFlieのロード処理
	// 読み込みファイル名リスト
	std::string file_name_list[] =
	{
		"asset/model/ri.x",
	};

	// XFile読み込み
	for (int i = 0; i < FILELIST; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}
}

void Field::Uninit()
{
	delete Object[0];
}

//	マップの描画
void Field::Draw()
{
#if 0
	g_field->pDevice = GetD3DDevice();

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
	g_field->pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);
#endif
	//	3Dモデルの描画
	Object[0] = new Model(
		D3DXVECTOR3(0.0f, 0.0f, -10.0f),
		D3DXVECTOR3(100.0f, 1.0f, 10.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["asset/model/ri.x"]);

	Object[0]->Draw();
#if 0
	//	頂点バッファをデバイスのデータストリームにバインド
	g_field->pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//	頂点フォーマットの設定
	g_field->pDevice->SetFVF(FVF_VERTEX_3D);

	//	自分で作った頂点バッファを描画（メモリの確保、解放をしなければならない→遅くなる）
	g_field->pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
#endif
}

//	頂点作成関数
#if 0 
HRESULT Field::MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	//オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 5, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL)))
	{
		return E_FAIL;
	}

	{
		//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		//頂点バッファの範囲のロックし、頂点バッファへのポインタをもらう
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		//# 天井ポリゴン
			//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-1000, -10, 1000);
		pVtx[1].pos = D3DXVECTOR3(1000, -10, 1000);
		pVtx[2].pos = D3DXVECTOR3(-1000, -10, -1000);
		pVtx[3].pos = D3DXVECTOR3(1000, -10, 1000);
		pVtx[4].pos = D3DXVECTOR3(1000, -10, -1000);
		pVtx[5].pos = D3DXVECTOR3(-1000, -10, -1000);

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

		//頂点バッファをアンロック
		g_pVtxBuffField->Unlock();
	}

	return S_OK;
}
#endif

