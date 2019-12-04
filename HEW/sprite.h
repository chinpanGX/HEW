/*==================================
	
	[sprite.h]
	Author : 出合翔太

=================================*/

#pragma once
#include <d3d9.h>
#include "texture.h"

//Spriteクラス
class Sprite
{
private:
	static D3DXMATRIX				m_mtxWorld;			//	ワールドマトリックス
	static LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	//	頂点バッファ
	static LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;		//	インデックスバッファ
	static LPDIRECT3DDEVICE9		m_Device;			//	デバイス
public:
	HRESULT Init(LPDIRECT3DDEVICE9	pDevice);
	void Uninit();
	void SetColor(D3DCOLOR color);	//	カラーの設定		
	//!	Draw関数のオーバーロード
	//	描画 (引数：テクスチャ、X座標、Y座標)
	void Draw(TextureIndex texture_index, float dx, float dy);	
	//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅)
	void Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);
	//	描画 (引数：テクスチャ、カラー設定、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅)
	void Draw(TextureIndex texture_index, D3DCOLOR color, float dx, float dy, int tx, int ty, int tw, int th);
	//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅、テクスチャの中心座標、拡大縮小、回転)
	void Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation);
};
