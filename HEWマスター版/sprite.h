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
	void SetColor(D3DCOLOR color);	//	カラーの設定		
	//!	Draw関数のオーバーロード
	//	描画 (引数：テクスチャ、X座標、Y座標)
	void Draw(TextureIndex texture_index, float dx, float dy);	
	//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅)
	void Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);
	//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅、カラー設定(R)、カラー設定(G)、カラー設定(B)、カラー設定(A))
	void Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, int col_r, int col_g, int col_b, int col_a);
	//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅、テクスチャの中心座標、拡大縮小、回転)
	void Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation);
	//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅、テクスチャの中心座標、拡大縮小、回転、カラー設定(R)、カラー設定(G)、カラー設定(B)、カラー設定(A))
	void Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation, int col_r, int col_g, int col_b, int col_a);
	//	特別な描画処理
	//	Witdth,Heightはテクスチャの大きさ、カラーはデフォルト値で255,255,255,255を設定
	void Draw(TextureIndex texture_index, float dx, float dy, float Width, float Height, float tx, float ty, float tw, float th, D3DXCOLOR Color = D3DCOLOR_RGBA(255, 255, 255, 255));
	void Draw(TextureIndex texture_index, float dx, float dy, float tx, float ty, float tw, float th, float cx, float cy, float sx, float sy, float rotation, D3DXCOLOR Color = D3DCOLOR_RGBA(255, 255, 255, 255));
};
