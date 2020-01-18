/*==================================

	[SceneGame.h]
	概要 : ゲームシーンを管理する
	Author : 出合翔太

===================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "Character.h"
#include "Field.h"
#include "camera.h"

//#	SceneGameクラス:親クラス,SceneBaseを継承した子クラス
class SceneGame:public SceneBase
{
private:
	Character		m_Character;
	Field			m_Map;
	Camera			m_Camera;
	Score			m_Score;
	bool			EndCheck();
public:
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
	Character*	SetCharacter();
	Field*		SetField();
	Camera*		SetCamera();
};
