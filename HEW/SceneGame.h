/*==================================

	[SceneGame.h]
	Author : 出合翔太

===================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "Character.h"
#include "CharacterCamera.h"
#include "Field.h"

//#	SceneGameクラス:親クラス,SceneBaseを継承した子クラス
class SceneGame:public SceneBase
{
private:
	Character		m_Character;
	CharacterCamera	m_Camera;
	Field			m_Map;
public:
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
	Character*	SetCharacter();
	Field*		SetField();
};
