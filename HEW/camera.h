/*=============================================================================

	camera.h
	Author : 出合翔太

=============================================================================*/

#pragma once
#include "main.h"

class Camera
{
private:
	D3DXVECTOR3 posV;			// カメラの視点
	D3DXVECTOR3 posR;			// カメラの注視点
	D3DXVECTOR3 vecU;			// カメラの上方向
	D3DXVECTOR3 posVDest;		// カメラの視点の目的位置
	D3DXVECTOR3 posRDest;		// カメラの注視点の目的位置
	D3DXVECTOR3 rot;			// カメラの回転
	float fLengthInterval;		// カメラの視点と注視点の距離
	float fHeightV;				// カメラの視点の高さ
	float fHeightR;				// カメラの注視点の高さ
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	float fRateRotAuto;			// 自動回り込み係数
	bool bMoveAuto;				// 自動回り込みON/OFF
public:
	HRESULT Init();
	void Uninit();
	void Update();
	void Set();
	D3DXVECTOR3 GetRot();
};

#if 0
//*****************************************************************************
// カメラの構造体
//*****************************************************************************
struct CAMERA
{
	D3DXVECTOR3 posV;			// カメラの視点
	D3DXVECTOR3 posR;			// カメラの注視点
	D3DXVECTOR3 vecU;			// カメラの上方向
	D3DXVECTOR3 posVDest;		// カメラの視点の目的位置
	D3DXVECTOR3 posRDest;		// カメラの注視点の目的位置
	D3DXVECTOR3 rot;			// カメラの回転
	float fLengthInterval;		// カメラの視点と注視点の距離
	float fHeightV;				// カメラの視点の高さ
	float fHeightR;				// カメラの注視点の高さ
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	float fRateRotAuto;			// 自動回り込み係数
	bool bMoveAuto;				// 自動回り込みON/OFF
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Camera_Initialize(void);
void Camera_Finalize(void);
void Camera_Update(void);

void Camera_SetCamera(void);
CAMERA *GetCamera(void);

#endif

