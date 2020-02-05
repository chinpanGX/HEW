/*==================================

	[SceneGame.cpp]
	概要 : ゲームシーンを管理する
	Author : 出合翔太

===================================*/

#include "SceneGame.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Sound.h"

//	ゲームの初期化処理
void SceneGame::Init()
{
	m_bEnd = false;		
	m_ColorFlag = false;
	m_Color = D3DCOLOR_RGBA(255, 255, 255, 0);	
	test.Init();
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
	State = MONDAI_1st;
	//	BGM再生
}

//	ゲームの終了処理
void SceneGame::Uninit()
{
	//	BGM終了
	Sound::Stop();
}

//	ゲームの更新処理
void SceneGame::Update()
{
	test.Update();
	UpdateFrame();	//	枠の更新
	UpdateState();	//	ステートの更新
}

//	ゲームの描画処理
void SceneGame::Draw()
{
	DrawFrame();
	DrawTest();
}

/// <summary>
/// Update()のヘルパー関数
/// </summary>
//	枠の更新
void SceneGame::UpdateFrame()
{
	if (KeyBoard::IsTrigger(DIK_LEFTARROW) || GamePad::IsTrigger(0, BUTTON_LEFT))
	{
		m_ColorFlag = false;
		Sound::Play(S_SE_MOVE); //	カーソル移動SE
	}
	else if (KeyBoard::IsTrigger(DIK_RIGHTARROW) || GamePad::IsTrigger(0, BUTTON_RIGHT))
	{
		m_ColorFlag = true;
		Sound::Play(S_SE_MOVE); // カーソル移動SE
	}
}

//	ステートの更新
void SceneGame::UpdateState()
{
	switch (State)
	{
	case MONDAI_1st:
		if (KeyBoard::IsTrigger(DIK_SPACE) || GamePad::IsTrigger(0, BUTTON_2))
		{
			State = MONDAI_2nd;
		}
		break;
	case MONDAI_2nd:
		if (KeyBoard::IsTrigger(DIK_SPACE) || GamePad::IsTrigger(0, BUTTON_2))
		{
			State = MONDAI_3rd;
		}
		break;
	case MONDAI_3rd:
		if (KeyBoard::IsTrigger(DIK_SPACE) || GamePad::IsTrigger(0, BUTTON_2))
		{
			State = MONDAI_END;
		}
		break;
	case MONDAI_END:
		if (!m_bEnd)
		{
			m_bEnd = true;
			Fade::Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
		}
		else
		{
			if (!Fade::IsFade())
			{
				SceneManager::ChangeSceneState();
			}
		}
		break;
	}
}

//	ゲーム終了チェック	
bool SceneGame::EndCheck()
{
	return false;
}

//	枠の描画
void SceneGame::DrawFrame()
{
	D3DCOLOR leftcolor = D3DCOLOR_RGBA(255, 255, 255, 255);
	D3DCOLOR rightcolor = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	falseのとき左を選択
	if (m_ColorFlag == false)	
	{
		rightcolor = m_Color;
	}
	//	trueのとき右を選択
	else if (m_ColorFlag == true)
	{
		leftcolor = m_Color;
	}
	//	シーン更新のとき
	if (m_bEnd == true)
	{
		//	描画しない
		leftcolor = rightcolor = m_Color;
	}
	m_Sprite.Draw(TEXTURE_FRAME, 295.0f, 430.0f, 545.0f, 545.0f, 0.0f, 0.0f, 545.0f, 545.0f, leftcolor);
	m_Sprite.Draw(TEXTURE_FRAME, 970.0f, 430.0f, 545.0f, 545.0f, 0.0f, 0.0f, 545.0f, 545.0f, rightcolor);
	
}

//	問題の描画
void SceneGame::DrawTest()
{
	switch (State)
	{
	case MONDAI_1st:
		test.Draw(MONDAI_1st);
		break;
	case MONDAI_2nd:
		test.Draw(MONDAI_2nd);
		break;
	case MONDAI_3rd:
		test.Draw(MONDAI_3rd);
		break;
	case MONDAI_END:
		break;
	}
}

