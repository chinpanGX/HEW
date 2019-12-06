/*==============================================

	[SceneDebug.h]
	Author : 出合翔太

==============================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "DebugCamera.h"
#include "Map.h"
#include "Character.h"
#include "sprite.h"
#include "Count.h"


//# SceneDebug : 親クラスSceneBase
class SceneDebug: public SceneBase
{
private:
	Character	m_Character;
	DebugCamera m_Camera;
	Map			m_Map;
	//Sprite		m_Sprite;
	Count       m_Count;
public:
	//SceneBaseのメンバー関数のオーバーライド
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};

