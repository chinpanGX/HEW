/*================================================

	[SceneTitle.h]
	Author : 出合翔太
	
================================================*/

#pragma once
#include "SceneBase.h"

//#	SceneGameクラス:親クラス,SceneBaseを継承した子クラス
class SceneTitle : public SceneBase
{
public:
	//	SceneBaseのメンバー関数のオーバーライド
	void Init();	//	初期化処理
	void Uninit();	//	終了処理
	void Update();	//	更新処理
	void Draw();	//	描画処理
};

