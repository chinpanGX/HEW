/*=================================================

	[Character.cpp]
	Author : 出合翔太

=================================================*/

#include "Controller.h"
#include "Character.h"
#include "CharacterCamera.h"
#include "debugproc.h"
#include "Collision.h"
#include "SceneManager.h"
#include "Collision.h"
#include "Field.h"
#include "SceneGame.h"
#include "ObjectManager.h"

//	マクロ定義
#define	VALUE_MOVE_MODEL	(0.5f)					// 移動速度
#define	RATE_MOVE_MODEL		(0.2f)					// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)		// 回転速度
#define	RATE_ROTATE_MODEL	(0.2f)					// 回転慣性係数

// スタティック変数
LPDIRECT3DTEXTURE9	Character::m_pTexture = NULL;	//	テクスチャへのポインタ
LPD3DXMESH			Character::m_pMesh	= NULL;		//	メッシュ情報へのポインタ
LPD3DXBUFFER		Character::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD				Character::m_nNumMat;			//	マテリアル情報の総数
D3DXMATRIX			Character::m_mtxWorld;			//	ワールドマトリックス
int					Character::m_count;				//	問題数のカウンター

//	初期化処理
HRESULT Character::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pDevice = GetD3DDevice();

	//Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX("asset/model/ri.x", D3DXMESH_SYSTEMMEM, m_pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh)))
	{
		return E_FAIL;
	}
	
	///	<summary>
	///	変数の初期化
	///	</summary>
	m_position = pos;	//	位置
	m_rotation = rot;	//	向き
	m_rotDest = rot;	//	目的の向き
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//ベクトル
	m_grivity = 0.7f;
	m_pCamera = new CharacterCamera;
	m_count = 0;
	m_score = 0;

	return S_OK;
}

//	終了処理
void Character::Uninit()
{
	delete m_pCamera;
	SAFE_RELEASE(m_pBuffMat);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexture);
}

//	更新処理
void Character::Update()
{
	// カメラの取得
	m_pCamera = GetCharCam();

	if (KeyBoard::IsPress(DIK_D) || GamePad::IsPress(0, LEFTSTICK_LEFT))
	{
		if (KeyBoard::IsPress(DIK_W) || GamePad::IsPress(0, LEFTSTICK_UP))
		{// 左奥移動
			m_velocity.x += sinf(-D3DX_PI * 0.75f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(-D3DX_PI * 0.75f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = m_pCamera->rot.y + D3DX_PI * 0.75f;
		}
		else if (KeyBoard::IsPress(DIK_S) || GamePad::IsPress(0, LEFTSTICK_DOWN))
		{// 左手前移動
			m_velocity.x += sinf(-D3DX_PI * 0.25f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(-D3DX_PI * 0.25f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = m_pCamera->rot.y + D3DX_PI * 0.25f;
		}
		else
		{// 左移動
			m_velocity.x += sinf(-D3DX_PI * 0.50f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(-D3DX_PI * 0.50f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = m_pCamera->rot.y + D3DX_PI * 0.50f;
		}
	}
	else if (KeyBoard::IsPress(DIK_A) || GamePad::IsPress(0, LEFTSTICK_RIGHT))
	{
		if (KeyBoard::IsPress(DIK_W) || GamePad::IsPress(0, LEFTSTICK_UP))
		{// 右奥移動
			m_velocity.x += sinf(D3DX_PI * 0.75f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(D3DX_PI * 0.75f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = m_pCamera->rot.y - D3DX_PI * 0.75f;
		}
		else if (KeyBoard::IsPress(DIK_S) || GamePad::IsPress(0, LEFTSTICK_DOWN))
		{// 右手前移動
			m_velocity.x += sinf(D3DX_PI * 0.25f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(D3DX_PI * 0.25f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = m_pCamera->rot.y - D3DX_PI * 0.25f;
		}
		else
		{// 右移動
			m_velocity.x += sinf(D3DX_PI * 0.50f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(D3DX_PI * 0.50f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;

			m_rotDest.y = m_pCamera->rot.y - D3DX_PI * 0.50f;
		}
	}
	else if (KeyBoard::IsPress(DIK_S) || GamePad::IsPress(0, LEFTSTICK_UP))
	{// 前移動
		m_velocity.x += sinf(D3DX_PI * 1.0f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
		m_velocity.z -= cosf(D3DX_PI * 1.0f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;

		m_rotDest.y = m_pCamera->rot.y + D3DX_PI * 1.0f;
	}
	else if (KeyBoard::IsPress(DIK_W) || GamePad::IsPress(0, LEFTSTICK_DOWN))
	{// 後移動
		m_velocity.x += sinf(D3DX_PI * 0.0f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
		m_velocity.z -= cosf(D3DX_PI * 0.0f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;

		m_rotDest.y = m_pCamera->rot.y + D3DX_PI * 0.0f;
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
	float fDiffRotY;
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

	// 位置移動
	m_position.x += m_velocity.x;
	m_position.z += m_velocity.z;

	// 移動量に慣性をかける
	m_velocity.x += (0.0f - m_velocity.x) * RATE_MOVE_MODEL;
	m_velocity.z += (0.0f - m_velocity.z) * RATE_MOVE_MODEL;

	/// <summary>当たり判定</summary>
#if 0	
	// 当たり判定
	FLOAT fDistance = 0;
	D3DXVECTOR3 vNormal;

	if (m_Col.Collide(m_position, m_velocity, &m_XFile, &m_Model, &fDistance, &vNormal) && fDistance <= 0.3)
	{
		//当たり状態なので、滑らせる
		m_velocity = m_Col.Slip(m_velocity, vNormal);//滑りベクトルを計算

		//滑りベクトル先の地面突起とのレイ判定 ２重に判定	
		if (m_Col.Collide(m_position, m_velocity, &m_XFile, &m_Model, &fDistance, &vNormal) && fDistance <= 0.2)
		{
			//２段目の当たり状態なので、滑らせる おそらく上がる方向		
			m_velocity = m_Col.Slip(m_velocity, vNormal);//滑りベクトルを計算
		}
		DebugProc_Print((char*)"当たっている");
		m_position += m_velocity;
	}

	//pos = m_Character.GetMove();
	//move = m_Character.GetMove();



	DebugProc_Print((char*)"Character [%f : %f : %f]\n", m_position.x, m_position.y, m_position.z);
	DebugProc_Print((char*)"\n");
#endif

	DebugProc_Print((char*)"%f,%f,%f",m_position.x,m_position.y,m_position.z);

	//RenderRay(m_pDevice, m_position, m_velocity);
	//m_position.y -= m_grivity;
	/// <summary> 当たり判定

	FLOAT fDistance=0;
	D3DXVECTOR3 vNormal;
	Field *field = ObjectManager::SetField();

	//	重力をかける
	if (KeyBoard::IsPress(DIK_SPACE))
	{
		m_position.y -= m_grivity;
	}

	//	上昇
	if (KeyBoard::IsPress(DIK_Q))
	{
		m_position.y += m_grivity;
	}

	//m_position.y = -0.7f;
	if( Collision::Collide(m_position,m_velocity, field,&fDistance,&vNormal) && fDistance<=0.3)
	{
		//当たり状態なので、滑らせる
		m_velocity= Collision::Slip(m_velocity,vNormal);//滑りベクトルを計算

		//滑りベクトル先の地面突起とのレイ判定 ２重に判定	
		if(Collision::Collide(m_position,m_velocity,field,&fDistance,&vNormal)&& fDistance<=0.2 )
		{				
			//２段目の当たり状態なので、滑らせる おそらく上がる方向		
			m_velocity= Collision::Slip(m_velocity,vNormal);//滑りベクトルを計算
		}		
	}
	//m_position.y = -0.7f;
	//ロボット　位置更新
	m_position += m_velocity;	

	///	<summary> 
	///	ステート
	///	当たり判定が完成したら、実行
	///</summary>
#if 0
	//	ステート
	switch (m_PlayerState)
	{
	case PLAYER_INIT:
		InitState();
		break;
	case PLAYER_MOVE:
		MoveState();
		break;
	case PlAYER_ANSWERSTAY:
		AnswerstayState();
		break;
	case PLAYER_ANSWER: 
		AnswerState();
		break;
	case PLAYER_JUMP:
		JumpState();
		break;
	case PLAYER_END:
		EndState();
		break;
	}
#endif // 0
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
	D3DXMatrixTranslation(&mtxTranslate, m_position.x, m_position.y, m_position.z);
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

//	スコアのゲッター
int Character::Score()
{
	return m_score;
}

//	ステートの初期化
void Character::InitState()
{
	//!	カウントダウン

	//if (カウントがゼロになったら)
	{
		m_PlayerState = PLAYER_MOVE;
	}
}

//	プレイヤーのスタート
void Character::MoveState()
{
	/// <summary> 移動の処理　</summary>
	m_velocity.x += sinf(D3DX_PI * 0.0f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
	m_velocity.z -= cosf(D3DX_PI * 0.0f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
	m_rotDest.y = m_pCamera->rot.y + D3DX_PI * 0.0f;
	
	m_position.y -= m_velocity.y;	//	重力の値を加算代入
	m_position.z += m_velocity.z;
	m_velocity.z += (0.0f - m_velocity.z) * RATE_MOVE_MODEL;	//	慣性
	
	/// <summary>
	/// 関数の呼び出し回数を数える
	///	</summary>
	m_count++;
	if (m_count >= 3)	//	4回目ならジャンプ
	{
		m_PlayerState = PLAYER_JUMP;
	}
	else
	{
		m_PlayerState = PlAYER_ANSWERSTAY;
	}
}

void Character::AnswerstayState()
{
	float fDiffRotY;
	switch (m_AnsawerStayState)
	{
	case ANSWER_DROW:
		//!	問題文の描画
		
		//!if ( 問題の選出、描画が完了したら )
		{
			m_AnsawerStayState = ANSWER_SELECT;
		}
		break;

	case ANSWER_SELECT:

		//!	カウントダウンを開始

		//	移動
		if (KeyBoard::IsPress(DIK_A) || GamePad::IsPress(0,LEFTSTICK_RIGHT))
		{
			m_velocity.x += sinf(D3DX_PI * 0.50f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(D3DX_PI * 0.50f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_rotDest.y = m_pCamera->rot.y - D3DX_PI * 0.50f;
		}
		if (KeyBoard::IsPress(DIK_D) || GamePad::IsPress(0, LEFTSTICK_LEFT))
		{
			m_velocity.x += sinf(-D3DX_PI * 0.50f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_velocity.z -= cosf(-D3DX_PI * 0.50f - m_pCamera->rot.y) * VALUE_MOVE_MODEL;
			m_rotDest.y = m_pCamera->rot.y + D3DX_PI * 0.50f;
		}
		m_position.x += m_velocity.x;	//	x座標しか移動させない

		//!if ( カウントダウンが終了したら )
		{
			m_PlayerState = PLAYER_ANSWER;
		}
		break;

	}
}

void Character::AnswerState()
{
	/// <sumamry>
	///	当たり判定はコリジョンのリターンフラグで判別する
	///	</summaey>
	//!if ( 正解 )
	{
		//	スピード補正
		m_velocity.z *= 1.05f;
	}
	//!else	不正解
	{
		//	何もしない
	}
	m_PlayerState = PLAYER_MOVE;
}

void Character::JumpState()
{
	/// <summary>
	///	関数を実行している間、更新する 
	///	60FPS = 1 の更新速度
	///	</summary>
	m_score++;
	//!if ( 地面に着いたら　= yの座標値)
	{
		m_PlayerState = PLAYER_END;
	}
}

void Character::EndState()
{
	//!	飛距離の描画

	//! if ( しばらくたったら )
	{
		SceneManager::ChangeSceneState();
	}
}
