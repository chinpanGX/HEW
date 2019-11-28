/*==================================

	[sprite.cpp]
	Author : 出合翔太

==================================*/

#include <d3dx9.h>
#include <math.h>
#include "main.h"
#include "texture.h"
#include "sprite.h"

//	マクロ定義
#define MINA	(0.5f)	//	画面の表示位置の修正固定値

//	グローバル変数
D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);	//カラーの変更が可能

//	スタティック変数
D3DXMATRIX				Sprite::m_mtxWorld;			//	ワールドマトリックス
LPDIRECT3DVERTEXBUFFER9 Sprite::m_pVertexBuffer;	//	頂点バッファ(頂点情報)を格納したメモリ
LPDIRECT3DINDEXBUFFER9	Sprite::m_pIndexBuffer;		//	インデックスバッファ
LPDIRECT3DDEVICE9		Sprite::m_Device;			//	デバイス

//	初期化処理
HRESULT Sprite::Init(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL)))
	{
		return E_FAIL;
	}
	if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL)))
	{
		return E_FAIL;
	}
	VERTEX_3D *pVtx;	//	頂点バッファへのポインタ
	WORD* pIndex;		//	インデクスバッファへのポインタ
	m_pVertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-30.0f, 30.0f, -30.0f);		//	中身「を関数の引数にする
	pVtx[1].pos = D3DXVECTOR3(30.0f, 30.0f, -30.0f);
	pVtx[2].pos = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
	pVtx[3].pos = D3DXVECTOR3(30.0f, -30.0f, -30.0f);
	pVtx[4].pos = D3DXVECTOR3(30.0f, -30.0f, 30.0f);
	pVtx[5].pos = D3DXVECTOR3(-30.0f, -30.0f, 30.0f);

	for (int i = 0; i < 5 ; i++)
	{
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(3.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(2.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(3.0f, 1.0f);
	
	m_pVertexBuffer ->Unlock();
	
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 1;
	pIndex[4] = 3;
	pIndex[5] = 2;
	m_pIndexBuffer->Unlock();
}

//	終了処理
void Sprite::Uninit()
{
	DEVICE_RELEASE(m_pIndexBuffer);
	DEVICE_RELEASE(m_pVertexBuffer);
}

//	色を設定するセッター
void Sprite::SetColor(D3DCOLOR color)
{
	g_Color = color;
}

//	描画 (引数：テクスチャ、X座標、Y座標)
void Sprite::Draw(TextureIndex texture_index, float dx, float dy)
{
	m_Device = GetD3DDevice();
	if (!m_Device) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	VERTEX_2D vertexes[] = {
		{ D3DXVECTOR4(dx - MINA, dy - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(dx + w - MINA, dy - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx - MINA, dy + h - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx + w - MINA, dy + h - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 1.0f) },
	};

	m_Device->SetFVF(FVF_VERTEX2D);
	m_Device->SetTexture(0, Texture_GetTexture(texture_index));

	m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}

//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅)
void Sprite::Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty,int tw, int th)
{
	m_Device = GetD3DDevice();
    if( !m_Device ) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

    float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

    VERTEX_2D vertexes[] = 
	{
        { D3DXVECTOR4(dx      - MINA, dy      - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
        { D3DXVECTOR4(dx + tw - MINA, dy      - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(dx      - MINA, dy + th - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(dx + tw - MINA, dy + th - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
    };

    m_Device->SetFVF(FVF_VERTEX2D);
	m_Device->SetTexture(0, Texture_GetTexture(texture_index));
    m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}

//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅、テクスチャの中心座標、拡大縮小、回転)
void Sprite::Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation)
{
	m_Device = GetD3DDevice();
	if (!m_Device) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

	D3DXMATRIX matBase[4];

	D3DXMatrixTranslation(&matBase[0], -(tw - (tw - cx)), -(th - (th - cy)), 0.0f);
	D3DXMatrixTranslation(&matBase[1],   tw - cx,         -(th - (th - cy)), 0.0f);
	D3DXMatrixTranslation(&matBase[2], -(tw - (tw - cx)),   th - cy,         0.0f);
	D3DXMatrixTranslation(&matBase[3],   tw - cx,           th - cy,         0.0f);

	D3DXMATRIX matTrans;
	D3DXMATRIX matRot;
	D3DXMATRIX matScale;
	D3DXMATRIX matAll;
	float px[4], py[4];

	D3DXMatrixTranslation(&matTrans, dx, dy, 0.0f);
	D3DXMatrixRotationZ(&matRot, rotation);
	D3DXMatrixScaling(&matScale, sx, sy, 1.0f);

	for (int i = 0; i < 4; i++){
		matAll = matBase[i] * matScale * matRot * matTrans;
		px[i] = matAll._41;
		py[i] = matAll._42;
	}

	VERTEX_2D vertexes[] = 
	{
		{ D3DXVECTOR4(px[0] - 0.4f, py[0] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
		{ D3DXVECTOR4(px[1] - 0.4f, py[1] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(px[2] - 0.4f, py[2] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(px[3] - 0.4f, py[3] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
	};

	m_Device->SetFVF(FVF_VERTEX2D);
	m_Device->SetTexture(0, Texture_GetTexture(texture_index));
	m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}

//	3D描画（引数：テクスチャ、X座標、Y座標、Z座標、）
void Sprite::Draw(TextureIndex Texture, float pos_x,float pos_y,float pos_z,float rot_x,float rot_y,float rot_z,float scl_x,float scl_y,float scl_z)
{
	m_Device = GetD3DDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//	ワールド変換（ワールドマトリクスの初期化）
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScl, scl_x, scl_y, scl_z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);					//　引数は2番目と3番目の計算結果を1番目に入れる
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot_x, rot_y, rot_z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTranslate, pos_y, pos_x, pos_z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ワールドマトリクスの設定
	m_Device->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//	頂点バッファをデバイスのデータストリームにバインド
	//	SetStreamSource	(第１引数:頂点バッファを設定するストリーム番号を指定、第２引数:頂点バッファへのポインタを指定、第３引数:頂点データの一つ分のデータサイズをバイト単位で指定)
	m_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));

	//インデックスバッファのセット
	m_Device->SetIndices(m_pIndexBuffer);

	//	頂点フォーマットの設定
	m_Device->SetFVF(FVF_VERTEX3D);

	//テクスチャの設定
	m_Device->SetTexture(0, Texture_GetTexture(Texture));

	//----------------------------------------------------------------------------------------------
	//	  DrawPrimitiveUpとDrawRimitiveの違い
	//"		DrawPrimitiveUpの説明	->	板ポリなど頂点が少ないオブジェクトで使う
	//!			１．DrawPrimitiveUpが頂点情報を通常のメモリに置く -> 処理が遅くなる
	//!			２．LockとUnlockを使わなくていい	
	//"		DrawPrimitiveの説明		->	頂点が多いモデルファイルなどを描画するときに使う
	//!			１．頂点情報がVRAM上に置かれる　-> 処理速度が速い
	//!			２．LockとUnlockが必要になる	-> パフォーマンスが低下 ->なるべく少なくしたい
	//----------------------------------------------------------------------------------------------

	//	自分で作った頂点バッファを描画（メモリの確保、解放をしなければならない　-> 多用すると遅くなる）
	//DrawPrimitive (第1引数：プリミティブを指定、第2引数：描画を開始する頂点を指定、第3引数：使用するプリミティブの数を指定)
	//m_Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, POLYGON_NUM);
	m_Device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, 0, 20, 0, 6);
}
