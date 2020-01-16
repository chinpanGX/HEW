//=============================================================================
//
// カメラ処理 [camera.cpp]
//
//=============================================================================
#include "camera.h"
#include "Character.h"
#include "input.h"
#include "debugproc.h"
#include "ObjectManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAM_POS_V_X        (0.0f)                                          
#define CAM_POS_V_Y        (100.0f)                                        
#define CAM_POS_V_Z        (250.0f)                                        
#define CAM_POS_R_X        (0.0f)                                          
#define CAM_POS_R_Y        (50.0f)                                         
#define CAM_POS_R_Z        (-30.0f)                                        
#define VIEW_ANGLE        (D3DXToRadian(45.0f))                            
#define VIEW_ASPECT        ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)    
#define VIEW_NEAR_Z        (10.0f)                                         
#define VIEW_FAR_Z        (1000.0f)                                        
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

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CAMERA	g_camera;		// カメラ情報

//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT Camera_Initialize(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, 250.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 50.0f, -30.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fRateRotAuto = 0.01f;

	float vx,vz;
	vx = g_camera.posV.x - g_camera.posR.x;
	vz = g_camera.posV.z - g_camera.posR.z;
	g_camera.fLengthInterval = sqrtf(vx * vx + vz * vz);

	g_camera.fHeightV = CHASE_HEIGHT_V;
	g_camera.fHeightR = CHASE_HEIGHT_R;

	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void Camera_Finalize(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void Camera_Update(void)
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
	/*
	if (Keyboard_IsPress(DIK_T))
	{// 注視点上昇
		g_camera.fHeightR += 1.0f;
		if(g_camera.fHeightR > 100.0f)
		{
			g_camera.fHeightR = 100.0f;
		}
	}
	if (Keyboard_IsPress(DIK_B))
	{// 注視点下降
		g_camera.fHeightR -= 1.0f;
		if(g_camera.fHeightR < -200.0f)
		{
			g_camera.fHeightR = -200.0f;
		}
	}

	if (Keyboard_IsPress(DIK_Y))
	{// 視点上昇
		g_camera.fHeightV += 1.0f;
		if(g_camera.fHeightV > 200.0f)
		{
			g_camera.fHeightV = 200.0f;
		}
	}
	if (Keyboard_IsPress(DIK_N))
	{// 視点下降
		g_camera.fHeightV -= 1.0f;
		if(g_camera.fHeightV < -100.0f)
		{
			g_camera.fHeightV = -100.0f;
		}
	}

	if (Keyboard_IsPress(DIK_U))
	{// ズームイン
		if(g_camera.fLengthInterval > 100.0f)
		{
			g_camera.fLengthInterval -= 1.0f;
			g_camera.fHeightV -= 0.35f;
		}
	}
	if (Keyboard_IsPress(DIK_M))
	{// ズームアウト
		if(g_camera.fLengthInterval < 300.0f)
		{
			g_camera.fLengthInterval += 1.0f;
			g_camera.fHeightV += 0.35f;
		}
	}

	if (Keyboard_IsPress(DIK_Z))
	{// 視点旋回「左」
		g_camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLengthInterval;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLengthInterval;
	}

	if (Keyboard_IsPress(DIK_C))
	{// 視点旋回「右」
		g_camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLengthInterval;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLengthInterval;
	}
	*/
	// 注視点の目的位置
	g_camera.posRDest.x = posPlayer.x - sin(rotPlayer.y) * fIntervalCamera;
	g_camera.posRDest.y = posPlayer.y + g_camera.fHeightR;
	g_camera.posRDest.z = posPlayer.z - cos(rotPlayer.y) * fIntervalCamera;

	// 視点の目的位置
	g_camera.posVDest.x = posPlayer.x - sinf(g_camera.rot.y) * g_camera.fLengthInterval - sin(rotPlayer.y) * fLengthMove;
	g_camera.posVDest.y = posPlayer.y + g_camera.fHeightV;
	g_camera.posVDest.z = posPlayer.z - cosf(g_camera.rot.y) * g_camera.fLengthInterval - cos(rotPlayer.y) * fLengthMove;

	// 注視点の補正
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * fRateChaseCameraR;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.10f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * fRateChaseCameraR;

	// 視点の補正
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * fRateChaseCameraP;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * fRateChaseCameraP;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * fRateChaseCameraP;

	DebugProc_Print((char*)"[カメラの視点  ：(%f : %f : %f)]\n", g_camera.posV.x, g_camera.posV.y, g_camera.posV.z);
	DebugProc_Print((char*)"[カメラの注視点：(%f : %f : %f)]\n", g_camera.posR.x, g_camera.posR.y, g_camera.posR.z);
	DebugProc_Print((char*)"[カメラの向き  ：(%f)]\n", g_camera.rot.y);
	DebugProc_Print((char*)"\n");
	DebugProc_Print((char*)"*** カメラ操作 ***\n");
	DebugProc_Print((char*)"視点上昇     : [ Ｙ ]\n");
	DebugProc_Print((char*)"視点下降     : [ Ｎ ]\n");
	DebugProc_Print((char*)"注視点上昇   : [ Ｔ ]\n");
	DebugProc_Print((char*)"注視点下降   : [ Ｂ ]\n");
	DebugProc_Print((char*)"ズームイン   : [ Ｕ ]\n");
	DebugProc_Print((char*)"ズームアウト : [ Ｍ ]\n");
	DebugProc_Print((char*)"\n");
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void Camera_SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView, 
						&g_camera.posV,		// カメラの視点
						&g_camera.posR,		// カメラの注視点
						&g_camera.vecU);		// カメラの上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
								VIEW_ANGLE,			// 視野角
								VIEW_ASPECT,		// アスペクト比
								VIEW_NEAR_Z,		// ビュー平面のNearZ値
								VIEW_FAR_Z);		// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//=============================================================================
// カメラの取得
//=============================================================================
CAMERA *GetCamera(void)
{
	return &g_camera;
}

