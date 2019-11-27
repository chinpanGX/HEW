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

//# SceneDebug : 親クラスSceneBase
class SceneDebug: public SceneBase
{
private:
	Character			m_Character;	//	Character型のインスタンス
	CharacterCamera		m_CharaCamera;	//	CharacterCamera型のインスタンス
	DebugCamera			m_Camera;		//	DebugCamera型のインスタンス	
	Map					m_Map;			//	Map型のインスタンス
	Sprite				m_Sprite;		//	Sprite型のインスタンス
public:
	//SceneBaseのメンバー関数のオーバーライド
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};

