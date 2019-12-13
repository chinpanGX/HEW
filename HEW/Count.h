#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "sprite.h"
#include "Limit.h"

#define COUNTDOWN (128)


class Count 
{
private:

	Sprite      m_sprite;
	Limit	    m_Limit;

public:

	//カウントのメンバー関数のオーバーライド
	void Init();	//	ゲームの初期化処理	
	void Uninit();	//	ゲームの終了処理
	void Update();	//	ゲームの更新処理
	void Draw();	//	ゲームの描画処理
};