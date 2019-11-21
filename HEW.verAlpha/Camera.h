/*=====================================

	[Camera.h]
	Author : 出合翔太

=====================================*/

#pragma once
#include "main.h"
#include "CameraBase.h"

//# Cameraクラス : 抽象クラス(CameraBase)
class Camera : public CameraBase
{
protected:
	static D3DXVECTOR3			posV;			//	視点（カメラの位置）
	static D3DXVECTOR3			posR;			//	注視点（カメラはどこを見ているのか）
	static D3DXVECTOR3			vecU;			//	上方向ベクトル（カメラの上方向はｙがプラス）座標は（０，１，０）
	static D3DXMATRIX			mtxProjection;	//	プロジェクションマトリックス
	static D3DXMATRIX			mtxView;		//	ビューマトリックス
	static LPDIRECT3DDEVICE9	pDevice;		//　デバイスの取得用変数
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Set();
};

