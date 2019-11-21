/*===============================================

	[Camera.h]
	Author : 出合翔太

=================================================*/

#pragma once
#include "main.h"
#include "CameraBase.h"

//#	Cameraクラス
/* カメラの設定を管理するクラス */
class Camera : public CameraBase
{
protected:
	//メンバ変数
	D3DXVECTOR3			posV;			// 視点（カメラの位置）
	D3DXVECTOR3			posR;			// 注視点（カメラはどこを見ているのか）
	D3DXVECTOR3			vecU;			// 上方向ベクトル（カメラの上方向はｙがプラス）座標は（０，１，０）
	D3DXMATRIX			mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX			mtxView;		// ビューマトリックス
	LPDIRECT3DDEVICE9	pDevice;		//　デバイスの取得用変数

public:
	//　メンバ関数
	virtual void Init();		//カメラの初期化
	virtual void Uninit();		//カメラの終了処理
	virtual void Update();
	virtual void Set();			//カメラの設定
};



