/*==================================

	[SceneGame.cpp]
	概要 : ゲームシーンを管理する
	Author : 出合翔太

===================================*/

#include "SceneGame.h"
#include "SceneManager.h"
#include "Controller.h"

//	ゲームの初期化処理
void SceneGame::Init()
{
	m_ColorFlag = true;
	m_Color = D3DCOLOR_RGBA(255, 255, 255, 0);
	test.Init();
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
	flag = MONDAI_1st;
}

//	ゲームの終了処理
void SceneGame::Uninit()
{
	
}

//	ゲームの更新処理
void SceneGame::Update()
{
	if (KeyBoard::IsTrigger(DIK_RIGHTARROW) || GamePad::IsTrigger(0, BUTTON_RIGHT))
	{
		m_ColorFlag = false;
	}
	if (KeyBoard::IsTrigger(DIK_LEFTARROW) || GamePad::IsTrigger(0, BUTTON_LEFT))
	{
		m_ColorFlag = true;
	}
}
//	ゲームの描画処理
void SceneGame::Draw()
{
	D3DCOLOR leftcolor = D3DCOLOR_RGBA(255, 255, 255, 255);
	D3DCOLOR rightcolor = D3DCOLOR_RGBA(255, 255, 255, 255);
	if (m_ColorFlag == false)
	{
		leftcolor = m_Color;
	}
	else if (m_ColorFlag == true)
	{
		rightcolor = m_Color;
	}
	m_Sprite.Draw(TEXTURE_FRAME,295.0f,430.0f,545.0f,545.0f,0.0f,0.0f,545.0f,545.0f,leftcolor);
	m_Sprite.Draw(TEXTURE_FRAME,970.0f,430.0f,545.0f,545.0f,0.0f,0.0f,545.0f,545.0f,rightcolor);
	switch (flag)
	{
	case MONDAI_1st:

		test.Draw(MONDAI_1st);

		if (KeyBoard::IsTrigger(DIK_SPACE))
		{
			flag = MONDAI_2nd;
		}

		break;

	case MONDAI_2nd:

		test.Draw(MONDAI_2nd);

		if (KeyBoard::IsTrigger(DIK_SPACE))
		{
			flag = MONDAI_3rd;
		}

		break;

	case MONDAI_3rd:

		test.Draw(MONDAI_3rd);

		if (KeyBoard::IsTrigger(DIK_SPACE))
		{
			flag = MONDAI_END;
		}

		break;

	case MONDAI_END:

		if (KeyBoard::IsTrigger(DIK_SPACE))
		{
			exit(0);
		}

		break;
	}
}

bool SceneGame::EndCheck()
{
	return false;
}

