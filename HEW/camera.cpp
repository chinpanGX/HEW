/*========================================================

	[Camera.cpp]
	Author : 出合翔太

==========================================================*/

#include "camera.h"
#include "Character.h"
#include "debugproc.h"
#include "ObjectManager.h"

//	マクロ定義
#define VIEW_ANGLE          (D3DXToRadian(45.0f))                            
#define VIEW_ASPECT         ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)    
#define VIEW_NEAR_Z         (10.0f)                                         
#define VIEW_FAR_Z          (1000.0f)                                        
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))							// 視野角
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z			(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(100000.0f)										// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA	(2.0f)											// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)								// カメラの回転量
#define	INTERVAL_CAMERA_R	(12.5f)					// モデルの視線の先までの距離
#define	RATE_CHASE_CAMERA_V	(0.35f)					// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)					// カメラの注視点への補正係数
#define	CHASE_HEIGHT_V		(100.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R		(0.0f)					// 追跡時の注視点の高さ

// カメラの初期化
HRESULT Camera::Init()
{
	posV = D3DXVECTOR3(0.0f, 100.0f, -250.0f);
	posR = D3DXVECTOR3(0.0f, 50.0f, -30.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	posVDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fRateRotAuto = 0.01f;

	float vx,vz;
	vx = posV.x - posR.x;
	vz = posV.z - posR.z;
	fLengthInterval = sqrtf(vx * vx + vz * vz);

	fHeightV = CHASE_HEIGHT_V;
	fHeightR = CHASE_HEIGHT_R;

	return S_OK;
}

// カメラの終了処理
void Camera::Uninit()
{
}

// カメラの更新処理
void Camera::Update()
{
	Character *pPlayer;
	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 rotPlayer;
	D3DXVECTOR3 movePlayer;
	float fIntervalCamera, fLengthMove;
	float fRateChaseCameraP, fRateChaseCameraR;
	float fHeightFieldPlayer;

	// プレイヤーを取得
	pPlayer = ObjectManager::SetCharacter();

	// プレイヤーの位置取得
	posPlayer = pPlayer->m_position;

	// プレイヤーの目的の向き取得
	rotPlayer = pPlayer->m_rotation;

	// プレイヤーの移動量取得
	movePlayer = pPlayer->m_velocity;

	// プレイヤーが現在いる高さ
	fHeightFieldPlayer = posPlayer.y;

	// プレイヤーの移動量
	fLengthMove = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;

	if(movePlayer.x < -0.05f || movePlayer.x > 0.05f
	|| movePlayer.z < -0.05f || movePlayer.z > 0.05f)
	{// モデルが移動中
		fIntervalCamera = INTERVAL_CAMERA_R + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 10.0f;
		fRateChaseCameraR = 0.10f;
    	fRateChaseCameraP = 0.30f;
	}
	else
	{// モデルが停止中
		fIntervalCamera = INTERVAL_CAMERA_R + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		fRateChaseCameraR = 0.005f;
    	fRateChaseCameraP = 0.30f;
	}

#if 0
	if (KeyBoard::IsPress(DIK_T))
	{// 注視点上昇
		fHeightR += 1.0f;
		if(fHeightR > 100.0f)
		{
			fHeightR = 100.0f;
		}
	}
	if (KeyBoard::IsPress(DIK_B))
	{// 注視点下降
		fHeightR -= 1.0f;
		if(fHeightR < -200.0f)
		{
			fHeightR = -200.0f;
		}
	}

	if (KeyBoard::IsPress(DIK_Y))
	{// 視点上昇
		fHeightV += 1.0f;
		if(fHeightV > 200.0f)
		{
			fHeightV = 200.0f;
		}
	}
	if (KeyBoard::IsPress(DIK_N))
	{// 視点下降
		fHeightV -= 1.0f;
		if(fHeightV < -100.0f)
		{
			fHeightV = -100.0f;
		}
	}

	if (KeyBoard::IsPress(DIK_U))
	{// ズームイン
		if(fLengthInterval > 100.0f)
		{
			fLengthInterval -= 1.0f;
			fHeightV -= 0.35f;
		}
	}
	if (KeyBoard::IsPress(DIK_M))
	{// ズームアウト
		if(fLengthInterval < 300.0f)
		{
			fLengthInterval += 1.0f;
			fHeightV += 0.35f;
		}
	}

	if (KeyBoard::IsPress(DIK_Z))
	{// 視点旋回「左」
		rot.y += VALUE_ROTATE_CAMERA;
		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2.0f;
		}

		posV.x = posR.x - sinf(rot.y) * fLengthInterval;
		posV.z = posR.z - cosf(rot.y) * fLengthInterval;
	}

	if (KeyBoard::IsPress(DIK_C))
	{// 視点旋回「右」
		rot.y -= VALUE_ROTATE_CAMERA;
		if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}

		posV.x = posR.x - sinf(rot.y) * fLengthInterval;
		posV.z = posR.z - cosf(rot.y) * fLengthInterval;
	}
	
	// 注視点の目的位置
	posRDest.x = posPlayer.x - sin(rotPlayer.y) * fIntervalCamera;
	posRDest.y = posPlayer.y + fHeightR;
	posRDest.z = posPlayer.z - cos(rotPlayer.y) * fIntervalCamera;

	// 視点の目的位置
	posVDest.x = posPlayer.x - sinf(rot.y) * fLengthInterval - sin(rotPlayer.y) * fLengthMove;
	posVDest.y = posPlayer.y + fHeightV;
	posVDest.z = posPlayer.z - cosf(rot.y) * fLengthInterval - cos(rotPlayer.y) * fLengthMove;

	// 注視点の補正
	posR.x += (posRDest.x - posR.x) * fRateChaseCameraR;
	posR.y += (posRDest.y - posR.y) * 0.10f;
	posR.z += (posRDest.z - posR.z) * fRateChaseCameraR;

	// 視点の補正
	posV.x += (posVDest.x - posV.x) * fRateChaseCameraP;
	posV.y += (posVDest.y - posV.y) * fRateChaseCameraP;
	posV.z += (posVDest.z - posV.z) * fRateChaseCameraP;

	DebugProc_Print((char*)"[カメラの視点  ：(%f : %f : %f)]\n", posV.x, posV.y, posV.z);
	DebugProc_Print((char*)"[カメラの注視点：(%f : %f : %f)]\n", posR.x, posR.y, posR.z);
	DebugProc_Print((char*)"[カメラの向き  ：(%f)]\n", rot.y);
	DebugProc_Print((char*)"\n");
	DebugProc_Print((char*)"*** カメラ操作 ***\n");
	DebugProc_Print((char*)"視点上昇     : [ Ｙ ]\n");
	DebugProc_Print((char*)"視点下降     : [ Ｎ ]\n");
	DebugProc_Print((char*)"注視点上昇   : [ Ｔ ]\n");
	DebugProc_Print((char*)"注視点下降   : [ Ｂ ]\n");
	DebugProc_Print((char*)"ズームイン   : [ Ｕ ]\n");
	DebugProc_Print((char*)"ズームアウト : [ Ｍ ]\n");
	DebugProc_Print((char*)"\n");
#endif
}

// カメラの設定処理
void Camera::Set()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView, 
						&posV,		// カメラの視点
						&posR,		// カメラの注視点
						&vecU);		// カメラの上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
								VIEW_ANGLE,			// 視野角
								VIEW_ASPECT,		// アスペクト比
								VIEW_NEAR_Z,		// ビュー平面のNearZ値
								VIEW_FAR_Z);		// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

D3DXVECTOR3 Camera::GetRot()
{
	return rot;
}
