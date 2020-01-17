/*=================================================

	[Character.cpp]
	Author : 出合翔太

=================================================*/

#include "Controller.h"
#include "Character.h"
#include "debugproc.h"
#include "Collision.h"
#include "SceneManager.h"
#include "Field.h"
#include "SceneGame.h"
#include "ObjectManager.h"
#include "camera.h"

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
float				Character::m_frame;				//  frame数カウンタ
static bool			flag;							//! jump用一時y軸跳ね上げ用flag

//	初期化処理
HRESULT Character::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pDevice = GetD3DDevice();

	//Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX("asset/model/human.x", D3DXMESH_SYSTEMMEM, m_pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh)))
	{
		return E_FAIL;
	}
	
	///	<summary>
	///	変数の初期化
	///	</summary>
	m_position = pos;	//	位置
	m_rotation = rot;	//	向き
	m_rotDest = rot;	//	目的の向き
	m_scale = D3DXVECTOR3(100.0f,100.0f,100.0f);
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//ベクトル
	m_grivity = 0.7f;
	//m_pCamera = new CharacterCamera;
	m_count = 0;
	m_score = 0;
	m_frame = 0;

	flag = true;

	return S_OK;
}

//	終了処理
void Character::Uninit()
{
	//delete m_pCamera;
	SAFE_RELEASE(m_pBuffMat);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexture);
}

//	更新処理
void Character::Update()
{
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
	
	Move();			//	移動処理更新
	Collision();	//	当たり判定更新
}

//	描画処理
void Character::Draw()
{
	m_pDevice = GetD3DDevice();
	D3DXMATRIX mtxRot, mtxTranslate,mtxScl;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//	拡縮を反映
	D3DXMatrixScaling(&mtxScl, m_scale.x, m_scale.y, m_scale.y);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

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
int Character::GetScore()
{
	return m_score;
}

void Character::Move()
{
	// 位置移動
	m_position.x += m_velocity.x;
	m_position.y -= m_grivity;
	m_position.z += m_velocity.z;
	// 移動量に慣性をかける
	m_velocity.x += (0.0f - m_velocity.x) * RATE_MOVE_MODEL;
	m_velocity.z += (0.0f - m_velocity.z) * RATE_MOVE_MODEL;
}

void Character::Action()
{
}

void Character::Collision()
{
	/// <summary> 当たり判定
	FLOAT fDistance = 0;
	D3DXVECTOR3 vNormal;
	Field *field = ObjectManager::SetField();
	if (Collision::Collide(m_position, m_velocity, field, &fDistance, &vNormal) && fDistance <= 0.3)
	{
		//当たり状態なので、滑らせる
		m_velocity = Collision::Slip(m_velocity, vNormal);//滑りベクトルを計算

		//滑りベクトル先の地面突起とのレイ判定 ２重に判定	
		if (Collision::Collide(m_position, m_velocity, field, &fDistance, &vNormal) && fDistance <= 0.2)
		{
			//２段目の当たり状態なので、滑らせる おそらく上がる方向		
			m_velocity = Collision::Slip(m_velocity, vNormal);//滑りベクトルを計算
		}
	}
	//m_position.y = -0.7f;
	//ロボット　位置更新
	m_position += m_velocity;

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
	Camera* pCamera = ObjectManager::SetCamera();
	D3DXVECTOR3 CameraRot = pCamera->GetRot();
	/// <summary> 移動の処理　</summary>
	m_velocity.x += sinf(D3DX_PI * 0.0f - CameraRot.y) * VALUE_MOVE_MODEL;
	m_velocity.z -= cosf(D3DX_PI * 0.0f - CameraRot.y) * VALUE_MOVE_MODEL;
	m_rotDest.y = CameraRot.y + D3DX_PI * 0.0f;
	
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
	case ANSWER_SELECT:
		//!	問題文の描画

		//!	カウントダウンを開始
		m_frame++;

		//Z座標
		//プレイヤースタート位置220 ジャンプ台端122.24
		//ジャンプ台の判定分欲しいだろうから150か145
		//(220-150)/3　ってことで

		/*if (m_frame >= 3000 && m_position.z > 220 - (70 / (3 - m_count)))
		{
			
		}*/
		//!	問題文の更新と描画	

		//!if ( カウントダウンが終了したら )
		{
			m_PlayerState = PLAYER_ANSWER;
		}
		break;

	}
}

void Character::AnswerState()
{
	//	ゲッター

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
	m_score++;

	if (m_position.z < 122.3f&&flag == true)
	{
		m_position.y += 10.0f;
		flag = false;	//playerが上昇し続けるのを防ぐため
	}

	//!if ( 地面に着いたら　= yの座標値)
	{
		m_PlayerState = PLAYER_END;
	}
}

void Character::EndState()
{
	//! if ( しばらくたったら )
	{
		SceneManager::ChangeSceneState();
	}
}
