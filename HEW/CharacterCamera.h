/*====================================================

	[CharacterCamera.h]
	Author : 出合翔太

=====================================================*/

#pragma once
#include "main.h"
#include "Camera.h"

//#	CharacterCameraクラス : 基底クラスCameraの派生
/* キャラクターにつけるカメラ */
class CharacterCamera
{
private:
	//メンバ変数
	D3DXVECTOR3			posV;			// 視点（カメラの位置）
	D3DXVECTOR3			posR;			// 注視点（カメラはどこを見ているのか）
	D3DXVECTOR3			vecU;			// 上方向ベクトル（カメラの上方向はｙがプラス）座標は（０，１，０）
	D3DXMATRIX			mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX			mtxView;		// ビューマトリックス
	LPDIRECT3DDEVICE9	pDevice;		//　デバイスの取得用変数
public:
	D3DXVECTOR3			rot;

public:
	void Init();
	void Uninit();
	void Update();
	void Set();
};

CharacterCamera* GetCharCam();