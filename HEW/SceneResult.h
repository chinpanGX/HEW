/*===================================================
	
	[SceneResult.h]
	Author : 出合翔太

===================================================*/

#pragma once
#include"SceneBase.h"
#include "sprite.h"

class SceneResult : public SceneBase
{
private:

	bool flag;
	Sprite		m_Sprite;				//	Spriteインスタンス
	static	int	m_Ranking[5];	//	ランキングの値を格納する配列
public:
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理

private:
	void Sort(int Score);	//	ソート関数
};

