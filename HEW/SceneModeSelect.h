/*=======================================================

	[SecneModeSelect.h]
	Author : 出合翔太

=======================================================*/

#pragma once
#include "SceneBase.h"
#include "sprite.h"

class SceneModeSelect : public SceneBase
{
	
private:
	Sprite m_Sprite;
public:
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};
bool Getflg();
