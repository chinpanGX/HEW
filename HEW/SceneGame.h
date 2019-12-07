/*==================================

	[SceneGame.h]
	Author : 出合翔太

===================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "Character.h"
#include "DebugCamera.h"
#include "Map.h"


//#	SceneGameクラス:親クラス,SceneBaseを継承した子クラス
class SceneGame:public SceneBase
{
private:
	Character	m_Character;
	DebugCamera m_Camera;
	//Map			m_Map;
//	Count       m_Count;
public:
	//SceneBaseのメンバー関数のオーバーライド
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};

