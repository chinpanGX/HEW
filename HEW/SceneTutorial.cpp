/*======================================================

	[SceneTutorial.cpp]
	Author : èoçá„ƒëæ

======================================================*/

#include "SceneTutorial.h"
#include "SceneManager.h"
#include "Controller.h"

void SceneTutorial::Init()
{
}

void SceneTutorial::Uninit()
{
}

void SceneTutorial::Update()
{
	if (KeyBoard::IsTrigger(DIK_W))
	{
		SceneManager::ChangeSceneState();
	}
}

void SceneTutorial::Draw()
{
}
