/*========================================

	[Camera.cpp]
	Author : 出合翔太

========================================*/

#include "Camera.h"
#include "ObjectManager.h"
#include "Controller.h"

// マクロ定義
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))							// 視野角
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z			(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(100000.0f)										// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA	(2.0f)											// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)								// カメラの回転量
#define	INTERVAL_CAMERA_R	(100.0f)										// モデルの視線の先までの距離
#define	RATE_CHASE_CAMERA_V	(0.35f)											// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)											// カメラの注視点への補正係数
#define	CHASE_HEIGHT_V		(10.0f)											// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R		(10.0f)											// 追跡時の注視点の高さ

//	初期化処理
void Camera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 500.0f, -200.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 500.0f, -200.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float vx, vz;
	vx = m_posV.x - m_posR.x;
	vz = m_posV.z - m_posR.z;
	m_fLengthInterval = sqrtf(vx * vx + vz * vz);
	m_fHeightV = CHASE_HEIGHT_V;
	m_fHeightR = CHASE_HEIGHT_R;
}

//	終了処理
void Camera::Uninit()
{
}

//	更新処理
void Camera::Update()
{	
	Character *pPlayer;
	pPlayer = ObjectManager::SetCharacter();	//	Playerインスタンスの取得
	D3DXVECTOR3 posPlayer = pPlayer->GetPos();	//	位置の取得
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();	//	向きの取得
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();	//	移動量の取得
	float fIntervalCamera, fLengthMove;
	float fRateChaseCameraP, fRateChaseCameraR;
	float fHeightFieldPlayer;
	fHeightFieldPlayer = posPlayer.y * 200.0f;	//	現在いる高さ
	fLengthMove = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;	//	移動量
	//	プレイヤーが移動しているとき
	if (movePlayer.x < -0.05f || movePlayer.x > 0.05f || movePlayer.z < -0.05f || movePlayer.z > 0.05f)
	{
		fIntervalCamera = INTERVAL_CAMERA_R + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 10.0f;
		fRateChaseCameraR = 0.10f;
		fRateChaseCameraP = 0.3f;

	}
	else
	{
		fIntervalCamera = INTERVAL_CAMERA_R + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		fRateChaseCameraR = 0.0005f;
		fRateChaseCameraP = 0.3f;
	}

	// 注視点の目的位置
	m_posRDest.x = posPlayer.x - sin(rotPlayer.y) * fIntervalCamera;
	m_posRDest.y = posPlayer.y + m_fHeightR;
	m_posRDest.z = posPlayer.z - cos(rotPlayer.y) * fIntervalCamera;

	// 視点の目的位置
	m_posVDest.x = posPlayer.x - sinf(m_rot.y) * m_fLengthInterval - sin(rotPlayer.y) * fLengthMove;
	m_posVDest.y = posPlayer.y + m_fHeightV + 50.0f;
	m_posVDest.z = posPlayer.z - cosf(m_rot.y) * m_fLengthInterval - cos(rotPlayer.y) * fLengthMove;

	// 注視点の補正
	m_posR.x += (m_posRDest.x - m_posR.x) * fRateChaseCameraR;
	m_posR.y += (m_posRDest.y - m_posR.y) * 1.0f;
	m_posR.z += (m_posRDest.z - m_posR.z) * fRateChaseCameraR;

	// 視点の補正
	m_posV.x += (m_posVDest.x - m_posV.x) * fRateChaseCameraP;
	m_posV.y += (m_posVDest.y - m_posV.y) * fRateChaseCameraP;
	m_posV.z += (m_posVDest.z - m_posV.z) * fRateChaseCameraP;

}

//	カメラのセット
void Camera::Set()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	/// <summary>
	/// ビューマトリックスの作成(カメラ視点、カメラ注視点、カメラ上ベクトル)
	///	<summary>
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	/// <summary>
	/// プロジェクションマトリックスの作成(視野角、アスペクト比、ビュー平面のNearZ値、ビュー平面のFarZ値)
	/// </summary>
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
D3DXVECTOR3 Camera::GetRot()
{
	return m_rot;
}
