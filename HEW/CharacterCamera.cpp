/*================================================

	[CharacterCamera.cpp]
	Author : 出合翔太

=================================================*/

#include "CharacterCamera.h"
#include "Character.h"

//　マクロ定義
#define	CAM_POS_V_X		(0.0f)											// カメラの視点初期位置(X座標)
#define	CAM_POS_V_Y		(100.0f)											// カメラの視点初期位置(Y座標)
#define	CAM_POS_V_Z		(250.0f)											// カメラの視点初期位置(Z座標)
#define	CAM_POS_R_X		(0.0f)											// カメラの注視点初期位置(X座標)
#define	CAM_POS_R_Y		(50.0f)											// カメラの注視点初期位置(Y座標)
#define	CAM_POS_R_Z		(-30.0f)											// カメラの注視点初期位置(Z座標)
#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値	値より近いと描画しない
#define	VIEW_FAR_Z		(1000.0f)										// ビュー平面のFarZ値	値より遠いと描画しない

CharacterCamera g_CharCamera;

void CharacterCamera::Init()
{
	g_CharCamera.posV = D3DXVECTOR3(CAM_POS_V_X, CAM_POS_V_Y, CAM_POS_V_Z);	//カメラ位置
	g_CharCamera.posR = D3DXVECTOR3(CAM_POS_R_X, CAM_POS_R_X, CAM_POS_R_X);	//注視点
	g_CharCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//カメラの上ベクトル
}

void CharacterCamera::Uninit()
{

}

void CharacterCamera::Update()
{

	//D3DXVECTOR3 GetMove();
	//g_CharCamera.posV.z += sinf(D3DX_PI * 0.0f -rot.y) * 0.5f;
	//g_CharCamera.posR.z -= cosf(D3DX_PI * 0.0f -rot.y) * 0.5f;
	/// 位置移動
	//g_CharCamera.posV.x += 0.;
	//g_CharCamera.posV.z -= 0.5f;
	//g_CharCamera.posV.z -= 0.5f;
	//g_CharCamera.posR.z -= 0.5f;
}

void CharacterCamera::Set()
{
	//デバイスの取得
	pDevice = GetD3DDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_CharCamera.mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_CharCamera.mtxProjection,
		VIEW_ANGLE,				// ビュー平面の視野角
		VIEW_ASPECT,			// ビュー平面のアスペクト比
		VIEW_NEAR_Z,			// ビュー平面のNearZ値
		VIEW_FAR_Z);			// ビュー平面のFarZ値

								// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_CharCamera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_CharCamera.mtxView);	//	単位行列:行列の初期化するときに使う

									// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_CharCamera.mtxView,
		&g_CharCamera.posV,		// カメラの視点
		&g_CharCamera.posR,		// カメラの注視点
		&g_CharCamera.vecU);	// カメラの上方向ベクトル

				// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_CharCamera.mtxView);
}


CharacterCamera* GetCharCam()
{
	return	&g_CharCamera;
}