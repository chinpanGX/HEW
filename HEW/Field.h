/*============================================
	
	[Field.h]
	Author :　出合翔太

============================================*/

#pragma once
#include "main.h"

class Field
{
public:
	static LPDIRECT3DTEXTURE9	m_pTextureModel;	//	テクスチャへのポインタ
	static LPD3DXMESH			m_pMeshModel;		//	メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMatModel;	//	マテリアル情報へのポインタ
	static DWORD				m_nNumMatModel;		//	マテリアル情報の総数
	static LPDIRECT3DDEVICE9	m_pDevice;			//	デバイス
	D3DXMATRIX					m_mtxWorldModel;	//	ワールドマトリックス
	D3DXVECTOR3					m_position;			//	位置
	D3DXVECTOR3					m_scale;			//	スケール
	D3DXVECTOR3					m_angle;			//	回転
public:
	HRESULT Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, D3DXVECTOR3 Angle);
	void Uninit();
	void Draw();
};



