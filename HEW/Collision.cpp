/*=================================================

	[Collision.cpp]
	Author : 出合翔太

==================================================*/

#include "Collision.h"

void Collision::Update()
{

}
#if 0


void Collision::Player_vs_Map()
{
	//	当たり判定
	FLOAT fDistance = 0;
	D3DXVECTOR3 vNormal;

	if (Collide(m_Character.GetPos(), m_Character.GetMove(), &m_Actor[0], &fDistance, &vNormal) && fDistance <= 0.3)
	{
		//当たり状態なので、滑らせる
		Thing[1].vDir = Slip(Thing[1].vDir, vNormal);//滑りベクトルを計算

		//滑りベクトル先の地面突起とのレイ判定 ２重に判定	
		if (Collide(Thing[1].vPosition, Thing[1].vDir, &Thing[0], &fDistance, &vNormal) && fDistance <= 0.2)
		{
			//２段目の当たり状態なので、滑らせる おそらく上がる方向		
			Thing[1].vDir = Slip(Thing[1].vDir, vNormal);//滑りベクトルを計算
		}
	}
	Thing[1].vPosition.y += 0.7;

	//ロボット　位置更新
	Thing[1].vPosition += Thing[1].vDir;
}
#endif // 0

HRESULT Collision::FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3 * pvVertices)
{
	DWORD i, k;
	DWORD dwStride = pMesh->GetNumBytesPerVertex();
	DWORD dwVertexNum = pMesh->GetNumVertices();
	DWORD dwPolyNum = pMesh->GetNumFaces();
	WORD* pwPoly = NULL;
	pMesh->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);

	BYTE *pbVertices = NULL;
	FLOAT* pfVetices = NULL;
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;
	pMesh->GetVertexBuffer(&VB);
	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pvVertices[0].x = pfVetices[0];
		pvVertices[0].y = pfVetices[1];
		pvVertices[0].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pvVertices[1].x = pfVetices[0];
		pvVertices[1].y = pfVetices[1];
		pvVertices[1].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pvVertices[2].x = pfVetices[0];
		pvVertices[2].y = pfVetices[1];
		pvVertices[2].z = pfVetices[2];

		pMesh->UnlockIndexBuffer();
		VB->Unlock();
		VB->Release();
	}
	return S_OK;
}

//レイによる衝突判定　レイが相手メッシュと交差する場合は、pfDistanceに距離を、pvNormalに衝突面の法線を入れてtrueを返す
BOOL Collision::Collide(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, Character *pChara, FLOAT * pfDistance, D3DXVECTOR3 * pvNormal)
{
	BOOL boHit = false;
	D3DXMATRIX mWorld;
	D3DXVec3Normalize(&vDir, &vDir);

	// レイを当てるメッシュが動いていたり回転している場合でも対象のワールド行列の逆行列を用いれば正しくレイが当たる
	D3DXMatrixInverse(&mWorld, NULL, &pChara->GetMat());
	D3DXVec3TransformCoord(&vStart, &vStart, &mWorld);

	DWORD dwPolyIndex;
	D3DXIntersect(pChara->GetMesh(), &vStart, &vDir, &boHit, &dwPolyIndex, NULL, NULL, pfDistance, NULL, NULL);
	if (boHit)
	{
		//交差しているポリゴンの頂点を見つける
		D3DXVECTOR3 vVertex[3];
		FindVerticesOnPoly(pChara->GetMesh(), dwPolyIndex, vVertex);
		D3DXPLANE p;
		//その頂点から平面方程式を得る
		D3DXPlaneFromPoints(&p, &vVertex[0], &vVertex[1], &vVertex[2]);
		//平面方程式の係数が法線の成分
		pvNormal->x = p.a;
		pvNormal->y = p.b;
		pvNormal->z = p.c;

		return true;
	}
	return false;
}

// L:入射ベクトル（レイ） N : ポリゴンの法線
D3DXVECTOR3 Collision::Slip(D3DXVECTOR3 L, D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //滑りベクトル（滑る方向）

	//滑りベクトル S=L-(N * L)/(|N|^2)*N
	S = L - ((D3DXVec3Dot(&N, &L)) / (pow(D3DXVec3Length(&N), 2))) * N;

	return S;
}