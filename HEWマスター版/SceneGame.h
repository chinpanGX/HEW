/*==================================

	[SceneGame.h]
	概要 : ゲームシーンを管理する
	Author : 出合翔太

===================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "mondai.h"

//#	SceneGameクラス:親クラス,SceneBaseを継承した子クラス
class SceneGame : public SceneBase
{
private:
	int State;		//問題用ステート
	Mondai			test;
	Sprite			m_Sprite;
	D3DCOLOR		m_Color;
	bool			m_ColorFlag; //	選択UIフラグ
	
	//	Update()のヘルパー関数
	void UpdateFrame();
	void UpdateState();
	bool EndCheck();

	//	Draw()のヘルパー関数
	void DrawFrame();

public:
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};
