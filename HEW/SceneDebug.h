/*==============================================

	[SceneDebug.h]
	Author : 出合翔太

==============================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "Character.h"
#include "sprite.h"
#include "Count.h"


//# SceneDebug : 親クラスSceneBase
class SceneDebug: public SceneBase
{
private:
	Character	m_Character;
	//Sprite	m_Sprite;
	Count       m_Count;
public:
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};

