/*==============================================

	[SceneDebug.h]
	Author : 出合翔太

==============================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "DebugCamera.h"
#include "Map.h"

//# SceneDebug : 親クラスSceneBase
class SceneDebug: public SceneBase
{
	DebugCamera m_Camera;
	Map			m_Map;
public:
	//SceneBaseのメンバー関数のオーバーライド
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};

