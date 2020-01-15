/*===================================================

	[SceneTitle.cpp]
	Author : 出合翔太

====================================================*/

#include "SceneTitle.h"
#include "SceneManager.h"
#include "Controller.h"

static bool SelectFlag;

void SceneTitle::Init()
{
	SelectFlag = false;
	m_bEnd = false;
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void SceneTitle::Uninit()
{

}

void SceneTitle::Update()
{
	//	チュートリアル選択
	if (KeyBoard::IsTrigger(DIK_Q))
	{
		SelectFlag = true;
	}
	//	ゲーム選択
	if (KeyBoard::IsTrigger(DIK_E))
	{
		SelectFlag = false;
	}
	if (!m_bEnd)
	{
		//	画面遷移
		if (KeyBoard::IsTrigger(DIK_T))
		{
			m_bEnd = true;
			Fade::Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		}
	}
	else 
	{
		if (!Fade::IsFade())
		{
			SceneManager::ChangeSceneState();
		}
	}
	
}

void SceneTitle::Draw()
{
	
}

bool GetFlag()
{
	return SelectFlag;
}
