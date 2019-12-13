/*============================================

	[Field.cpp]
	Author :　出合翔太

============================================*/

#include "Field.h"

//	スタティック変数
LPDIRECT3DTEXTURE9	Field::m_pTextureModel = NULL;		// テクスチャへのポインタ
LPD3DXMESH			Field::m_pMeshModel = NULL;			// メッシュ情報へのポインタ
LPD3DXBUFFER		Field::m_pBuffMatModel = NULL;		// マテリアル情報へのポインタ
DWORD				Field::m_nNumMatModel;				// マテリアル情報の総数
LPDIRECT3DDEVICE9	Field::m_pDevice;

HRESULT Field::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, D3DXVECTOR3 Angle)
{
	m_pDevice = GetD3DDevice();

	/// <summary>
	/// Xファイルの読み込み
	/// <summary>
	if (FAILED(D3DXLoadMeshFromX("asset/model/dai.x",D3DXMESH_SYSTEMMEM,m_pDevice,NULL,&m_pBuffMatModel,NULL,&m_nNumMatModel,&m_pMeshModel)))
	{
		return E_FAIL;
	}
	
	/// <summary> 変数の初期化 </summary>
	m_position = Pos;
	m_scale = Scale;
	m_angle = Angle;

	return S_OK;
}

void Field::Uninit()
{

}

void Field::Draw()
{
	m_pDevice = GetD3DDevice();

	D3DXMATRIX trans_matrix, rot_matrix, scale_matrix;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	
	D3DXMatrixIdentity(&m_mtxWorldModel);
	D3DXMatrixTranslation(&trans_matrix, m_position.x, m_position.y, m_position.z);
	D3DXMatrixScaling(&scale_matrix, m_scale.x, m_scale.y, m_scale.y);
	m_mtxWorldModel *= scale_matrix * trans_matrix;
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldModel);

	//現在のマテリアルを取得
	m_pDevice->GetMaterial(&matDef);

	//マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		m_pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		//テクスチャの設定
		m_pDevice->SetTexture(0, m_pTextureModel);
		//描画
		m_pMeshModel->DrawSubset(nCntMat);

	}
	//マテリアルをデフォルトに戻す
	m_pDevice->SetMaterial(&matDef);
}

