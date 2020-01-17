/*===================================================

	[SceneTitle.h]
	概要 ：タイトルシーンの管理をする
	Author : 出合翔太

====================================================*/

#pragma once
#include "SceneBase.h"
#include "Count.h"
#include "sprite.h"

//	SCENETILEクラス
/* タイトルシーンを管理するクラス */
class SceneTitle : public SceneBase
{
public:
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};

//	プロトタイプ宣言
bool GetFlag();

