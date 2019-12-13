/*===================================================

	[SceneTitle.h]
	Author : 出合翔太

====================================================*/

#pragma once
#include "SceneBase.h"
#include "Map.h"
#include "Count.h"

//	SCENETILEクラス
/* タイトルシーンを管理するクラス */
class SceneTitle : public SceneBase 
{
private:
	Map			m_Map;
public:
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};

