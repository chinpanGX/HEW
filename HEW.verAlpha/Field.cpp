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
#define FILELIST 2	//	読み込むファイルの数
#define POLYGON_NUM 2
#define VERTEX_NUM 6

//	グローバル変数
Model *Field::Actor[ACTOR_NUM];
extern std::map<std::string, XFile *>g_pXFileList;
LPDIRECT3DVERTEXBUFFER9 Field::g_pVtxBuffField = NULL;	//	頂点バッファへのポインタ
D3DXMATRIX				Field::g_mtxWorldField;			//	ワールドマトリックス
D3DXVECTOR3				Field::g_posField;				//	地面の位置
D3DXVECTOR3				Field::g_rotField;				//	地面の向き(回転)
D3DXVECTOR3				Field::g_sclField;				//	地面の大きさ	
Field *g_field = new Field;

//	マップの初期化
HRESULT Field::Init()
{
	g_field->pDevice = GetD3DDevice();

	// 頂点情報の作成
	MakeVertexField(g_field->pDevice);

	// 位置・回転・スケールの初期設定
	g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//!	XFlieのロード処理
	// 読み込みファイル名リスト
	std::string file_name_list[] =
	{
		"asset/model/ri.x",
		"asset/model/dai.x",
	};

	// XFile読み込み
	for (int i = 0; i < FILELIST; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}

	return S_OK;
}

void Field::Uninit()
{
	delete Actor[0];
	/*delete Actor[1];*/
}

void Field::ActorDraw()
{
	//	3Dモデルの描画
	/*Actor[0] = new Model(
		D3DXVECTOR3(0.0f, 0.0f, -10.0f),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["asset/model/ri.x"]);

	Actor[0]->Draw();*/

	Actor[1] = new Model(
		D3DXVECTOR3(0.0f, 0.0f, -10.0f),
		D3DXVECTOR3(30.0f, 30.0f, 30.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["asset/model/dai.x"]);

	Actor[1]->Draw();
}

void Field::PlaneDraw()
{
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

	//	頂点バッファをデバイスのデータストリームにバインド
	g_field->pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//	頂点フォーマットの設定
	g_field->pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	//g_field->pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD03));

	//	自分で作った頂点バッファを描画（メモリの確保、解放をしなければならない→遅くなる）
	g_field->pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, POLYGON_NUM);

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

