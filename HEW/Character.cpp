/*=================================================

	[Character.cpp]
	Author : 出合翔太

=================================================*/

#include "Controller.h"
#include "Character.h"
#include "CharacterCamera.h"

//	マクロ定義
#define	VALUE_MOVE_MODEL	(0.5f)					// 移動速度
#define	RATE_MOVE_MODEL		(0.2f)					// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)		// 回転速度
#define	RATE_ROTATE_MODEL	(0.2f)					// 回転慣性係数


// スタティック変数
LPDIRECT3DTEXTURE9	Character::m_pTexture = NULL;	//	テクスチャへのポインタ
LPD3DXMESH			Character::m_pMesh	= NULL;		//	メッシュ情報へのポインタ
LPD3DXBUFFER		Character::m_pBuffMat = NULL;		// マテリアル情報へのポインタ
DWORD				Character::m_nNumMat;	//	マテリアル情報の総数
D3DXMATRIX			Character::m_mtxWorld;	//	ワールドマトリックス

//	初期化処理
HRESULT Character::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pDevice = GetD3DDevice();
	
	//Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX("asset/model/ri.x", D3DXMESH_SYSTEMMEM, m_pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh)))
	{
		return E_FAIL;
	}

	m_gravity = 0.9f;	//	重力	

	m_position = pos;	//	位置
	m_rotation = rot;	//	向き
	m_rotDest = rot;	//	目的の向き
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動
	
	return S_OK;
}

//	終了処理
void Character::Uninit()
{
	SAFE_RELEASE(m_pBuffMat);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexture);
}

//	更新処理
void Character::Update()
{
	m_velocity.y += m_gravity;	//	重力の値を加算代入
	CharacterCamera *pCamera;
	float fDiffRotY;

	// カメラの取得
	pCamera = GetCharCam();

	if (KeyBoard::IsPress(DIK_A) || GamePad::IsPress(0, LEFTSTICK_LEFT))
	{
		if (KeyBoard::IsPress(DIK_W) || GamePad::IsPress(0, LEFTSTICK_UP))
		{// 左奥移動
			m_velocity.x += sinf(-D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(-D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
		}
		else if (KeyBoard::IsPress(DIK_S) || GamePad::IsPress(0, LEFTSTICK_DOWN))
		{// 左手前移動
			m_velocity.x += sinf(-D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(-D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
		}
		else
		{// 左移動
			m_velocity.x += sinf(-D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(-D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = pCamera->rot.y + D3DX_PI * 0.50f;
		}
	}
	else if (KeyBoard::IsPress(DIK_D) || GamePad::IsPress(0, LEFTSTICK_RIGHT))
	{
		if (KeyBoard::IsPress(DIK_W) || GamePad::IsPress(0, LEFTSTICK_UP))
		{// 右奥移動
			m_velocity.x += sinf(D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
		}
		else if (KeyBoard::IsPress(DIK_S) || GamePad::IsPress(0, LEFTSTICK_DOWN))
		{// 右手前移動
			m_velocity.x += sinf(D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
		}
		else
		{// 右移動
			m_velocity.x += sinf(D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = pCamera->rot.y - D3DX_PI * 0.50f;
		}
	}
	else if (KeyBoard::IsPress(DIK_W) || GamePad::IsPress(0, LEFTSTICK_UP))
	{// 前移動
		m_velocity.x += sinf(D3DX_PI * 1.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;
		m_velocity.z -= cosf(D3DX_PI * 1.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;

		m_rotDest.y = pCamera->rot.y + D3DX_PI * 1.0f;
	}
	else if (KeyBoard::IsPress(DIK_S) || GamePad::IsPress(0, LEFTSTICK_DOWN))
	{// 後移動
		m_velocity.x += sinf(D3DX_PI * 0.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;
		m_velocity.z -= cosf(D3DX_PI * 0.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;

		m_rotDest.y = pCamera->rot.y + D3DX_PI * 0.0f;
	}

	if (KeyBoard::IsPress(DIK_Q) || GamePad::IsPress(0, PS4RIGHTSTICK_LEFT))
	{// 左回転
		m_rotDest.y -= VALUE_ROTATE_MODEL;
		if (m_rotDest.y < -D3DX_PI)
		{
			m_rotDest.y += D3DX_PI * 2.0f;
		}
	}
	if (KeyBoard::IsPress(DIK_E) || GamePad::IsPress(0, PS4RIGHTSTICK_RIGHT))
	{// 右回転
		m_rotDest.y += VALUE_ROTATE_MODEL;
		if (m_rotDest.y > D3DX_PI)
		{
			m_rotDest.y -= D3DX_PI * 2.0f;
		}
	}

	// 目的の角度までの差分
	fDiffRotY = m_rotDest.y - m_rotation.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// 目的の角度まで慣性をかける
	m_rotation.y += fDiffRotY * RATE_ROTATE_MODEL;
	if (m_rotation.y > D3DX_PI)
	{
		m_rotation.y -= D3DX_PI * 2.0f;
	}
	if (m_rotation.y < -D3DX_PI)
	{
		m_rotation.y += D3DX_PI * 2.0f;
	}

	/// 位置移動
	m_position.x += m_velocity.x;
	m_position.z += m_velocity.z;

	// 移動量に慣性をかける
	m_velocity.x += (0.0f - m_velocity.x) * RATE_MOVE_MODEL;
	m_velocity.z += (0.0f - m_velocity.z) * RATE_MOVE_MODEL;
	//	ステート
	switch (m_state)
	{
	case PLAYER_INIT:
		break;
	case PLAYER_STRAT:
		break;
	case PlAYER_ANSWERSTAY:
		break;
	case PLAYER_ANSWER: 
		break;
	case PLAYER_JUMP:
		break;
	case PLAYER_END:
		break;
	}
}

//	描画処理
void Character::Draw()
{
	m_pDevice = GetD3DDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotation.y, m_rotation.x, m_rotation.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_position.x, m_velocity.y, m_position.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	//ワールドマトリックスの設定
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	m_pDevice->GetMaterial(&matDef);

	//マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		m_pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		//テクスチャの設定
		m_pDevice->SetTexture(0, m_pTexture);
		//描画
		m_pMesh->DrawSubset(nCntMat);

	}
	//マテリアルをデフォルトに戻す
	m_pDevice->SetMaterial(&matDef);
}

//!	ゲッター
//	位置のゲッター
D3DXVECTOR3 Character::GetPos()
{
	return m_position;
}

//	回転のゲッター
D3DXVECTOR3 Character::GetRot()
{
	return m_rotation;
}

//	移動のゲッター
D3DXVECTOR3 Character::GetMove()
{
	return m_velocity;
}

//	マトリクスのゲッター
D3DXMATRIX Character::GetMat()
{
	return m_mtxWorld;
}

//	メッシュのゲッター
LPD3DXMESH Character::GetMesh()
{
	return  m_pMesh;
}

//!	ステート用関数
//	スタート時
void Character::Strat()
{
}

//	解答まち
void Character::Answerstay()
{
}

//	解答
void Character::Answer()
{
}

//	ジャンプ
void Character::Jump()
{
}

//	ステート終了
void Character::End()
{
}
