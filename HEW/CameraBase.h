/*===============================================

	[CameraBase.h]
	Author : 出合翔太

=================================================*/

#pragma once

//#	CameraBaseクラス
/* カメラの設定を管理する抽象クラス */
class CameraBase
{
public:
	//	純粋仮想関数指定
	virtual	void Init() = 0;		//	カメラの初期化
	virtual	void Uninit() = 0;		//	カメラの終了処理
	virtual void Update() = 0;		//	カメラの更新処理
	virtual	void Set() = 0;			//	カメラの設定
};



