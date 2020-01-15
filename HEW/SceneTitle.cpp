/*===================================================

	[SceneTitle.cpp]
	Author : 出合翔太

====================================================*/

#include "SceneTitle.h"
#include "SceneManager.h"
#include "Controller.h"
#include"Fade.h"

static bool flg = true;

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
	m_sprite.Draw(TEXTURE_UI, 640.0f, 740.0f, 30.0f, 660.0f, 1008.0f, 250.0f, 30.0f, 50.0f, 0.75f, 0.75f, 0.0f);//チュートリアルの描画

	if (flg==true)
	{
		m_sprite.Draw(TEXTURE_UI, 640.0f, 540.0f, 30.0f, 360.0f, 1008.0f, 300.0f, 30.0f, 50.0f, 0.75f, 0.75f, 0.0f);//ゲームスタートの描画	
	}
	else if (flg==false)
	{
		m_sprite.Draw(TEXTURE_UI, 640.0f, 540.0f, 30.0f, 360.0f, 1008.0f, 300.0f, 30.0f, 50.0f, 0.75f, 0.75f, 0.0f, 255, 255, 255, 0);//スタート画面、色の変更
	}


	/*m_Camera.Set();
	m_Map.Draw();*/
//	m_count.Draw();

}
