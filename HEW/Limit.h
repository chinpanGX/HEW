#pragma once

#include <d3d9.h>
#include "texture.h"


class Limit
{
private:
	static D3DXMATRIX				m_mtxWorld;			//	ワールドマトリックス
	static LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	//	頂点バッファ
	static LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;		//	インデックスバッファ
	static LPDIRECT3DDEVICE9		m_Device;			//	デバイス
	
public:

	void Update();
	void Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation);
};