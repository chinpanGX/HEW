/*=====================================================

	[SceneBase.h]
	Author : 出合翔太

======================================================*/

#pragma once
#include "main.h"

//#	SceneBaseクラス : 親クラス
class SceneBase
{
public:
	//仮想関数指定
	virtual ~SceneBase() {};	//	デストラクタ
	virtual void Init() = 0;	//	初期化処理
	virtual void Uninit() = 0;	//	終了処理
	virtual void Update() = 0;	//	更新処理
	virtual void Draw() = 0;	//	描画処理
};
