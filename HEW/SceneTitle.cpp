/*===================================================

	[SceneTitle.cpp]
	Author : 出合翔太

====================================================*/

#include "SceneTitle.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Fade.h"
#include "debugproc.h"

void SceneTitle::Init()
{
	flag = false;
	//m_Camera.Init();
	//m_Map.Init();
	//m_count.Init();
}

void SceneTitle::Uninit()
{
	//m_Camera.Uninit();
	//m_Map.Uninit();
}

void SceneTitle::Update()
{
	/*m_Camera.Update();*/
	//m_count.Update();



	if (flag = false)
	{
		if (KeyBoard::IsTrigger(DIK_W))
		{
			flag = true;

			Fade::Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		}

		
	}
	else
		if (!Fade::IsFade())
		{

			SceneManager::ChangeSceneState(); 
		}
	
}

void SceneTitle::Draw()
{
	/*m_Camera.Set();
	m_Map.Draw();*/
//	m_count.Draw();
	DebugProc_Print((char*)"                                           タイトル");
}
