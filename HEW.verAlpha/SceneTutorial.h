/*======================================================

	[SceneTutorial.h]
	Author : 出合翔太

======================================================*/

#pragma once
#include "SceneBase.h"

//# SceneTutorialクラス
/* チュートリアルシーンを管理するクラス */
class SceneTutorial : public SceneBase
{
public:	
	//SceneBaseのメンバー関数のオーバーライド
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};

