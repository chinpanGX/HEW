/*==================================

	[SceneGame.h]
	概要 : ゲームシーンを管理する
	Author : 出合翔太

===================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"

//#	SceneGameクラス:親クラス,SceneBaseを継承した子クラス
class SceneGame:public SceneBase
{
private:

	bool			EndCheck();
public:
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};
