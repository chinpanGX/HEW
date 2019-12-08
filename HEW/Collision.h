/*===================================================
	
	[Collision.h]
	Author : 出合翔太

===================================================*/

#pragma once
#include "main.h"
#include "Character.h"
#include "Map.h"
#include "Model.h"
#include "XFile.h"

//	コリジョンを管理するクラス
class Collision
{
private:
	Character	m_Character;
	XFile		m_XFile;
	Model		m_Model;
public:
	Collision();
	D3DXVECTOR3 Player_vs_Map(D3DXVECTOR3 pos,D3DXVECTOR3 move);	//	プレイヤーとマップの当たり判定
	HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices);									//	ポリゴンの頂点を見つける
	BOOL Collide(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, XFile* XFile, Model* pModel, FLOAT* pfDistance, D3DXVECTOR3* pvNormal);	//	レイによる衝突判定
	D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);																				//	滑りベクトル
};

/*	メモ

当たり判定はローカル座標で指定 -> 逆行列で変換する。（転置行列のほうがはやい？）

方向ベクトルの注意点
4次元ベクトルの移動パラメータを０にする -> 平行移動を無効にする

*/