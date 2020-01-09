/*======================================================

	[SceneTutorial.cpp]
	Author : èoçá„ƒëæ

======================================================*/

#include "SceneTutorial.h"
#include "SceneManager.h"
#include "Controller.h"
#include"Fade.h"

void SceneTutorial::Init()
{

	flag = true;
	
}

void SceneTutorial::Uninit()
{
}

void SceneTutorial::Update()
{
	
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

void SceneTutorial::Draw()
{
}
