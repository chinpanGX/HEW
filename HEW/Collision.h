/*===================================================
	
	[Collision.h]
	Author : 出合翔太

===================================================*/

#pragma once
#include "main.h"
#include "Character.h"
#include "Field.h"

//	コリジョンを管理するクラス
class Collision
{
public:
	static BOOL Collide(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, Field* pField, FLOAT* pfDistance, D3DXVECTOR3* pvNormal);	//	レイによる衝突判定
	static HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices);					//	ポリゴンの頂点を見つける
	static D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);																//	滑りベクトル
};

/*	メモ

当たり判定はローカル座標で指定 -> 逆行列で変換する。（転置行列のほうがはやい？）

方向ベクトルの注意点
4次元ベクトルの移動パラメータを０にする -> 平行移動を無効にする

*/